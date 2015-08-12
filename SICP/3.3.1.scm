(define (count-pairs x)
  (if (not (pair? x))
      0
      (+ (count-pairs (car x))
         (count-pairs (cdr x))
         1)))

(define z3 '(a b c))
(count-pairs z3)

(define z1 '(c))
(define z4
  (list z1 z1))

(define z23
  (cons z1 z1))
(define z7
  (cons z23 z23))


(define zi '(a b c))
(set-cdr! (cddr zi) zi)
(count-pairs zi)

(define (count-pairs x)
  (let ((aux '()))
    (define (uncounted? x)
      (if (memq x aux)
        0
        (begin
          (set! aux (cons x aux))
          1)))
    (define (count x)
      (if (not (pair? x))
        0
        (+
          (count (car x))
          (count (cdr x))
          (uncounted? x))))
    (count x)))

(count-pairs z7)

(define (has_cycle? l)
  (define (detect pair countedList)
    (cond ((not (pair? pair)) #f)
          ((memq pair countedList) #t)
          (else
            (detect (cdr pair) (cons pair countedList)))))
  (detect l '()))

(has_cycle? z7)

(define (has_cycle_2? l)
  (define (iter l r)
    (cond ((eq? l r) #t)
          ((not (pair? r)) #f)
          ((not (pair? (cdr r))) #f)
          (else (iter (cdr l) (cdr (cdr r))))))
  (cond ((not (pair? l)) #f)
        ((not (pair? (cdr l))) #f)
        (else (iter (cdr l) (cdr (cdr l))))))

(has_cycle_2? zi)
