(define (fold-left op init seq)
  (define (iter ans res)
    (if (null? res)
      ans
      (iter (op ans (car res)) (cdr res))))
  (iter init seq))

(define (make-table same-key?)
  (define (associate key records)
    (cond ((null? records) #f)
          ((same-key? key (caar records))
           (car records))
           (else
             (associate key (cdr records)))))
  (let ((the-table (list '*table*)))
    (define (lookup keys)
      (define (lookup-record record-list key)
        (if record-list
          (let ((record (associate key record-list)))
            (if record
              (cdr record)
              #f))
          #f))
    (fold-left lookup-record (cdr the-table) keys))
  (define (insert! keys value)
    (define (descend table key)
      (let ((record (associate key (cdr table))))
        (if record
          record
          (let ((new (cons (list key)
                           (cdr table))))
            (set-cdr! table new)
            (car new)))))
    (set-cdr! (fold-left descend the-table keys)
              value))
  (define (dispatch m)
    (cond ((eq? m 'lookup) lookup)
          ((eq? m 'insert!) insert!)
          (else (error "Undefined method" m))))
    dispatch))

(define op-table (make-table eq?))
(define put (op-table 'insert!))
(define get (op-table 'lookup))
(put '(letters a) 97)  ; Two dimensions
(put '(letters b) 98)
(put '(math +) 43)
(put '(math -) 45)
(put '(math *) 42)
(put '(greek majiscule Λ) 923)  ; Three dimensions
(put '(greek miniscule λ) 955)
(put '(min) 42)  ; One dimension
(put '(max) 955)
(get '(min))
(get '(letters b))
(put '(min) 43)  ; update
(get '(min))

(define (entry tree) (car tree))
(define (entry-key tree) (caar tree))
(define (entry-value tree) (cdar tree))
(define (left-branch tree) (cadr tree))
(define (right-branch tree) (caddr tree))

(define (make-tree entry left right)
  (list entry left right))

(define (adjoin-set x set)
  (cond ((null? set)
         (make-tree x '() '()))
        ((= (car x) (entry-key set))
         (set-cdr! (entry set) x))
        ((< (car x) (entry-key set))
         (make-tree (entry set)
                    (adjoin-set x (left-branch set))
                    (right-branch set)))
        (else
          (make-tree (entry set)
                     (left-branch set)
                     (adjoin-set x (right-branch set))
                     ))))

(define (make-table)
  (let ((local-table '()))
    (define (associate key)
      (define (iter tree)
        (cond ((null? tree) #f)
              ((= key (entry-key tree))
               (entry tree))
              ((< key (entry-key tree))
               (iter (left-branch tree)))
              (else
                (iter (right-branch tree)))))
      (iter local-table))
    (define (insert! key value)
      (let ((record (associate key)))
        (if record
          (set-cdr! record value)
          (set! local-table
            (adjoin-set (cons key value) local-table)
            ))))
     (define (dispatch m)
       (cond ((eq? m 'get-proc) associate)
             ((eq? m 'insert-proc) insert!)))
     dispatch))

(define table (make-table))
(define get (table 'get-proc))
(define put (table 'insert-proc))

(put 43 'a)
(put 42 'b)
(get 43)
(get 42)

(put 43 'e)
(get 43)
