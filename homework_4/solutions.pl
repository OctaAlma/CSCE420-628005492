% Octavio Almanza
% UIN: 628005492
% CSCE 420: AI Fall 2023
% Homework 4

% Question 1: Write rules in Prolog to infer various kinship relationships
parent(bart,homer).
parent(bart,marge).
parent(lisa,homer).
parent(lisa,marge).
parent(maggie,homer).
parent(maggie,marge).
parent(homer,abraham).
parent(herb,abraham).
parent(tod,ned).
parent(rod,ned).
parent(marge,jackie).
parent(patty,jackie).
parent(selma,jackie).
female(maggie).
female(lisa).
female(marge).
female(patty). 
female(selma).
female(jackie).
male(bart).
male(homer).
male(herb).
male(burns).
male(smithers).
male(tod).
male(rod).
male(ned).
male(abraham).

% Write rules to define the following relationships: 
% To check that two terms are equal, we use: ==
% To check that two terms are NOTE equal, we use \==
brother(X,Y) :- male(Y), parent(X,Z), parent(Y,Z), X\=Y.

sister(X,Y) :-  female(Y), parent(X,Z), parent(Y,Z), X\=Y.

aunt(X,Y) :- female(Y), parent(X,Z), sister(Z,Y).
uncle(X,Y) :- male(Y), parent(X,Z), brother(Z,Y).

grandfather(X,Y) :- male(Y), parent(X,Z), parent(Z,Y).
grandmother(X,Y) :- female(Y), parent(X,Z), parent(Z,Y).

granddaughter(X,Y) :- female(Y), (grandfather(Y,X); grandmother(Y,X)).

% Ancestor base case:
ancestor(X,Y) :- parent(X,Y).
% Ancestor recursive case:
ancestor(X,Y) :- parent(X,Z), ancestor(Z,Y).

% Question 2: Writing more queries
occupation(joe,oral_surgeon).
occupation(sam,patent_lawyer).
occupation(bill,trial_lawyer).
occupation(cindy,investment_banker).
occupation(joan,civil_lawyer).
occupation(len,plastic_surgeon).
occupation(lance,heart_surgeon).
occupation(frank,brain_surgeon).
occupation(charlie,plastic_surgeon).
occupation(lisa,oral_surgeon).
address(joe,houston).
address(sam,pittsburgh).
address(bill,dallas).
address(cindy,omaha).
address(joan,chicago).
address(len,college_station).
address(lance,los_angeles).
address(frank,dallas).
address(charlie,houston).
address(lisa,san_antonio).
salary(joe,50000).
salary(sam,150000).
salary(bill,200000).
salary(cindy,140000).
salary(joan,80000).
salary(len,70000).
salary(lance,650000).
salary(frank,85000).
salary(charlie,120000).
salary(lisa,190000).

% Some helper rules for question 2
lawyer_types([patent_lawyer, trial_lawyer, civil_lawyer]).
surgeon_types([oral_surgeon, plastic_surgeon, heart_surgeon, brain_surgeon]).
banker_types([investment_banker]).

texas_cities([san_antonio, houston, college_station, dallas]).
california_cities([los_angeles]).
nebraska_cities([omaha]).
pennsylvania_cities([pittsburgh]).
illinois_cities([chicago]).

% query2a: find all lawyers.
query2a(X) :- occupation(X,O), lawyer_types(L), member(O, L).

% query2b: find all surgeons who live in California.
query2b(X) :- occupation(X,O), surgeon_types(S), member(O, S), address(X,A), california_cities(C), member(A,C).

% query2c: find all the surgeons who live in Texas and make over $100,000/yr.
query2c(X) :- occupation(X,O), surgeon_types(D), member(O, D), address(X,A), texas_cities(T), member(A,T), salary(X, S), S > 100000.


% Question 3: Write a predicate canTeach(X,Y) that defines which persons X 
% can teach a class Y a given subject
subject(algebra,math).
subject(calculus,math).
subject(dynamics,physics).
subject(electromagnetism,physics).
subject(nuclear,physics).
subject(organic,chemistry).
subject(inorganic,chemistry).
degree(bill,phd,chemistry).
degree(john,bs,math).
degree(chuck,ms,physics).
degree(susan,phd,math).
retired(bill).

doctorOf(X,Y) :- degree(X, phd, Y).
masterOf(X,Y) :- degree(X, ms, Y).

% Person X can teach a class of subject Y, which requires they have a PhD in field Z
canTeach(X,Y) :- subject(Y,Z), doctorOf(X,Z).

canTeach2(X,Y) :- canTeach(X,Y), \+ retired(X).

canTeach3(X,Y) :- subject(Y,Z), (doctorOf(X,Z); masterOf(X,Z)), \+ retired(X).


% Question 4: Octal Codes

bit(1).
bit(0).

octal_code(A,B,C) :- bit(A), bit(B), bit(C), format('~n~w~w~w~n',[A,B,C]).


% Question 5: Solving the map coloring CSP

color(red).
color(green).
color(blue).

mapcolor(WA,NT,SA,Q,NSW,V,T) :- 
    color(WA), color(NT), color(SA), color(Q), color(NSW), color(V), color(T),
    WA\=NT, WA\=SA,
    NT\=WA, NT\=SA, NT\=Q,
    SA\=WA, SA\=NT, SA\=Q, SA\=NSW, SA\=V,
    Q\=NT, Q\=SA, Q\=NSW,
    NSW\=Q, NSW\=SA, NSW\=V,
    V\=SA, V\=NSW.
