(define (make-accumulator initial)
  (let ((accumulate initial))
    (lambda (x)
      (set! accumulate (+ accumulate x))
      accumulate)))

(define A (make-accumulator 5))
(A 10)
(A 10)

(define (make-monitored proc)
  (let ((call-times 0))
    (define (dispatch m)
      (cond
        ((eq? m 'how-many-calls?) call-times)
        ((eq? m 'reset-count) (set! call-count 0))
        (else
          (set! call-times (+ 1 call-times))
          (proc m))))
    dispatch))

(define s (make-monitored sqrt))
(s 100)
(s 100)

(s 'how-many-calls?)

(define (make-account balance password)
  (define (withdraw amount)
    (if (>= balance amount) (begin (set! balance (- balance amount)) balance)
        "Insufficient funds"))
  (define (deposit amount)
    (set! balance (+ balance amount)) balance)
  (define (dispatch pass m)
    (if (not (eq? pass password))
      (error "Bad password -- " pass)
      (cond ((eq? m 'withdraw) withdraw)
            ((eq? m 'deposit) deposit)
            (else (error "Unknown request -- MAKE-ACCOUNT" m)))))
  dispatch)

(define acc (make-account 100 'secret-password))
((acc 'secret-password 'withdraw) 40)
((acc 'some-other-password 'deposit) 50)


(define (make-account balance password)
  (define (withdraw amount)
    (if (>= balance amount) (begin (set! balance (- balance amount)) balance)
        "Insufficient funds"))
  (define (deposit amount)
    (set! balance (+ balance amount)) balance)
  (define (error-message amount)
    (display 'incorrect-password))
  (let ((incorrect-pass-count 0))
    (define (dispatch pass m)
        (if (not (eq? pass password))
          (begin
            (set! incorrect-pass-count (+ 1 incorrect-pass-count))
            (if (> incorrect-pass-count 7)
              call-the-cops
              error-message))
          (begin
            (set! incorrect-pass-count 0)
            (cond ((eq? m 'withdraw) withdraw)
                            ((eq? m 'deposit) deposit)
                            (else (error "Unknown request -- MAKE-ACCOUNT" m)))))))
  dispatch)

(define (square x) (* x x))

(define (random-in-range low high)
 (let ((range (- high low)))
   (+ low (random range))))

(define (monte-carlo trials experiment)
  (define (iter trials-remaining trials-passed)
    (cond ((= trials-remaining 0)
           (/ trials-passed trials))
          ((experiment)
           (iter (- trials-remaining 1) (+ trials-passed 1)))
          (else
           (iter (- trials-remaining 1) trials-passed))))
  (iter trials 0))

(define (rect-area x1 x2 y1 y2)
  (abs (* (- x2 x1) (- y2 y1))))

(define (estimate-integral P x1 x2 y1 y2 trials)
  (define (test)
    (P (random-in-range x1 x2) (random-in-range y1 y2)))
  (* (monte-carlo trials test)
     (rect-area x1 x2 y1 y2)))

(define (estimate-pi trials)
  (define (P x y)
    (< (+ (square x) (square y)) 1.0))
  (estimate-integral P -1.0 1.0 -1.0 1.0 trials))

(estimate-pi 100)

