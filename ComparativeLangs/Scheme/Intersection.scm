;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
;     Project:    Intersection.scm
;     Name:       Jonny Hughes
;     Class:      Comparative Programming Languages
;     Proffessor: Dr. Crawley
;     Last Edit:  4/7/20
;                 4/13/20 - fixed Dupes and Sort
;
;    Info: There are two functions defined
;        the first used to find which elems exist in
;        lists. The second finds the intersection of
;        two provided lists
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Function: intersection
; Use:      this function takes two lists and returns
;           a sigle list contating only elements within
;           both of the original lists.
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
(define (intersection list1 list2)
  (cond ((null? list1)
         '())
        ((memberof? (car list1) list2)
         (cons  (car list1)
                (removeAll (car list1) (intersection (cdr list1)  list2))))
        (else
         (qs (intersection (cdr list1) list2)))
        )
  )


;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Function: interDup
; Use:      this function takes two lists and returns
;           a sigle list contating only elements within
;           both of the original lists.
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
(define (interDup list1 list2)
  (cond ((null? list1)
         '())
        ((memberof? (car list1) list2)
         (cons  (car list1)
                (interDup (cdr list1)
                              (removeFirst (car list1) list2))))
        (else
         (interDup (cdr list1) list2))
        )
  )


;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Function: memberof?
; Use:      this function takes an element and a list
;           and returns #t if element is an element of
;           the provided list, #f if it is not.
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
(define (memberof? elem list) 
  (cond ((null? list)
         #f)
        ((eqv? elem (car list))
         #t)
        (else
         (memberof? elem (cdr list)))
        )
  )

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Function: removeAll
; Use:      this function takes an element and a list
;           and returns the list with all occurences of
;           the elem removed
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
(define (removeAll elem list)
  (cond ((null? list)
         '())
        ((eqv? elem (car list))
         (removeAll elem (cdr list)))
        (else
         (cons (car list)
               (removeAll elem (cdr list))))  
    )
  )

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Function: removeFirst
; Use:      this function takes an element and a list
;           and returns the list with the first occurence
;           of the elem removed
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
(define (removeFirst elem list)
  (cond ((null? list)
         '())
        ((eqv? elem (car list))
         (cdr list))
        (else
         (cons (car list)
               (removeFirst elem (cdr list))))  
    )
  )