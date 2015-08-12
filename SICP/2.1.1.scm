(define (number x) (car x))
(define (denom x) (cdr x))

(define (make-rat n d)
  (let ((g (gcd n d)))
    (if (> d 0)
      (cons (/ n g) (/ d g))
      (cons (/ (- n) g) (/ (- d) g)))))

(define (print-rat x)
  (newline)
  (display (number x))
  (display "/")
  (display (denom x)))

(define (print-point p)
   (newline)
   (display "(")
   (display (x-point p))
   (display ",")
   (display (y-point p))
   (display ")"))

(define (make-segment a b) (cons a b))

(define (start-segment s) (car s))
(define (end-segment s) (cdr s))

(define (make-point x y) (cons x y))
(define (x-point p) (car p))
(define (y-point p) (cdr p))

(define (midpoint-segment s)
  (make-point
    (/
      (+
        (x-point (start-segment s))
        (x-point (end-segment s)))
      2)
    (/
      (+
        (y-point (start-segment s))
        (y-point (end-segment s)))
      2)))

(define a (make-point 0 2))

(define s (make-segment a a))

;define rectangle using two points
(define (make-rec a b) (cons a b))

(define (rect-width r)
  (abs (-
         (x-point (car r))
         (x-point (cdr r)))))

(define (rect-height r)
  (abs (-
         (y-point (car r))
         (y-point (cdr r)))))

(define (rect-perimeter r)
   (* 2 (+ (rect-width r) (rect-height r))))

(define (rect-area r)
   (* (rect-width r) (rect-height r)))

;define rectangle using base point, width and height
(define (make-rect p w h) (cons p (cons w h)))

(define (rect-width r)
   (car (cdr r)))

(define (rect-height r)
   (cdr (cdr r)))

(define (proc-cons x y)
  (lambda (m) (m x y)))

(define (proc-car z)
  (z (lambda (p q) p)))

(define (proc-cdr z)
  (z (lambda (p q) q)))

(define (get-degree n d)
  (if (= 0 (remainder n d))
         (+ 1 (get-degree (/ n d) d))
         0))

(define (math-cons a b)
  (* (expt 2 a)
     (expt 3 b)))

(define (math-car s)
  (get-degree s 2))

(define (math-cdr s)
  (get-degree s 3))

(define zero (lambda (f) (lambda (x) x)))

(define (add-1 n)
   (lambda (f) (lambda (x) (f ((n f) x)))))

(define one
   (lambda (f) (lambda (x) (f x))))

(define two
   (lambda (f) (lambda (x) (f (f x)))))

(define (church-add a b)
  (lambda (f) (lambda (x) ((a f) ((b f) x)))))

(define (church-multi a b)
  (lambda (f) (lambda (x) ((a (b f)) x))))

(define three (church-add one two))
(define four (church-multi two two))
((four inc) 0)
