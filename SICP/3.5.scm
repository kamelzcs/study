(include "3.5-base.scm")
(include "base.scm")
(define (partial-sums s)
  (cons-stream
    (stream-car s)
    (add-streams
      (stream-cdr s)
      (partial-sums s))))
(stream-ref
   (stream-enumerate-interval 1 100)
   11)

(define (stream-map proc . argstreams)
  (if (null? (stream-car argstreams))
      the-empty-stream
      (cons-stream
       (apply proc (map stream-car argstreams))
       (apply stream-map
              (cons proc (map stream-cdr argstreams))))))

(define s1 (stream-enumerate-interval 10 100))
(define s2 (stream-enumerate-interval 20 200))
(define s3 (stream-enumerate-interval 30 300))

(define test (stream-map + s1 s2 s3))
(stream-ref test 0)
(stream-ref test 1)
(stream-ref test 2)

(define (show x)
  (display-line x)
  x)

(define x (stream-map show (stream-enumerate-interval 0 10)))
(stream-ref x 5)
(stream-ref x 7)

(define (integrate-series s)
  (stream-map / s integers))

(define sine-series
  (cons-stream 0 (integrate-series cosine-series)))

(define cosine-series
  (cons-stream 1
               (scale-stream
                 (integrate-series sine-series)
                 -1)))

(define (mul-series s1 s2)
  (cons-stream
    (* (stream-car s1) (stream-car s2))
    (add-streams
      (scale-stream
        (stream-cdr s2)
        (stream-car s1))
      (mul-series
        (stream-cdr s1)
        s2))))

(define t
  (add-streams
    (mul-series sine-series sine-series)
    (mul-series cosine-series cosine-series)))

(define (invert-unit-series s)
  (cons-stream 1
               (scale-stream
                 (mul-series
                   (stream-cdr s)
                   (invert-unit-series s)))))

(define (div-series num den)
   (let ((den0 (stream-car den)))
      (if (= den-const 0)
        (error "The constant term of the denominator must be nonzero")
        (scale-stream
         (mul-series
          num (invert-unit-series
                (scale-stream den (/ 1 den-const))))
         (/ 1 den-const)))))

(define (sqrt-improve guess x)
  (average guess (/ x guess)))

(define (sqrt-stream x)
  (define guesses
    (cons-stream 1.0
                 (stream-map (lambda (guess)
                               (sqrt-improve guess x))
                             guesses)))
  guesses)

(define (pi-summands n)
  (cons-stream (/ 1.0 n)
               (stream-map
                 -
                 (pi-summands (+ n 2)))))
(define pi-stream
  (scale-stream (partial-sums (pi-summands 1)) 4))

(define (euler-transform s)
  (let ((s0 (stream-ref s 0))           ; Sn-1
        (s1 (stream-ref s 1))           ; Sn
        (s2 (stream-ref s 2)))          ; Sn+1
    (cons-stream (- s2 (/ (square (- s2 s1))
                          (+ s0 (* -2 s1) s2)))
                 (euler-transform (stream-cdr s)))))

(define (make-tableau transform s)
  (cons-stream s
               (make-tableau transform
                             (transform s))))
(define (accelerated-sequence transform s)
  (stream-map stream-car
              (make-tableau transform s)))

(stream-ref (accelerated-sequence euler-transform
                                      pi-stream) 2)

(define (stream-limit s tolerance)
  (let ((s2 (stream-cdr s)))
    (if (< (abs
             (-
               (stream-car s)
               (stream-car s2)))
           tolerance)
      (stream-car s2)
      (stream-limit s2 tolerance))))

(define (sqrt2 x tolerance)
  (stream-limit (sqrt-stream x) tolerance))

(sqrt2 2.0 0.0001)

(define (log2-summands n)
  (cons-stream (/ 1.0 n)
               (stream-map - (log2-summands (+ n 1)))))
(define log2-stream
  (partial-sums (log2-summands 1)))

(stream-limit
  (accelerated-sequence euler-transform log2-stream) 0.0001)

(define (interleave s1 s2)
  (if (stream-null? s1)
      s2
      (cons-stream (stream-car s1)
                   (interleave s2 (stream-cdr s1)))))

(define (pairs s t)
  (cons-stream
   (list (stream-car s) (stream-car t))
   (interleave
    (stream-map (lambda (x) (list (stream-car s) x))
                (stream-cdr t))
    (pairs (stream-cdr s) (stream-cdr t)))))

(stream-ref (pairs integers integers) 4)

(define (merge-weighted s1 s2 weight)
  (cond ((stream-null? s1) s2)
        ((stream-null? s2) s1)
        (else
          (let ((s1car (stream-car s1))
                (s2car (stream-car s2)))
            (if (<= (weight s1car)
                    (weight s2car))
              (cons-stream s1car
                           (merge-weighted (stream-cdr s1)
                                           s2
                                           weight))
              (cons-stream s2car
                           (merge-weighted s1
                                           (stream-cdr s2)
                                           weight)))))))

(define (weighted-pairs s t weight)
  (cons-stream
    (list (stream-car s) (stream-car t))
    (merge-weighted
      (stream-map
        (lambda (x) (list (stream-car s) x))
        (stream-cdr t))
      (weighted-pairs
        (stream-cdr s)
        (stream-cdr t)
        weight)
      weight)))

(weighted-pairs integers
                integers
                (lambda (x)
                  (apply + x)))

(define no-factors
  (stream-filter
    (lambda (x)
      (not
        (or (divides? x 2)
            (divides? x 3)
            (divides? x 5))))
    integers))

(weighted-pairs no-factors
                no-factors
                (lambda (lst)
                  (let ((i (car lst))
                        (j (cadr lst)))
                    (+
                      (* 2 i)
                      (* 3 j)
                      (* 5 i j)))))

(define (sum-cube pair)
  (let ((i (car pair))
        (j (cadr pair)))
    (+ (* i i i)
       (* j j j))))

(define all-pairs
  (weighted-pairs integers integers sum-cube))

(define (ram-numbers stream)
  (let* ((w1 (sum-cube
               (stream-car stream)))
         (rest (stream-cdr stream))
         (w2 (sum-cube
               (stream-car rest))))
    (if (= w1 w2)
      (cons-stream w1
                   (ram-numbers (stream-cdr
                                  rest)))
      (ram-numbers rest))))

(show-stream (ram-numbers all-pairs) 6)

(define (integral integrand initial-value dt)
  (define int
    (cons-stream initial-value
                 (add-streams (scale-stream integrand dt)
                              int)))
  int)

(define (RC r c dt)
  (lambda (i v)
    (add-streams
      (scale-stream i r)
      (integral (scale-stream i
                              (/ 1 c))
                v
                dt))))

(define zero-crossings
  (stream-map sign-change-detector sense-data
              (cons-stream 0 sense-data)))

(define (smooth s)
  (stream-map (lambda (x y) (/ (+ x y) 2))
              (cons-stream 0 s)
              s))
