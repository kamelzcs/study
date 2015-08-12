;(print-as-expression #f)
(list 'a 'b 'c)

(list (list 'george))
(cadr '((x1 x2) (y1 y2)))
(pair? (car '(a short list)))
(memq 'red '((red shoes) (blue socks)))

(memq 'red '(red shoes blue socks))

(define (equal? a b)
  (cond ((and (pair? a) (pair? b))
         (and (equal? (car a) (car b))
              (equal? (cdr a) (cdr b))))
        ((and (not (pair? a)) (not (pair? b)))
         (eq? a b))
        (else #f)))

(equal? '(this is a list) '(this is a list))
(equal? '(this is a list) '(this (is a) list))

'((1 2) (3 4))
