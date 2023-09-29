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

// Returns the sum of the absolute values of each block's current position - goal position. 
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

// Returns the number of blocks that are not in the right stack.
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

// Returns the number of blocks that are not in the right row.
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

// Returns the number of blocks that are not in the right position. 
int const H4(const BlockStack& bs){
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

            if (currCoord.col != inGoal.col || currCoord.row != inGoal.row){
                heuristicVal++;
            }

            currRow++;
        }
    }

    return heuristicVal;
}

/* Same as H4 but it also looks at the block below the current block (if applicable) 
and increments the heuristic value if the block below is not in the correct position.*/
int const H5(const BlockStack& bs){
    int heuristicVal = 0;

    std::list<Block> currList;
    std::list<Block>::iterator currBlock, prevBlock;
    
    Coords prevGoalCoords, prevCoords;

    for (int i = 0; i < bs.numCols; i++){
        
        // Create a copy of the list to keep the const 
        currList = (bs.blockColumns.at(i));

        int currRow = 0;
        for (currBlock = currList.begin(); currBlock != currList.end(); ++currBlock){
            Coords currCoord(i, currRow, currBlock->letter);
            Coords inGoal = findInGoal(currBlock->letter);
            
            // If the current block is not in the correct position, increment the heuristic value by 1
            bool currBlockInRightPos = (currCoord.col == inGoal.col) && (currCoord.row == inGoal.row);
            if (!currBlockInRightPos){
                heuristicVal++;
            }

            // if there is a block below the current block, check if it is in the correct place
            // If the block below is not in the correct place, increment the heuristic value by 1
            if (!(currList.size() == 1 || currBlock == currList.begin())){
                bool prevBlockInRightPos = (prevGoalCoords.col == prevCoords.col) && (prevGoalCoords.row == prevCoords.row);
                if (!prevBlockInRightPos){
                    heuristicVal++;
                }
            }

            prevGoalCoords = inGoal;
            prevCoords = currCoord;
            currRow++;
        }
    }

    return heuristicVal;
}

/* Will return the number of blocks in all stacks - the number of continuous blocks in the 
correct place from the bottom to the stop of each stack.*/
int const H6(const BlockStack& bs){
    int heuristicVal = goalCoords.size();

    std::list<Block> currList;
    std::list<Block>::iterator currBlock;

    for (int i = 0; i < bs.numCols; i++){
        
        // Create a copy of the list to keep the const 
        currList = (bs.blockColumns.at(i));

        int currRow = 0;
        for (currBlock = currList.begin(); currBlock != currList.end(); ++currBlock){
            Coords currCoord(i, currRow, currBlock->letter);
            Coords inGoal = findInGoal(currBlock->letter);

            if (currCoord.col == inGoal.col && currCoord.row == inGoal.row){
                heuristicVal--;
            }else{
                break;
            }

            currRow++;
        }
    }

    return heuristicVal;
}

/* Same as H6, but it also increments the heuristic if it finds blocks that are
stuck under a block that belongs in the current stack. */
int const H7(const BlockStack& bs){
    int heuristicVal = goalCoords.size();

    std::list<Block> currList;
    std::list<Block>::iterator currBlock;

    for (int i = 0; i < bs.numCols; i++){
        
        // Create a copy of the list to keep the const 
        currList = (bs.blockColumns.at(i));

        int currRow = 0;
        for (currBlock = currList.begin(); currBlock != currList.end(); ++currBlock){
            Coords currCoord(i, currRow, currBlock->letter);
            Coords inGoal = findInGoal(currBlock->letter);

            if (currCoord.col == inGoal.col && currCoord.row == inGoal.row){
                heuristicVal--;
            }else{
                break;
            }

            currRow++;
        }

        // Count the number of stuck blocks in the current stack:
        currRow = 0;
        for (currBlock = currList.begin(); currBlock != currList.end(); ++currBlock){
            Coords currCoord(i, currRow, currBlock->letter);
            Coords inGoal = findInGoal(currBlock->letter);

            // Check if the current block is stuck between
            if ((currBlock!=currList.end()) && (inGoal.col != currCoord.col)){
                std::list<Block>::iterator topBlock = currList.begin();
                std::advance(topBlock, currRow + 1);

                Coords topBlockGoalCoords = findInGoal(topBlock->letter);
                // Check if the topBlock is the correct stack. If so, this is bad for the current block, so we increase the heuristic
                if (topBlockGoalCoords.col == (i)){
                    heuristicVal += (currList.size() - currRow); // Add the depth of the current block rather than just 1
                }

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
    std::cout << "Max queue size: " << maxQ << "\n\n";


}

void printStatisticsCSV(std::string filename, int iterations, size_t maxQ, int planLen){
    std::cout << filename << "," << HEURISTIC << "," << planLen << "," << iterations << "," << maxQ << "\n";
}


bool BlockStack::operator<(BlockStack const& other) const {
    switch(HEURISTIC){
        case 0:
            return (H0(*this) + this->depth) > (H0(other) + other.depth);
        case 1:
            return (H1(*this) + this->depth) > (H1(other) + other.depth);
        case 2:
            return (H2(*this) + this->depth) > (H2(other) + other.depth);
        case 3:
            return (H3(*this) + this->depth) > (H3(other) + other.depth);
        case 4:
            return (H4(*this) + this->depth) > (H4(other) + other.depth);
        case 5:
            return (H5(*this) + this->depth) > (H5(other) + other.depth);
        case 6:
            return (H6(*this) + this->depth) > (H6(other) + other.depth);
        case 7:
            return (H7(*this) + this->depth) > (H7(other) + other.depth);
        default:
            return (H5(*this) + this->depth) > (H5(other) + other.depth);
    }

    return false;
}

int getHeuristicVal(BlockStack const& bs){
    switch(HEURISTIC){
        case 0:
            return (H0(bs));
        case 1:
            return (H1(bs));
        case 2:
            return (H2(bs));
        case 3:
            return (H3(bs));
        case 4:
            return (H4(bs));
        case 5:
            return (H5(bs));
        case 6:
            return (H6(bs));
        case 7:
            return (H7(bs));
        default: // the default case is H5
            return (H5(bs));
    }
    return -1;
}

struct compareStacks{
    bool operator()(BlockStack const& b1, BlockStack const& b2){
        switch(HEURISTIC){
            case 0: 
                return (H0(b1) + b1.depth) > (H0(b2) + b2.depth); 
            case 1:
                return (H1(b1) + b1.depth) > (H1(b2) + b2.depth);
            case 2:
                return (H2(b1) + b1.depth) > (H2(b2) + b2.depth);
            case 3:
                return (H3(b1) + b1.depth) > (H3(b2) + b2.depth);
            case 4:
                return (H4(b1) + b1.depth) > (H4(b2) + b2.depth);
            case 5:
                return (H5(b1) + b1.depth) > (H5(b2) + b2.depth);
            case 6:
                return (H6(b1) + b1.depth) > (H6(b2) + b2.depth);
            case 7:
                return (H7(b1) + b1.depth) > (H7(b2) + b2.depth);
            default: // the default case is H5
                return (H5(b1) + b1.depth) > (H5(b2) + b2.depth);
        }
        return false;
    }
};