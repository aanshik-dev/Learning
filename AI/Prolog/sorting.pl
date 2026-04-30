% bubble_sort 
bubble_sort(List, Sorted) :-
    swap(List, Temp),
    !,
    bubble_sort(Temp, Sorted).
bubble_sort(List, List).
swap([X, Y | T], [Y, X | T]) :-
    X > Y.
swap([H | T], [H | T1]) :-
    swap(T, T1).


% Insertion Sort
insertion_sort([], []).
insertion_sort([H|T], Sorted) :-
    insertion_sort(T, Temp),
    insert(H, Temp, Sorted).

insert(X, [], [X]).
insert(X, [H|T], [X,H|T]) :-
    X =< H.
insert(X, [H|T], [H|T1]) :-
    X > H,
    insert(X, T, T1).

% Selection Sort 
selection_sort([], []).
selection_sort(List, [Min|Sorted]) :-
    min_elem(List, Min),
    remove_one(Min, List, Rest),
    selection_sort(Rest, Sorted).

min_elem([X], X).
min_elem([H|T], Min) :-
    min_elem(T, MinT),
    (H < MinT -> Min = H ; Min = MinT).

remove_one(X, [X|T], T).
remove_one(X, [H|T], [H|T1]) :-
    remove_one(X, T, T1).

% Merge Sort
merge_sort([], []).
merge_sort([X], [X]).
merge_sort(List, Sorted) :-
    split(List, L1, L2), !,
    merge_sort(L1, S1),
    merge_sort(L2, S2),
    merge(S1, S2, Sorted).
split([], [], []).
split([X], [X], []).
split([X,Y|T], [X|T1], [Y|T2]) :-
    split(T, T1, T2).

merge([], L, L).
merge(L, [], L).
merge([H1|T1], [H2|T2], [H1|T]) :-
    H1 =< H2,
    merge(T1, [H2|T2], T).
merge([H1|T1], [H2|T2], [H2|T]) :-
    H1 > H2,
    merge([H1|T1], T2, T).

% quick_sort
quick_sort([], []).
quick_sort([H|T], Sorted) :-
    partition(H, T, L, G),
    quick_sort(L, SL),
    quick_sort(G, SG),
    append(SL, [H|SG], Sorted).

partition(_, [], [], []).
partition(P, [H|T], [H|L], G) :-
    H =< P,
    partition(P, T, L, G).
partition(P, [H|T], L, [H|G]) :-
    H > P,
    partition(P, T, L, G).

% Builtin 
% ?- sort([3,1,2,1], X).
% X = [1,2,3].