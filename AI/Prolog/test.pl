% % Facts
% concat([], List, List).
% concat([H|T], List2, [H|Res]) :- concat(T, List2, 
%   Res).

% list([1,2,3,4,5,6,7,8,9,10]).
% % ?- list(L), length(L, X).

% % sum
% sum(5+600).

% % ?- sum(X).

big(elephant, horse).
big(horse, donkey).
big(donkey, dog).
big(dog, cat).
big(cat, mouse).

is_bigger(X, Y) :- big(X, Y).
is_bigger(X, Y) :- big(X, Z), is_bigger(Z, Y).
:- write('Hello, have a beautiful day!').