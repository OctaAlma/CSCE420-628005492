#include <iostream>
#include <vector>
#include <utility>

#include <queue>
#include <string>
#include <unordered_map>

#include "BlockStack.hpp"
#include "Heuristics.hpp"

bool equals(BlockStack & b1, BlockStack & b2){
    if (b1.getKey() == b2.getKey()){
        return true;
    }

    return false;
}

void printMoves(BlockStack goal, BlockStack initialState){
    std::vector<Move> movesMade = goal.movesMade;

    std::cout << "\n<-------- Start Solution Path -------->";

    int currMoveAndCost = 0; // The pathcost == the current move
    int H;

    while (!movesMade.empty()){
        std::cout << std::endl;
        H = getHeuristicVal(initialState);
        std::cout << "Move " << currMoveAndCost << ", Pathcost = " << currMoveAndCost << ", Heuristic = " << H << ", f(n) = g(n)+h(n) = " << currMoveAndCost + H << std::endl;
        initialState.printStacks();
        initialState.moveBlock(movesMade.at(0).sourceCol, movesMade.at(0).destCol);
        movesMade.erase(movesMade.begin() + 0);
        currMoveAndCost++;
    }

    H = getHeuristicVal(initialState);
    std::cout << std::endl;
    std::cout << "Move " << currMoveAndCost << ", Pathcost = " << currMoveAndCost << ", Heuristic = " << H << ", f(n) = g(n)+h(n) = " << currMoveAndCost + H << std::endl;
    initialState.printStacks();

    std::cout << "<--------- End Solution Path --------->\n" << std::endl;

}

// AStar will return a BlockStack object where the movesMade member variable contains all moves necessary to create the solution from the initial state
BlockStack AStar(BlockStack initialState, int maxIters, int& numIters, size_t& maxQ){

    int maxDepth = initialState.stepsForScramble;

    BlockStack GS(goalState);

    std::priority_queue<BlockStack, std::vector<BlockStack>, compareStacks> frontier;
    std::unordered_map<std::string, BlockStack> reached;

    frontier.push(initialState);
    reached[initialState.getKey()] = initialState;

    numIters = 0;
    maxQ = 0;

    while (!frontier.empty() && numIters <= maxIters){
        
        // Update the max queue size if applicable
        if (frontier.size() > maxQ){
            maxQ = frontier.size();
        }

        // Extract the value at the top of the priority queue
        BlockStack currState = frontier.top();
        frontier.pop();

        // Check if the current configuration is equal to the goal state
        if (equals(currState, GS)){
            std::cout << "Success! Goal found." << std::endl;
            return currState;
        }

        if (currState.depth + 1 > maxDepth){
            continue;
        }
        
        // createChildren() is equivalent to the successor() function
        std::vector<BlockStack> children = currState.createChildren();
        
        // Iterate through the created children and check if they should be pushed to the frontier
        for (int i = 0; i < children.size(); i++){

            children.at(i).depth = currState.depth + 1;
            BlockStack* currChild = &(children.at(i));
            std::string childKey = currChild->getKey();

            if (reached.find( childKey ) == reached.end()){
                // The child configuration was not found in reached. Add it to reached and the frontier!
                frontier.push(children.at(i));            
                reached[ childKey ] = *currChild;
            }else{

                // In the case the child is already in reached, check if the one in reached has more moves
                if (reached.find( childKey )->second.movesMade.size() > currChild->movesMade.size()){
                    reached[ childKey ] = *currChild;
                }
            }
        }

        numIters++;
    }

    std::cout << "Could not find solutions under " << maxIters << " iterations.\n";
    return initialState;
}