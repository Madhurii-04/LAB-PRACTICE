% Facts: Defining family relationships
parent(john, mary).      % John is the parent of Mary
parent(john, mike).      % John is the parent of Mike
parent(susan, mary).     % Susan is the parent of Mary
parent(susan, mike).     % Susan is the parent of Mike
parent(mike, alice).     % Mike is the parent of Alice
parent(mike, bob).       % Mike is the parent of Bob

% Rule to determine if someone is a sibling
sibling(X, Y) :- 
    parent(Z, X), 
    parent(Z, Y), 
    X \= Y.

% Rule to determine if someone is a grandparent
grandparent(X, Y) :- 
    parent(X, Z), 
    parent(Z, Y).

% Rule to determine if someone is a child
child(X, Y) :- 
    parent(Y, X).

% Example queries:
% ?- sibling(mary, mike).
% ?- grandparent(john, alice).
% ?- child(alice, mike).
