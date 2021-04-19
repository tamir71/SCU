; Tamir Enkhjargal
; COEN 171 - Programming Languages
; Homework 3 - Quicksort in Scheme

(define (filter pred lst)
	(cond
		((null? lst) lst)
		((pred (car lst)) (cons (car lst) (filter pred (cdr lst))))
		(else (filter pred (cdr lst)))))

(define (quicksort lst)
	(if (null? lst) lst
		(let*
			((a (car lst))
			 (b (cdr lst))
			 (below (lambda (x) (< x a)))
			 (above (lambda (x) (>= x a)))
			)
			(append
				(quicksort (filter below b)) (cons a (quicksort (filter above b))))
			)))
