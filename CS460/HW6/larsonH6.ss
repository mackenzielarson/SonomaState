;;;;;Mackenzie Larson
;;;;;5/9/16
;;;;;HW6 CS 460 WATTS

;;;;1. Write a new procedure called all-reverse that recurisvely reverses nested lists.
;;;;Recursively reverses nested lists '(a (b (c d))(e f))
;;;;Old list reverse returns: (list-reverse '(a (b c) d))
;;;;$1 = (d (b c) a)

(define all-reverse
  (lambda (lst)
    (if (null? lst) lst
	(if (list? (car lst))
	    (append (all-reverse (cdr lst)) (cons (all-reverse (car lst)) '()))
	    (append (all-reverse (cdr lst)) (list (car lst)))))))

;;;;(all-reverse '(a (b (c d))(e f)))
;;;;$1 = ((f e) ((d c) b) a)


;;;;;2. Quicksort procedure that uses quick sort to sort its single list argument into ascending order
(define (split compare lst)
  (cond
   ((null? lst) '())
   ((compare (car lst)) (cons (car lst) (split compare (cdr lst))))
   (else (split compare (cdr lst)))))

(define (quicksort lst)
  (cond
   ((null? lst) '())
   (else (let ((pivot (car lst)))
	   (append (append (quicksort (split (lambda (x) (< x pivot)) lst))
			   (split (lambda (x) (= x pivot)) lst))
		   (quicksort (split (lambda (x) (> x pivot)) lst)))))))
;;;;;(quicksort '(1 5 3 6 8 92 -1 0 4 5 3))
;;;;;$3 = (-1 0 1 3 3 4 5 5 6 8 92)

;;;;;3. Mergesort procedure that uses merge sort to sort its single list argument into descending order
;;;; (mergesort '(1 5 3 6 8 92 -1 0 4 5 3))
;;;; $2 = (92 8 6 5 5 4 3 3 1 0 -1)
;;;;;Will find the first half of the list to be sorted
(define (getfirsthalf lst n)
  (if (or (null? lst) (<= n 0))
      '()
      (cons (car lst) (getfirsthalf (cdr lst) (- n 1)))))

;;;;;Will remove the first half of the list and is left with second half of list
(define (secondhalf lst n)
  (if (or (null? lst) (<= n 0));;;null if list is empty
      lst
      (secondhalf (cdr lst) (- n 1))))

;;; merge sort function will sort through both halfs of the list 
(define (mergesort lst)
  (define (sort lst)
    (letrec ((merge (lambda (ls rs)
		      (cond ((null? ls) rs)
			    ((null? rs) ls)
			    ((> (car ls) (car rs)) (cons (car ls) (merge (cdr ls) rs)))
			    (else (cons (car rs) (merge ls (cdr rs))))))))
      (if (or (null? lst) (< (length lst) 2))
	  lst
	  (let ((half (quotient (length lst) 2)))
	    (merge (sort (getfirsthalf lst half)) (sort (secondhalf lst half)))))))
  (if (list? lst)
      (sort (filter number? lst))
      lst))
