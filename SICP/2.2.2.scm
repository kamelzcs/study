(cadr (caddr '(1 3 (5 7) 9)))
(caar '((7)))
(cadr (cadr (cadr (cadr (cadr (cadr '(1 (2 (3 (4 (5 (6 7))))))))))))

(define x (list 1 2 3))
(define y (list 4 5 6))

(define (append list1 list2)
  (if (null? list1)
      list2
      (cons (car list1) (append (cdr list1) list2))))

(define (reverse items)
  (if (null? items)
      items
      (append (reverse (cdr items)) (list (car items)))))

(define (deep-reverse items)
  (cond ((pair? items)
         (if (pair? (car items))
           (append
             (deep-reverse (cdr items))
             (list (deep-reverse (car items))))
           (append (deep-reverse (cdr items))
                   (deep-reverse (car items)))))
        (else
          (if (null? items)
            null
            (list items)))))
(define (fringe tree)
  (cond ((pair? tree)
         (append (fringe (car tree))
                 (fringe (cdr tree))))
        (else
          (if (null? tree)
            null
            (list tree)))))

(fringe (list 1 2 (list 3 4)))
(fringe (list 3))
