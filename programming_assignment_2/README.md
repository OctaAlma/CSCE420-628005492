### CSCE 420 - Programming Assignment 2
Octavio Almanza

UIN: 628005492

#### Instructions
To compile the code, open the ``programming_assignment_2`` folder in a terminal and enter: 

```make```

This creates an executable file called ``DPLL``. To run the executable, enter:

```./DPLL <KB-FILENAME> <Literal>* [+UCH]```

 - ``<KB-FILENAME>`` is the location of the ``.cnf`` file and is the only required argument.
 - ``<Literal>*`` enables you to append "facts" into the knowledge base. Each ``<Literal>`` should be space-separated.
 - ``[+UCH]`` option enables the unit clause heuristic. It should always be the **LAST** argument.

#### Important things to note:
 - My truth assignments are the following:
     - ``-1`` is ``NOT SET``
     - ``0`` is ``FALSE``
     - ``1`` is ``TRUE``
 - By default, the DPLL algorithm does NOT use the UCH heuristic.
 - All ``.cnf`` files can be found in the ``CNFs`` directory.
 - All ``.kb`` files can be found in the ``kbScripts`` directory under its respective problem's folder.
 - All transcripts can be found in the ``transcripts`` directory.
 - For any questions or concerns, please contact me at oa5967@tamu.edu
