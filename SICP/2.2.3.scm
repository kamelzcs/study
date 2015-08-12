 (define (filter predicate sequence) 
   (cond ((null? sequence) nil) 
         ((predicate (car sequence)) 
          (cons (car sequence)  
                (filter predicate (cdr sequence)))) 
         (else (filter predicate (cdr sequence))))) 

(define (accumulate op initial sequence)
   (if (null? sequence)
       initial
       (op (car sequence)
           (accumulate op initial (cdr sequence)))))

(accumulate + 0 (list 1 2 3 4 5))

(define (map p sequence)
   (accumulate (lambda (x y) (cons (p x) y)) null sequence))

(define (square x) (* x x))

(map square '(1 2 3))

(define (append seq1 seq2)
   (accumulate cons seq2 seq1))

(append (list 1 2 3) (list 4 5 6))

(define (length sequence)
   (accumulate (lambda (x y) (+ 1 y)) 0 sequence))

(length '(1 2 3))

(define (horner-eval x coefficient-sequence)
   (accumulate (lambda (this-coeff higher-terms)
                 (+ this-coeff
                    (* x higher-terms)))
               0
               coefficient-sequence))

(horner-eval 2 (list 1 3 0 5 0 1))

(define (count-leaves t)
   (accumulate + 0 (map
                     (lambda (x)
                       (if (not (pair? x))
                         1
                         (count-leaves x)))
                     t)))

(define (accumulate-n op init seqs)
   (if (null? (car seqs))
       null
       (cons (accumulate op init
                         (map (lambda (x)
                                (car x))
                              seqs))
             (accumulate-n op init
                           (map (lambda (x)
                                  (cdr x))
                                seqs)))))

(accumulate-n + 0 '((1 2 3) (4 5 6) (7 8 9) (10 11 12)))

(define (dot-product v w)
   (accumulate + 0 (map * v w)))

(define (matrix-*-vector m v)
   (map (lambda (row)
          (dot-product v row)) m))

(define m0 '((1 2 3 4) (4 5 6 6) (6 7 8 9)))
(matrix-*-vector m0 '( 2 1 4 5))

(define (transpose mat)
   (accumulate-n cons null  mat))

(transpose m0)

(define (matrix-*-matrix m n)
   (let ([cols (transpose n)])
      (map (lambda(v) (matrix-*-vector cols v)) m)))

(matrix-*-matrix m0 (transpose m0))

(define (fold-right op initial sequence)
   (if (null? sequence)
       initial
       (op (car sequence)
           (fold-right op initial (cdr sequence)))))

(define (fold-left op initial sequence)
   (define (iter result rest)
     (if (null? rest)
         result
         (iter (op result (car rest))
               (cdr rest))))
   (iter initial sequence))

(fold-right / 1 (list 1 2 3))
(fold-left / 1 (list 1 2 3))
(fold-right list null (list 1 2 3))
(fold-left list null (list 1 2 3))

(define (reverse sequence)
  (fold-right (lambda (x y)
                (append y (list x)))
              null
              sequence))

(reverse (list 1 2 3 4))

(define (reverse sequence)
  (fold-left (lambda (x y)
                (cons y  x))
              null
              sequence))

(reverse (list 1 2 3 4))

(define (square x) (* x x))

(define (smallest-divisor n)
  (find-divisor n 2))

(define (find-divisor n test-divisor)
  (cond ((> (square test-divisor) n) n)
        (( divides? test-divisor n) test-divisor)
        (else (find-divisor n (+ test-divisor 1)))))

(define (divides? a b)
  (= (remainder b a) 0))

(define (prime? n)
  (= n (smallest-divisor n)))

;(define (enumerate-interval a b)
  ;(cond ((> a b) null)
        ;(else
          ;(cons a
                ;(enumerate-interval
                  ;(+ a 1)
                  ;b)))))

(define accumulate fold-right)

(define (enumerate-interval low high)
  (if (> low high)
      '()
      (cons low (enumerate-interval (+ low 1) high))))

(define (flatmap proc seq)
   (accumulate append null (map proc seq)))

(define (prime-sum? pair)
   (prime? (+ (car pair) (cadr pair))))

(define (make-pair-sum pair)
   (list (car pair) (cadr pair) (+ (car pair) (cadr pair))))

(define (prime-sum-pairs n)
   (map make-pair-sum
        (filter prime-sum?
                (flatmap
                 (lambda (i)
                   (map (lambda (j) (list i j))
                        (enumerate-interval 1 (- i 1))))
                 (enumerate-interval 1 n)))))

(define (unique-pairs n)
  (flatmap (lambda (i)
             (map (lambda (j) (list i j))
                  (enumerate-interval 1 (- i 1))))
           (enumerate-interval 1 n)))

(define (prime-sum-pairs n)
   (map make-pair-sum
        (filter prime-sum?
                (unique-pairs n))))

(define (unique-triples n)
  (flatmap (lambda (i)
             (flatmap (lambda (j)
                        (map
                          (lambda (k) (list i j k))
                          (enumerate-interval 1 (- j 1))))
                      (enumerate-interval 1 (- i 1))))
           (enumerate-interval 1 n)))

(define (equal-sum? s)
  (lambda (lst)
    (= s (accumulate + 0 lst))))

(prime-sum-pairs 3)
(filter (equal-sum? 11) (unique-triples 6))

(define (flatmap proc seq)
  (accumulate append '() (map proc seq)))
(define accumulate fold-right)
(define (enumerate-interval low high)
  (if (> low high)
      '()
      (cons low (enumerate-interval (+ low 1) high))))

(define (queens board-size)
  (define (queen-cols k)
    (if (= k 0)
        (list empty-board)
        (filter
         (lambda (positions) (safe? k positions))
         (flatmap
          (lambda (rest-of-queens)
            (map (lambda (new-row)
                   (adjoin-position new-row k rest-of-queens))
                 (enumerate-interval 1 board-size)))
          (queen-cols (- k 1))))))
  (queen-cols board-size))

(define empty-board '())

(define (adjoin-position row k rest-of-queens)
  (append rest-of-queens (list (list row k))))

(define (last l)
    (cond ((null? (cdr l)) (car l))
          (else (last (cdr l)))))

(define (safe? k positions)
  (define (attack? q1 q2)
    (and (not (= (car q1) (car q2)))
         (not (= (abs (- (car q1) (car q2)))
                 (abs (-  (cadr q1)(cadr q2)))))))

  (let ((new-queen (last positions)))
    (define (check i positions)
      (cond ((= i k) true)
            ((attack? (car positions) new-queen)
             (check (+ i 1) (cdr positions)))
            (else false)))
    (check 1 positions)))

(queens 4)

