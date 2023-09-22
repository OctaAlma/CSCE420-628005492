#include <iostream>
#include <string>
#include "BlockStack.hpp"
#include "Heuristics.hpp"
#include "AStar.hpp"

using namespace std;

int HEURISTIC = 2;
std::vector< std::list<Block> > goalState;

void makeAllCaps(string& str){
    for (int i = 0; i < str.size(); i++){
        str.at(i) = std::toupper(str.at(i));
    }
}

int main(int argc, char** argv){

    if (argc < 2){
        cout << "\nusage: ./blocksworld FILENAME" << endl;
        cout << "Options:    -H# - specify whether to use heuristic function 0-3";
        cout << "\n            -MAX_ITERS <int> - specify the maximum number of iterations allowed for A*\n";
        cout << "\n            -dp - Do not print out the solution path\n\n";
        exit(0);
    }

    std::string fileName(argv[1]);
    int maxIterations = 1000000; // Default max iterations is 1 million

    bool printPath = true;

    for (int i = 2; i < argc; i++){
        string currArg(argv[i]);

        // capitalize the whole argument
        makeAllCaps(currArg);

        // Makes the -H from -H# into zeroes to parse integer:
        if (currArg.size() == 3){
            if (currArg.at(0) == '-' && currArg.at(1) == 'H'){
                currArg.at(0) = '0';
                currArg.at(1) = '0';
                HEURISTIC = std::stoi(currArg);
            }
        }

        if (currArg == "MAX_ITERS"){
            if ((i + 1) < argc){
                maxIterations = std::stoi(argv[i + 1]);
            }
        }

        if (currArg == "-DP" || currArg == "DP"){ // Don't print out the path
            printPath = false;
        }
    }

    BlockStack initialState("./probs/" + fileName, goalState);

    populateGoalCoords(); // Must be called BEFORE calling A*

    int iterations;
    size_t maxQ;

    BlockStack solution = AStar(initialState, maxIterations, iterations, maxQ);

    if (!solution.movesMade.empty()){
        if (printPath){
            printMoves(solution, initialState);
        }
        printStatistics(fileName, iterations, maxQ, solution.movesMade.size());
    }else{
        printStatistics(fileName, iterations, maxQ, -1);
    }

}