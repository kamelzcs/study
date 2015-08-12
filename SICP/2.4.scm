(define global-array '())

(define (make-entry k v) (list k v))
(define (key entry) (car entry))
(define (value entry) (cadr entry))

(define (put op type item)
  (define (put-helper k array)
    (cond ((null? array) (list(make-entry k item)))
          ((equal? (key (car array)) k) array)
          (else (cons (car array) (put-helper k (cdr array))))))
  (set! global-array (put-helper (list op type) global-array)))

(define (get op type)
  (define (get-helper k array)
    (cond ((null? array) #f)
          ((equal? (key (car array)) k) (value (car array)))
          (else (get-helper k (cdr array)))))
  (get-helper (list op type) global-array))

(define (variable? x) (symbol? x))
(define (same-variable? v1 v2)
  (and (variable? v1) (variable? v2) (eq? v1 v2)))
(define (sum? x)
  (and (pair? x) (eq? (car x) '+)))

(define (deriv exp var)
   (cond ((number? exp) 0)
         ((variable? exp) (if (same-variable? exp var) 1 0))
         (else ((get 'deriv (operator exp)) (operands exp)
                                            var))))
(define (operator exp) (car exp))
(define (operands exp) (cdr exp))

(define (attach-tag type-tag contents)
  (if (= type-tag 'scheme-number)
      contents
      (cons type-tag contents)))
(define (type-tag datum)
  (cond ((number? datum) 'scheme-number)
        ((pair? datum) (car datum))
        (else (error "Bad tagged datum -- TYPE-TAG" datum))))
(define (contents datum)
  (cond ((number? datum) datum)
        ((pair? datum) (cdr datum))
        (else (error "Bad tagged datum -- CONTENTS" datum))))
(define (install-deriv-package)
  (define (=number? exp num)
    (and (number? exp) (= exp num)))

  (define (make-sum a1 a2)
    (cond ((=number? a1 0) a2)
          ((=number? a2 0) a1)
          ((and (number? a1) (number? a2)) (+ a1 a2))
          (else (list '+ a1 a2))))
  (define (addend data) (car data))
  (define (augend data) (cadr data))
  (define (deriv-sum data var)
    (make-sum (deriv (addend data) var)
              (deriv (augend data) var)))

  (define (make-product m1 m2)
    (cond ((or (=number? m1 0) (=number? m2 0)) 0)
          ((=number? m1 1) m2)
          ((=number? m2 1) m1)
          ((and (number? m1) (number? m2)) (* m1 m2))
          (else (list '* m1 m2))))
  (define (multiplier data) (car data))
  (define (multiplicand data) (cadr data))
  (define (deriv-product data var)
    (make-sum
     (make-product (multiplier data)
                   (deriv (multiplicand data) var))
     (make-product (deriv (multiplier data) var)
                   (multiplicand data))))

  (define (make-exponentiation base exp)
    (cond ((=number? exp 0) 1)
          ((=number? exp 1) base)
          (else (list '** base exp))))
  (define (base data) (car data))
  (define (exponent data) (cadr data))
  (define (deriv-exponentation data var)
    (make-product
     (exponent data)
     (make-product
      (make-exponentiation (base data)
                           (make-sum (exponent data) (- 1)))
      (deriv (base data) var))))

  (put 'deriv '+ deriv-sum)
  (put 'deriv '* deriv-product)
  (put 'deriv '** deriv-exponentation)
  'done)

(install-deriv-package)
(deriv '(** (+ (** x 2) 1) 2) 'x)

(define (make-generic-file division file)
  (list division file))

(define (division-of-generic-file gf)
  (car gf))

(define (file-of-generic-file gf)
  (cadr gf))

(define (get-record employee file)
  ((get 'get-record' (division-of-generic-file file))
   employee
   (file-of-generic-file file)))

(define (make-from-mag-ang r a)
  (define (dispatch op)
    (cond ((eq? op 'real-part) (* r (cos a)))
          ((eq? op 'imag-part) (* r (sin a)))
          ((eq? op 'magnitude) r)
          ((eq? op 'angle) a)
          (else
           (error "Unknown op -- MAKE-FROM-MAG-ANG" op))))
  dispatch)

(define (attach-tag type-tag contents)
   (if (number? contents)
       contents
       (cons type-tag contents)))

 (define (type-tag datum)
   (cond ((number? datum) 'scheme-number)
         ((pair? datum) (car datum))
         (else (error "Bad taged datum -- TYPE-TAG" datum))))

 (define (contents datum)
   (cond ((number? datum) datum)
         ((pair? datum) (cdr datum))
         (else (error "Bad taged datum -- CONTENTS" datum))))

(define (equ? x y)
  (apply-generic 'equ ? x y))

(put 'equ? '(scheme-number scheme-number) =)
(put 'equ? '(rational rational) equ-rat?)
(define (equ-rat? x y)
  (and (= (numer x) (numer y))
       (= (denom x) (denom y)))

(put 'equ? '(complex complex) equ-complex?)
(define (equ-complex? x y)
  (and (= (real-part x) (real-part y))
       (= (imag-part x) (imag-part y))))

(define (=zero? x) (apply-generic '=zero? x))
(put '=zero? 'scheme-number (lambda (x) (= x 0)))
(put '=zero? 'rational-number
        (lambda (x) (= (number x) 0)))
(put '=zero? 'complex-number
        (lambda (x) (= (magnitude x) 0)))
