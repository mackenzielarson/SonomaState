#|
Author: Mackenzie Larson
Date: 5/2/16
Homework 5 Scheme Tutorial

1.
(car '(a b c))
$1 = a
(cdr '(a b c))
$2 = (b c)
(cons 'a '(b c))
$3 = (a b c)
(cons '(a b) '(c d))
$4 = ((a b) c d)
(car '((1 2) (3 4) (5 6)))
$5 = (1 2)
(cdr '((1 2) (3 4) (5 6)))
$6 = ((3 4) (5 6))
(cons '55 '((1 2) (3 4) (5 6)))
$7 = (55 (1 2) (3 4) (5 6))
(cons '(5 5) '((1 2) (3 4) (5 6)))
$8 = ((5 5) (1 2) (3 4) (5 6))

2.
car: Car will return the first element in a list
cdr: Cdr woll retr a sublist containing all elements except the first
cons: Cons takes two arguments and returns a list constructed from those two elements.

3.
$9 = (a e f)

5.
(square 5)
$10 = 25
(square -200)
$11 = 40000
(square 0.5)
$12 = 0.25
(square -1/2)
$13 = 1/4

7.
(reciprocal 10)
$1 = 1/10
(reciprocal 1/10)
$2 = 10
(reciprocal 0)
$3 = "oops!"
(reciprocal (reciprocal 1/10))
$4 = 1/10

8.
Command: (square (reciprocal 1/10))
Result: $1 = 100
Command: (reciprocal (square (square 10)))
Result: $2 = 1/10000

9.
(+ 2 5)
$3 = 7
(* 1.5 2.3)
$4 = 3.44999999999999997
(-(* 2 2/5)(/ 2 5))
$5 = 2/5


10.
1.2 x (2 -1/3) + -8.7
(+(*(/(+(* 2 3) -1) 3) 1.2) -8.7)

(2/3 + 2/9)/(5/1 -2/3)
(/ (+ 2/3 2/9) (- 5/1 2/3) )

1 + 1/(2 + 1/(1 + 1/2))
(+(/ 1 (+ 2 1) (/ (+ 1 1/2))) 1)

1 × -2 × 3 × -2 × 5 × -6 × 7
(*(*(*(*(*(* 1 -2) 3) -2) 5) -6) 7)


11.
Command: (square (reciprocal (* 2 3)))
Result: $10 = 1/36
Command: (reciprocal (* (square 10) 4))
Result:$11 = 1/400

12
atom: am atom is a fundamental winit in scheme (numbers are atoms and numbers evaluate to themselves)

primitive: procedure that manipulates data

lambda expression: a lambda expression creates a function in scheme

free variable: notation that specifies places in an expression where substitiution may take place

top level definition: the place where a function is defined

predicate: a procedure that always returns a boolean value

type predicate: numerical type predicates can be applied to any kind of argument; this includes non numbers. In general, if a
type predicate is true of  anumber than all higher type predicates are also true of that number and vice versa if false

lexical scoping: Scheme is a lexically scoped language as opposed to using dynamic scope. The identifier is fixed at
interpretation and or compilation in some region in the scource code containing the identifier's declation


13.
list? : Is the argument a list?
number? : Is the argument a number?
null? : Is the argument the empty list?
cddddr : -> object | (setf(cddddr x) new-object)
if : Choose between two alternatives
let : Give temporary names to values

|#

(define reciprocal
  (lambda (n)
    (if (= n 0)
	"oops!"
	(/ 1 n))))

(define square
  (lambda (n)
    (* n n)))

;;;;16. When entering (insert-first 1 2)?
;;;;Wrong number of elements to #<procedure insert-first
(define insert-first
  (lambda (lst arg)
    (if (list? lst)
	(cons arg lst);will add the argument arg to the front of the list
	"The first arg must be a list AND OR You can only prepend one element to a list")))
;;;;(insert-first '(2 3 4 5 6) 1)
;;;;$2 = (1 2 3 4 5 6)

;;;;17. What happens when you enter(remove-first 1)?
;;;;Wrong type argument for cdr
(define remove-first
  (lambda (lst)
    (if (and (list? lst) (not (null? lst)));check if the list is not null
	(cdr lst);will remove the first element of the list
	"You can only remove an element if the list is not empty")))
;;;;(remove-first '(1 2 3 4 5 6))
;;;;$1 = (2 3 4 5 6)
;;;;18. What happens if you enter (remove-first '())/
;;;;The list is empty. Cannor remove an element from a non-empty list

;;;;20. List copy will create a copy of a list
;;;;(list-copy '(1 2 3 4 5 6))
;;;;$1 = (1 2 3 4 5 6)
(define list-copy
  (lambda (lst)
    (if (and (list? lst) (not (null? lst)))
	(cons (car lst) (list-copy (cdr lst)))
	'())))

;;;;21. Odd-copy: Will creat a copy of the elements in the off numbered positions in a list starting with the first element in the list
(define odd-copy
  (lambda (lst)
    (cond
     ((not (list? lst)) "ERROR The first argument needs to be a list")
     ((or (null? lst) (null? (cdr lst))) lst)
     (else (cons (car lst) (odd-copy (cddr lst)))))))
;;;;;(odd-copy '(1 2 3 4 5 6))
;;;;;$1 = (1 3 5)

;;;;22. Even-copy: Will create a copy of the elements in the even numbered positions in a list starting with the second element in the list
(define even-copy
  (lambda (lst)
    (cond
     ((not (list? lst)) "ERROR The First argument needs to be a list")
     ((or (null? lst) (null? (cdr lst))) '())
     (else (cons (car (cdr lst)) (even-copy (cddr lst)))))))
;;;; (even-copy '(1 2 3 4 5 6))
;;;;$1 = (2 4 6)

;;;;23. Insert-last: Will insert a value into a list as the last element of the list
(define insert-last
  (lambda (lst arg)
    (if (list? lst)
	(append lst (list arg))
	"First arg of this function must be a list")))
;;;;(insert-last '(1 2 3 4 5) 6)
;;;;$1 = (1 2 3 4 5 6)


;;;;24. Remove-last: Remove the lst element of a list
(define remove-last
  (lambda (lst)
    (if (and (list? lst) (not (null? lst)))
	(if (null? (cdr lst))
	    '()
	    (cons (car lst) (remove-last (cdr lst))))
	'())))
;;;;(remove-last '(1 2 3 4 5 6))
;;;;$1 = (1 2 3 4 5)

;;;;25. List-reverse: Will reverse the elements of a list
(define list-reverse
  (lambda (lst)
    (if (and (list? lst) (not (null? lst)))
	(append (list-reverse (cdr lst)) (list (car lst)))
	'())))
;;;;;(list-reverse '(1 2 3 4 5 6))
;;;;;$1 = (6 5 4 3 2 1)

;;;;26. Square-root: Calculate the square root of a numeric value. If the param is not numeric, this function should return 0
(define square-root
  (lambda (arg)
    (cond
     ((not (number? arg)) "The argument must be a number")
     (else (sqrt arg)))))
;;;;(square-root 100)
;;;; $1 = 10
