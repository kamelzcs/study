(define (square x) (* x x))
(define (smallest-divisor n) (find-divisor n 2))
(define (find-divisor n test-divisor)
  (cond ((> (square test-divisor) n) n)
        ((divides? test-divisor n) test-divisor)
        (else (find-divisor n (+ test-divisor 1)))))
(define (divides? a b) (= (remainder b a) 0))
(define (expmod base exp m)
  (cond ((= exp 0) 1)
        ((even? exp)
         (remainder
           (square (expomod base (/ exp 2) m))
           m))
        (else
          (remainder
            (* base (expmod base (- exp 1) m))
            m))))
(define (fermat-test n)
  (define (try-it a)
    (= (expmod a n n) a))
  (try-it (+ 1 (random (- n 1)))))
(define (fast-prime? n times)
  (cond ((= times 0) true)
        ((fermat-test n) (fast-prime? n (- times 1)))
        (else false)))

(define (timed-prime-test n)
   (newline)
   (display n)
   (start-prime-test n (runtime)))

(define (start-prime-test n start-time)
   (cond ((prime? n)
          (report-prime (- (runtime) start-time)))))

(define (report-prime elapsed-time)
   (display " *** ")
   (display elapsed-time))

(define (prime? n)
   (= n (smallest-divisor n)))

(define (search-for-primes start end)
  (if (even? start) (search-for-primes (+ start 1) end)
    (cond ((<= start end)
           (timed-prime-test start) (search-for-primes (+ start 2) end)))))

(define (fixed-fermat-test n a)
  (= (expmod a n n) a))

(define (fermat-full n)
  (define (iter a)
    (cond ((= a 1) #t)
          ((not (fixed-fermat-test n a)) #f)
          (else (iter (- a 1)))))
  (iter (- n 1)))

(fermat-full 6601)
