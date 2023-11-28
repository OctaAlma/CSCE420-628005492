####CSCE 420 Homework 4
#####Octavio Almanza
#####UIN: 62800492

You can view the transcripts for each problem by going to its respective transcript file ``PROB_NUM-transript.txt``, where ``PROB_NUM`` is the problem number.

To consult my ``solution.pl`` file you can either:
- Run GNU prolog from your terminal with the following command: ``gprolog --consult-file solutions.pl``
- Otherwise, you can simply type ``| ?- consult('solutions.pl').`` in ``gprolog``.

**Question 4**: Use back-chaining to explain why the solutions are generated in the order they are. Note that typing ‘;’ after a solution is analogous to reaching a goal on the stack that fails, forcing back-tracking.

My code produces the octal codes in the following order: ``111, 110, 101, 100, 011, 010, 001, 000``.
The reason why the octal codes appear in that order has to do with the way that I have setup my knowlege base and the order in which Prolog assigns values to variables. Since I declare the rule ``bit(1)`` before ``bit(0)``, prolog will assign the value ``1`` to variables before trying the value ``0`` when looking for a solution to a query that states ``bit(X)``. Since Prolog uses depth-first search for its variable assignments, it will assign a value to the next variable before changing the value of the variable it just set. This is why the third bit changes at each octal code, the second bit changes every other octal code, and the first bit changes every four octal codes.