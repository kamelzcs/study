#lang planet neil/sicp
(define (f-triple n)
  (cond ((< n 3) n)
        (else
          (+ (f-triple (- n 1))
           (f-triple (- n 2))
           (f-triple (- n 3))))))

(define (f-triple-iter n)
  (if (< n 3)
    n
    (f-iter 2 1 0 (- n 2))))
(define (f-iter a b c count)
  (if (= count 0)
    a
    (f-iter (+ a (* 2 b) (* 3 c))
            a
            b
            (- count 1))))

(define (triangle row col)
  (cond ((= col 1) 1)
        ((> col row) 0)
        (else
            (+ (triangle (- row 1) (- col 1))
               (triangle (- row 1) col)))))

(triangle 5 3)
