Octavio Almanza

The code requires standard C++ libraries.
Note: The code was tested on my compute.cs.edu server.
       - The g++ version on my server was 4.8.5
       - I specify the use of the C++11 standard on my makefile
       - Some of the performance metrics I got on the server did not match the ones on my computer.
         I ran the same code on both machines and would sometimes get better results on my macbook and sometimes on the server.

To compile the code, simply enter "make" while inside the programming_assignment_1 folder.

Once the code is compiled, run it using the following format:

    ./blocksworld FILENAME

    - For FILENAME, only put the name of the file in the probs folder. DO NOT SPECIFY the path.

The program also features the following options:
    
    - The option -H <int> specifies the heuristic the program should use. 
      If not specified, heuristic 5 will be used. # should range from 0-7.
      When specifying, please type "-H#" (e.g -H2).
    
    - The option -dp tells the program to NOT print the solution path in the terminal if a solution is found.

    - The option -MAX_ITERS <int> specifies the maximum number of iterations that should be attempted by A*. 
      Default is 1,000,000

For any questions regarding the implementation, please contact me at oa5967@tamu.edu
