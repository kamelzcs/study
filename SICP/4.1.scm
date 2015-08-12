(define (list-of-values-left exps env)
  (if (no-operands exps)
    '()
    (let ((left (eval (first-operand exps) env)))
      (cons left
            (list-of-values-left (rest-operands exps) env)))))

(define (application? exp) (tagged-list? exp 'call))
(define (operator exp) (cadr exp))
(define (operands exp) (cddr exp))


(define (while->combination expr)
  (sequence->exp
    (list (list 'define
                (list 'while-iter)
                (make-if (while-condition expr)
                         (sequence->exp (list (while-body expr)
                                              (list 'while-iter)))
                         'true))
          (list 'while-iter))))

(define (make-frame variables values)
  (if (= (length variables) (length values))
    (map cons variables values)
    (error "length mismatch -- MAKE-FRAME" variables values)))

(define (frame-variables frame) (map car frame))
(define (frame-values frame) (map cdr frame))

(define (env-loop var null-action eq-action env)
  (define (scan vars vals)
    (cond ((null? vars)
           (null-action env))
          ((eq? var (car vars))
           (eq-action vals))
          (else (scan (cdr vars) (cdr vals)))))
  (if (eq? env the-empty-environment)
    (error "Unbound variable" var)
    (let ((frame (first-frame env)))
      (scan (frame-variables frame)
            (frame-values frame)))))

(define (set-variable-value! var val env)
  (define (null-action e)
    (env-loop var null-action eq-action (enclosing-environment e)))
  (define (eq-action vs)
    (set-car! vs val))
  (env-loop var null-action eq-action env))

(define (lookup-variable-value var env)
  (define (null-action e)
    (env-loop var null-action eq-action (enclosing-environment e)))
  (define eq-action car)
  (env-loop var null-action eq-action env))

(define (define-variable! var val env)
  (define (null-action e)
    (add-binding-to-frame! var val (first-frame e)))
  (define (eq-action vs)
    (set-car! vs val))
  (env-loop var null-action eq-action env))

 (define (make-unbound variable env)
   (let ((vars (frame-variables (first-frame env)))
         (vals (frame-values (first-frame env))))
     (define (unbound vars vals new-vars new-vals)
       (cond ((null? vars)
              (error "variable is not in the environment -- MAKE-UNBOUND"
                     variable))
             ((eq? (car vars) variable)
              (set-car! env
                        (cons (append new-vars (cdr vars))
                              (append new-vals (cdr vals)))))
             (else (unbound (cdr vars) (cdr vals)
                            (append  new-vars (list (car vars)))
                            (append  new-vals (list (car vals)))
     (unbound vars vals '() '())))

((application? exp)
 (apply (eval (operator exp) env)
        (list-of-values (operands exp) env)))

(define (apply procedure arguments)
  (cond ((primitive-procedure? procedure)
         (apply-primitive-procedure procedure arguments))
        ...)

(define (apply-primitive-procedure proc args)
  (apply-in-underlying-scheme
   (primitive-implementation proc) args))
