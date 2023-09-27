The code requires standard C++ libraries.
Note: The code was tested on my compute.cs.edu server.
       - The g++ version on my server was 4.8.5
       - I specify the use of the C++11 standard on my makefile

To compile the code, simply enter "make" while inside the programming_assignment_1 folder.

Once the code is compiled, run it using the following format:

./blocksworld FILENAME -H# dp
    - For FILENAME, only put the name of the file in the probs folder. DO NOT SPECIFY the path.
    - The optional -H# specifies the heuristic to use. Please type "-H3" when specifying. If not specified, heuristic 4 will be used. # must range from 0-6.
    - The optional dp tells the program to NOT print the 
