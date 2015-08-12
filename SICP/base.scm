(define (average x y) (/ (+ x y)
                         2))

(define (square x) (* x x))

(define (divides? n x)
  (= (remainder n x) 0))
