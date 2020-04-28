childof(bob,adam).
childof(carl, bob).
childof(don, carl).
childof(ed, don).
childof(frank, ed).
childof(greg, frank).

male(carl).
female(mary).

descendentof(A, B) :- childof(A,B).
descendentof(A, B) :- childof(X, B), descendentof(A, X).
