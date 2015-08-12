(define (same-parity a . z)
  (define (iter f left)
    (if (null? left)
      left
      (let* ([first (car left)]
            [second (cdr left)]
            [temp (iter f second)])
        (if (f first)
          (cons first temp)
          temp))))
  (iter
    (lambda (x) (= (remainder a 2) (remainder x 2)))
    (cons a z)))

(define (map proc items)
   (if (null? items)
       null
       (cons (proc (car items))
             (map proc (cdr items)))))

(define (square x) (* x x))

(define (square-list items)
   (if (null? items)
       null
       (cons (square (car items))
             (square-list (cdr items)))))

(define (square-list items)
   (map square items))

(define (square-list items)
   (define (iter things answer)
     (if (null? things)
         answer
         (iter (cdr things)
               (append answer
                       (list (square (car things)))))))
   (iter items null))

(define (for-each proc items)
  (cond
    ((null? items) #t)
    (else (proc (car items))
          (for-each proc (cdr items)))))

(for-each (lambda (x) (newline) (display x))
         (list 57 321 88))
