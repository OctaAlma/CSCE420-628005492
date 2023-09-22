#include "BlockStack.hpp"

using std::cout;
using std::endl;
using std::cerr;

BlockStack::BlockStack(std::string Filename, std::vector< std::list<Block> >& goalState){
    this->movesMade.clear();
    this->blockColumns.clear();
    this->depth = 0;
    
    std::ifstream inputFile;
    std::string line;

    inputFile.open(Filename);

    if (inputFile.is_open()){
        inputFile >> this->numCols;
        inputFile >> this->numBlocks;
        inputFile >> this->stepsForScramble;

        // Get the \n character
        std::getline(inputFile, line);
        // Get the >>>>> line:
        std::getline(inputFile, line);

    }else{
        std::cout << "Unable to open file " << Filename << std::endl;
        exit(0);
    }

    char currBlockLetter;

    for (int currCol = 0; currCol < this->numCols; currCol++){
        // Add a new linked list to the vector
        this->blockColumns.push_back(std::list<Block>());
        
        getline(inputFile, line);
        std::stringstream ss(line);
        
        while (!ss.eof()){
            ss >> currBlockLetter;
            
            if (ss.eof()){
                break;
            }

            Block b(currBlockLetter, currCol);

            blockColumns.at(currCol).push_back(b);
        }
    }

    // Get the >>>>> line:
    std::getline(inputFile, line);
    
    // Create the goal state
    for (int currCol = 0; currCol < this->numCols; currCol++){
        // Add a new linked list to the vector
        goalState.push_back(std::list<Block>());
        
        getline(inputFile, line);
        std::stringstream ss(line);
        
        while (!ss.eof()){
            ss >> currBlockLetter;
            
            if (ss.eof()){
                break;
            }

            Block b(currBlockLetter, currCol);

            goalState.at(currCol).push_back(b);
        }
    }

    inputFile.close();

    // Note: since we are reading a file that does not contain any move information, movesMade cannot be populated.
}

Coords BlockStack::findLetter(char letter){
    std::list<Block>* currList = nullptr;

    for (int currCol= 0; currCol< this->numCols; currCol++){
        currList = &(this->blockColumns.at(currCol));

        std::list<Block>::iterator currBlock;
        
        int currRow = 0;

        for (currBlock = currList->begin(); currBlock != currList->end(); ++currBlock){
            if (currBlock->letter == letter){
                return Coords(currCol, currRow, letter);
            }
            currRow++;
        }
    }

    // IF the letter is not found, return -1 Coords
    return Coords(-1,-1,'\0');

}

BlockStack::BlockStack(std::vector< std::list<Block> >& blockListVec){
    this->movesMade.clear();
    this->blockColumns.clear();
    this->depth = 0;

    std::list<Block>* currList = nullptr;

    this->numBlocks = 0;
    this->numCols = blockListVec.size();

    for (int i = 0; i < blockListVec.size(); i++){

        this->blockColumns.push_back(std::list<Block>());
        currList = &blockListVec.at(i);

        std::list<Block>::iterator currBlock;

        for (currBlock = currList->begin(); currBlock != currList->end(); ++currBlock){
            this->blockColumns.at(i).push_back(Block(currBlock->letter, currBlock->currCol));
            this->numBlocks++;
        }
    }

    // Since we are making a blockStack off of a vector of lists of blocks, there is no "moves made" to copy
}

BlockStack::BlockStack(BlockStack* other){
    this->movesMade.clear();
    this->blockColumns.clear();
    this->depth = 0;

    std::vector< std::list<Block> >/*&*/ blockListVec = other->blockColumns;
    
    std::list<Block>* currList = nullptr;

    this->numBlocks = 0;
    this->numCols = blockListVec.size();
    this->stepsForScramble = other->stepsForScramble;

    // Copy over the 
    for (int i = 0; i < blockListVec.size(); i++){

        this->blockColumns.push_back(std::list<Block>());
        currList = &blockListVec.at(i);

        std::list<Block>::iterator currBlock;

        for (currBlock = currList->begin(); currBlock != currList->end(); ++currBlock){
            this->blockColumns.at(i).push_back(Block(currBlock->letter, currBlock->currCol));
            this->numBlocks++;
        }
    }

    // Copy over the moves made for other:
    int SourceCol, DestCol;
    char Letter;
    for (int i = 0; i < other->movesMade.size(); i++){
        SourceCol = other->movesMade.at(i).sourceCol;
        DestCol = other->movesMade.at(i).destCol;
        Letter = other->movesMade.at(i).letter;
        this->movesMade.push_back(Move(SourceCol, DestCol, Letter));
    }
}

void BlockStack::moveBlock(char blockLetter, int col){

    Block* moveMe = nullptr;
    int removeMeCol = -1;

    for (int i = 0; i < this->numCols; i++){
        if (this->blockColumns.at(i).back().letter == blockLetter){
            moveMe = &this->blockColumns.at(i).back();
            removeMeCol = i;
            break;
        }   
    }

    if (moveMe == nullptr){
        cerr << "Block with letter " << blockLetter << " not found.\n";
        return; 
    }

    else if (col >= this->numCols){
        cerr << "Cannot move " << blockLetter << " to stack " << col << ".\nNumber of stacks = " << this->numCols << endl;
        return;
    }

    else{
        // Update the object's movesMade vector to include this move
        movesMade.push_back(Move(removeMeCol, col, blockLetter));
        
        blockColumns.at(col).push_back(*moveMe);
        blockColumns.at(removeMeCol).pop_back();

        // Update the moved block's currCol attribute
        blockColumns.at(col).back().currCol = col;
    }

}

// Move the top block from source column to dest column
void BlockStack::moveBlock(int source, int dest){

    Block* moveMe = nullptr;
    int removeMeCol = -1;

    if (source >= 0 && source < this->blockColumns.size() && dest >= 0 && dest < this->blockColumns.size() ){
        
        moveMe = &this->blockColumns.at(source).back();
        
        // Update the object's movesMade vector to include this move
        char blockLetter = moveMe->letter;
        movesMade.push_back(Move(source, dest, blockLetter));
        
        blockColumns.at(dest).push_back(*moveMe);
        this->blockColumns.at(source).pop_back();

        // Update the moved block's currCol attribute
        blockColumns.at(dest).back().currCol = dest;
    }else{
        std::cout << "Could not move block from col " << source << " to col " << dest << std::endl; 
    }
}

std::vector<BlockStack> BlockStack::createChildren(){
    std::vector<BlockStack> children;

    // Create an identical blockstack with each of the top blocks going to different rows
    std::list<Block>* currList = nullptr;

    // the currCol is the column containing the block that will be moved to other columns
    for (int currCol = 0; currCol< this->numCols; currCol++){

        // If the current column is empty, there will be nothing to move
        // Continue if the current column has nothing to move
        if (this->blockColumns.at(currCol).empty()){
            continue;
        }

        int destCol = (currCol + 1) % this->numCols;
        for (int i = 0; i < this->numCols - 1; i++){
            
            BlockStack duplicate(this);

            duplicate.moveBlock(currCol, destCol);

            children.push_back(duplicate);

            destCol = (destCol + 1) % this->numCols;
        }
    }

    // IF the letter is not found, return -1 Coords
    return children;
}


void BlockStack::printStacks(){
    std::list<Block>* currList = nullptr;
        
    for (int i = 0; i < this->numCols; i++){
        if (i < 10){
            cout << i << " |";
        }else{
            cout << i << "|";
        }

        currList = &this->blockColumns.at(i);
                
        std::list<Block>::iterator currBlock;

        for (currBlock = currList->begin(); currBlock != currList->end(); ++currBlock){
            cout << currBlock->letter << " ";
        }

        cout << endl;
    }
}

void BlockStack::printGoal(std::vector< std::list<Block> >& goalState){
    for (int i = 0; i < this->numCols; i++){
        
        std::list<Block>* currList = &goalState.at(i);
        
        std::list<Block>::iterator currBlock;

        for (currBlock = currList->begin(); currBlock != currList->end(); ++currBlock){
            cout << currBlock->letter << " ";
        }

        cout << endl;
    }
}

std::string BlockStack::getKey(){
    std::string Key = "";

    for (int currCol = 0; currCol < blockColumns.size(); currCol++){
        std::list<Block>::iterator currBlock = this->blockColumns.at(currCol).begin();
        while (currBlock != this->blockColumns.at(currCol).end()){
            Key.push_back(currBlock->letter);
            ++currBlock;
        }

        Key.push_back('\t');
    }

    //std::cout << "The key is " << Key << std::endl;

    return Key;
}

// The operator will only return true IF the ordering of the blocks is identical. 
// It DOES NOT take into account the number of moves it took to reach the state
bool BlockStack::operator==(const BlockStack& other) const{

    // Ensure they match in terms of numCols, numBlocks, and number of stacks 
    if (this->numCols != other.numCols || this->numBlocks != other.numBlocks || this->blockColumns.size() != other.blockColumns.size()){
        return false;
    }

    // Check each stack column and ensure they are of the same size and have the same letters
    for (int i = 0; i < this->blockColumns.size() /*<--they are both the same size*/; i++){
        if (this->blockColumns.at(i).size() != other.blockColumns.at(i).size()){
            return false;
        }

        // Create copies of the blockColumns of each object so that we can keep the "const" attribute
        std::vector<std::list<Block> > thisBsCopy = this->blockColumns;       
        std::vector<std::list<Block> > otherBsCopy = other.blockColumns;       

        // If they are of the same size, check the contents:
        std::list<Block>::iterator currThisBlock = thisBsCopy.at(i).begin();
        std::list<Block>::iterator currOtherBlock = otherBsCopy.at(i).begin();

        for (int j = 0; j < this->blockColumns.at(i).size(); j++){
            if (currThisBlock->letter != currOtherBlock->letter){
                return false;
            }
            ++currThisBlock;
            ++currOtherBlock;
        }
    }

    return true;

}


