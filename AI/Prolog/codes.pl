% Reverse
reverse_list([], []).
reverse_list([H|T], Rev) :-
    reverse_list(T, Temp),
    append(Temp, [H], Rev).

% Permutation
permut([], []). % permutation of empty is empty.
permut(List, [Elem | Permut]) :-
  select(Elem, List, Rest), % Select an element 
  permut(Rest, Permut). % Permute the rest

% Length of list
list_length([], 0).
list_length([_|T], N) :-
    list_length(T, N1),
    N is N1 + 1.

% palindrome
palindrome(List) :-
    reverse(List, List).

% Factorial
factorial(0, 1).
factorial(N, F) :-
    N > 0,
    N1 is N - 1,
    factorial(N1, F1),
    F is N * F1.

% Fibonacci
fib(0, 0).
fib(1, 1).
fib(N, F) :-
    N > 1,
    N1 is N - 1,
    N2 is N - 2,
    fib(N1, F1),
    fib(N2, F2),
    F is F1 + F2.

% Max Element
max_list([X], X).
max_list([H|T], Max) :-
    max_list(T, MaxT),
    (H > MaxT -> Max = H ; Max = MaxT).

% Sum of list
sum_list([], 0).
sum_list([H|T], Sum) :-
    sum_list(T, S1),
    Sum is H + S1.

% Check if number is even
is_even(N) :-
    0 is N mod 2.

% Last Element
last_element([X], X).
last_element([_|T], X) :-
    last_element(T, X).

% Count occurence
count(_, [], 0).
count(X, [X|T], N) :-
    count(X, T, N1),
    N is N1 + 1.
count(X, [_|T], N) :-
    count(X, T, N).

% Member
my_member(X, [X|_]).
my_member(X, [_|T]) :-
    my_member(X, T).

% GCD
gcd(X, 0, X).
gcd(X, Y, G) :-
    Y > 0,
    R is X mod Y,
    gcd(Y, R, G).

% Concatenate
concat([], List, List).
concat([H|T], List2, [H|Res]) :- concat(T, List2, Res).

% Power
power(_, 0, 1).
power(X, N, P) :-
    N > 0,
    N1 is N - 1,
    power(X, N1, P1),
    P is X * P1.

% Prime
is_prime(2).
is_prime(N) :-
    N > 2,
    \+ has_divisor(N, 2).
has_divisor(N, D) :-
    D * D =< N,
    (N mod D =:= 0 -> ! ;
    D1 is D + 1,
    has_divisor(N, D1)).

% Flatten
flatten_list([], []).
flatten_list([H|T], Flat) :-
    is_list(H),
    flatten_list(H, FH),
    flatten_list(T, FT),
    append(FH, FT, Flat).
flatten_list([H|T], [H|FT]) :-
    \+ is_list(H),
    flatten_list(T, FT).

% Remove duplicate
remove_duplicates([], []).
remove_duplicates([Head | Tail], Result) :- 
  member(Head, Tail),!,   % If Head duplicate..
  remove_duplicates(Tail, Result). % discard Head, process Tail.
remove_duplicates([Head | Tail], [Head | Result]) :-
  % Head is NOT a member of Tail 
  remove_duplicates(Tail, Result). % keep Head, process Tail

% Add element to list
add(Element, List, Result) :- 
    member(Element, List), !, 
    Result = List.
add(Element, List, [Element | List]).

% Subset
subset([], []).
subset([H|T], [H|Sub]) :-
  subset(T, Sub).
subset([_|T], Sub) :-
  subset(T, Sub).

% Subset Sum
subset_sum([], 0).
subset_sum([H|T], Sum) :-
  subset_sum(T, Sum1),
  Sum is Sum1 + H.
subset_sum([_|T], Sum) :-
  subset_sum(T, Sum).

% Subset Sum list
subset_sum_list([], 0, []).
subset_sum_list([H|T], Sum, [H|Sub]) :-
    subset_sum_list(T, Sum1, Sub),
    Sum is Sum1 + H.
subset_sum_list([_|T], Sum, Sub) :-
    subset_sum_list(T, Sum, Sub).