;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
;     Project:    QuickSort.scm
;     Name:       Jonny Hughes
;     Class:      Comparative Programming Languages
;     Proffessor: Dr. Crawley
;     Last Edits: 4/10/20 - init
;                 4/13/20 - fixed up org n names
;                 4/14/20 - finishing touches
;
;    Info: This program creates the (qs) function and it's
;          helpers (less) and (great). When run just call
;          qs on a list
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Function: qs
; Use:      this function takes a list and sorts it in
;           the manner of a recursive quicksort
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
(define (qs list)
  (cond ((null? list)
         '())
        (else
         (append (qs (less (car list) (cdr list)))
                 (cons (car list)
                       (qs (great (car list) (cdr list)))) )
         )
  )
)


;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Function: less
; Use:      this function takes an element and a list
;           and construcst a list of elements less than
;           or equal to the element
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
(define (less elem list) 
  (cond ((null? list)
         '())
        ((<= (car list) elem)
         (cons (car list)
               (less elem (cdr list))))
        (else
         (less elem (cdr list)))
   )
)

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Function: great
; Use:      this function takes an element and a list
;           and construcst a list of elements greater than
;           the element
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
(define (great elem list) 
  (cond ((null? list)
         '())
        ((> (car list) elem)
         (cons (car list)
               (great elem (cdr list))))
        (else
         (great elem (cdr list)))
   )
)