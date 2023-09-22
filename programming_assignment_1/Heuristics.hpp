#pragma once
#include "BlockStack.hpp"

extern std::vector< std::list<Block> > goalState;

std::vector<Coords> goalCoords;

// THIS FUNCTION MUST BE CALLED AT THE BEGINNING OF THE PROGRAM AFTER READING IN FILE
void populateGoalCoords(){
    std::list<Block>* currList = nullptr;
    std::list<Block>::iterator currBlock;

    for (int currCol = 0; currCol < goalState.size(); currCol++){
        
        currList = &(goalState.at(currCol));

        int currRow = 0;

        for (currBlock = currList->begin(); currBlock != currList->end(); ++currBlock){
            goalCoords.push_back(Coords(currCol, currRow, currBlock->letter)); 
            currRow++;
        }
    }

}

Coords findInGoal(char letter){
    for (int i = 0; i < goalCoords.size(); i++){
        if (goalCoords.at(i).letter == letter){
            return goalCoords.at(i);
        }
    }
    return Coords();
}

// Returns 0 no matter the state. Admissable since it always underestimates
int const H0(const BlockStack& bs){
    return 0;
}

// Returns the sum of the absolute values of each block's current position - goal position. Not admissable. 
int const H1(const BlockStack& bs){
    std::list<Block> currList;
    std::list<Block>::iterator currBlock;

    int heuristicVal = 0;

    for (int i = 0; i < bs.numCols; i++){
        
        // Create a copy of the list to keep the const 
        currList = (bs.blockColumns.at(i));

        int currRow = 0;
        for (currBlock = currList.begin(); currBlock != currList.end(); ++currBlock){
            Coords currCoord(i, currRow, currBlock->letter);
            Coords inGoal = findInGoal(currBlock->letter);
            
            // The heuristic value will increment by how far each letter is from its respective place
            heuristicVal += currCoord.getDist(inGoal);

            currRow++;
        }
    }

    return heuristicVal;
}

// Returns the number of blocks that are not in the right stack. Admissable
int const H2(const BlockStack& bs){
    std::list<Block> currList;
    std::list<Block>::iterator currBlock;

    int heuristicVal = 0;

    for (int i = 0; i < bs.numCols; i++){
        
        // Create a copy of the list to keep the const 
        currList = (bs.blockColumns.at(i));

        int currRow = 0;
        for (currBlock = currList.begin(); currBlock != currList.end(); ++currBlock){
            Coords currCoord(i, currRow, currBlock->letter);
            Coords inGoal = findInGoal(currBlock->letter);

            if (currCoord.col != inGoal.col){
                heuristicVal++;
            }

            currRow++;
        }
    }

    return heuristicVal;
}

// Returns the number of blocks that are not in the right row. Not admissable
int const H3(const BlockStack& bs){
    std::list<Block> currList;
    std::list<Block>::iterator currBlock;

    int heuristicVal = 0;

    for (int i = 0; i < bs.numCols; i++){
        
        // Create a copy of the list to keep the const 
        currList = (bs.blockColumns.at(i));

        int currRow = 0;
        for (currBlock = currList.begin(); currBlock != currList.end(); ++currBlock){
            Coords currCoord(i, currRow, currBlock->letter);
            Coords inGoal = findInGoal(currBlock->letter);

            if (currCoord.row != inGoal.row){
                heuristicVal++;
            }

            currRow++;
        }
    }

    return heuristicVal;
}

void printStatistics(std::string filename, int iterations, size_t maxQ, int planLen){
    // ‘iters’ is a count of the number of times through the main loop; 
    // ‘maxq’ is the maximum size of the queue. 
    
    // PlanLen represents the number of moves to get to the solution
    // If it is not able to find a solution before reach MAX_ITERS, set planlen to ‘FAILED’.
    std::cout << "Statistics: " << filename << " | Method: ";

    if (HEURISTIC == 0){
        std::cout << "BFS | ";
    }else{
        std::cout << "A* with H" << HEURISTIC << " | ";
    }

    if (planLen == -1){
        std::cout << "Planlen FAILED | ";
    }else{
        std::cout << "Planlen " << planLen << " | ";
    }

    std::cout << "Iter " << iterations << " | ";
    std::cout << "Max queue size: " << maxQ << "\n";
}


bool BlockStack::operator<(BlockStack const& other) const {
    switch(HEURISTIC){
        case 0:
            return (H0(*this) + this->depth) > (H0(other) + other.depth);
        case 1:
            return (H1(*this) + this->depth) > (H1(other) + other.depth);
    }

    return false;
}

int getHeuristicVal(BlockStack const& bs){
    switch(HEURISTIC){
        case 1:
            return (H1(bs) + bs.depth);
        case 2:
            return (H2(bs) + bs.depth);
        case 3:
            return (H3(bs) + bs.depth);
        default: // the default case is H0
            return (H0(bs) + bs.depth);
    }
    return -1;
}

struct compareStacks{
    bool operator()(BlockStack const& b1, BlockStack const& b2){
        switch(HEURISTIC){
            case 1:
                return (H1(b1) + b1.depth) > (H1(b2) + b2.depth);
            case 2:
                return (H2(b1) + b1.depth) > (H2(b2) + b2.depth);
            case 3:
                return (H3(b1) + b1.depth) > (H3(b2) + b2.depth);
            default: // the default case is H0
                return (H0(b1) + b1.depth) > (H0(b2) + b2.depth);
        }
        return false;
    }
};