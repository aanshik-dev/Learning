% Part 1.
% 2
max(X, Y, X) :- X >= Y, !.
max(_, Y, Y).

% 3
is_leap_year(Y) :-
    (0 is Y mod 400), !.
is_leap_year(Y) :-
    (0 is Y mod 4),
    (Y mod 100 =\= 0).

% 4
is_prime(2).
is_prime(N) :-
    N > 2,
    \+ has_divisor(N, 2).
has_divisor(N, D) :-
    D * D =< N,
    (N mod D =:= 0 -> ! ;
    D1 is D + 1,
    has_divisor(N, D1)).

% PART 2

% 5
analyse_list([]) :-
    write('This is an empty list.'), nl, !.
analyse_list([H|T]) :-
    write('Head: '), write(H), nl,
    write('Tail: '), write(T), nl, !.
analyse_list(_) :- fail.

% 6
membership(X, [X|_]).
membership(X, [_|T]) :-
    membership(X, T).

% 7
mylength([], 0).
mylength([_|T], N) :-
    mylength(T, N1),
    N is N1 + 1.

% 8
last1([X], X).
last1([_|T], X) :-
    last1(T, X).
last2(List, X) :-
    append(_, [X], List).

% 9
replace([], _, _, []).
replace([Old|T], Old, New, [New|T1]) :-
    replace(T, Old, New, T1), !.
replace([H|T], Old, New, [H|T1]) :-
    replace(T, Old, New, T1).

% 10
palindrome(A) :-
    atom_chars(A, L),
    reverse(L, L).

% 11
element_at([H|_], 1, H) :- !.
element_at([_|T], N, X) :-
    N > 1,
    N1 is N - 1,
    element_at(T, N1, X).

% 12
split_list(_, [], [], []).
split_list(T, [H|Rest], [H|L], G) :-
    H < T,
    split_list(T, Rest, L, G), !.
split_list(T, [H|Rest], L, [H|G]) :-
    split_list(T, Rest, L, G).

% 13
fibonacci(0, 0) :- !.
fibonacci(1, 1) :- !.
fibonacci(N, F) :-
    N > 1,
    N1 is N - 1,
    N2 is N - 2,
    fibonacci(N1, F1),
    fibonacci(N2, F2),
    F is F1 + F2.

% 14
factorial(0, 1).
factorial(N, F) :-
    N > 0,
    N1 is N - 1,
    factorial(N1, F1),
    F is N * F1.

power(_, 0, 1).
power(X, N, P) :-
    N > 0,
    N1 is N - 1,
    power(X, N1, P1),
    P is X * P1.

mysin(_, 0, 0).
mysin(X, N, R) :-
    N > 0,
    N1 is N - 1,
    mysin(X, N1, R1),
    K is N1,
    Sign is (-1) ** K,
    P is 2*K + 1,
    power(X, P, XP),
    factorial(P, F),
    Term is Sign * XP / F,
    R is R1 + Term.

% 15

% -------- FACTS --------
female(mary).
female(sandra).
female(juliet).
female(lisa).

male(peter).
male(paul).
male(dick).
male(bob).
male(harry).

parent(bob, lisa).
parent(bob, paul).
parent(bob, mary).
parent(juliet, lisa).
parent(juliet, paul).
parent(juliet, mary).
parent(peter, harry).
parent(lisa, harry).
parent(mary, dick).
parent(mary, sandra).

% -------- RULES --------
father(F, C) :-
    male(F),
    parent(F, C).

sister(S, P) :-
    female(S),
    parent(X, S),
    parent(X, P),
    S \= P.

grandmother(G, C) :-
    female(G),
    parent(G, X),
    parent(X, C).


% 16
% -------- FACTS --------
born(jan, date(20, 3, 1977)).
born(jeroen, date(2, 2, 1992)).
born(joris, date(17, 3, 1995)).
born(jelle, date(1, 1, 2004)).
born(jesus, date(24, 12, 0)).
born(joop, date(30, 4, 1989)).
born(jannecke, date(17, 3, 1993)).
born(jaap, date(16, 11, 1995)).

% -------- RULES --------

% find people by year
year(Y, Person) :-
    born(Person, date(_, _, Y)).

% check if one date is before another
before(date(D1,M1,Y1), date(D2,M2,Y2)) :-
    (Y1 < Y2) ;
    (Y1 =:= Y2, M1 < M2) ;
    (Y1 =:= Y2, M1 =:= M2, D1 < D2).

% older person
older(P1, P2) :-
    born(P1, Date1),
    born(P2, Date2),
    before(Date1, Date2).

% 17
successor(X, [x|X]).

plus([], Y, Y).
plus([x|T], Y, [x|R]) :-
    plus(T, Y, R).

% 19
remove_duplicates([], []).
remove_duplicates([H|T], R) :-
    member(H, T), !,
    remove_duplicates(T, R).
remove_duplicates([H|T], [H|R]) :-
    remove_duplicates(T, R).

% 20
% -------- FACTS --------
married(peter, lucy).
married(paul, mary).
married(bob, juliet).
married(harry, geraldine).

% -------- RULE --------
single(X) :-
    \+ married(X, _),
    \+ married(_, X).

% 21
gcd(A, 0, A) :- !.
gcd(A, B, G) :-
    B > 0,
    R is A mod B,
    gcd(B, R, G).

% 22
:- op(200, fy, neg).
:- op(400, yfx, and).
:- op(500, yfx, or).
:- op(600, yfx, implies).

% 23
:- op(500, yfx, ++).
:- op(400, yfx, **).

eval_expr(X, X) :- integer(X), !.

eval_expr(A ++ B, V) :-
    eval_expr(A, VA),
    eval_expr(B, VB),
    V is VA + VB + 1.

eval_expr(A ** B, V) :-
    eval_expr(A, VA),
    eval_expr(B, VB),
    V is VA * VB * 2.

% 24
print_square(N, C) :-
    N > 0,
    print_row(N, C),
    N1 is N - 1,
    print_square(N1, C).
print_square(0, _).

print_row(0, _) :- nl.
print_row(N, C) :-
    N > 0,
    write(C),
    N1 is N - 1,
    print_row(N1, C).