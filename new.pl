% Facts: Defining family relationships and gender
father(bhairavnath, pragati).
father(bhairavnath, madhuri).
father(bhairavnath, gaurav).

mother(mangal, pragati).
mother(mangal, madhuri).
mother(mangal, gaurav).

% Gender information
male(bhairavnath).
male(gaurav).

female(mangal).
female(pragati).
female(madhuri).

% Rule: Sibling relationship
sibling(X, Y) :-
    father(F, X), father(F, Y),
    mother(M, X), mother(M, Y),
    X \= Y.

% Rule: Parent relationship
parent(P, C) :- father(P, C).
parent(P, C) :- mother(P, C).
