#pragma once
#ifndef BLOCKSTACK
#define BLOCKSTACK

#include <iostream>
#include <list>
#include <utility>
#include <string>
#include <fstream>
#include <sstream>

extern int HEURISTIC;

struct Block{
    char letter;
    int currCol;

    Block(){
        letter = '-';
        currCol = -1;
    }

    Block(char Letter, int col){
        letter = Letter;
        currCol = col;
    }
};

struct Coords{
    int col;
    int row;
    char letter;

    Coords(){
        col = row = -1;
        letter = '\0';
    }

    Coords(int Col, int Row, char Letter){
        this->col = Col;
        this->row = Row;
        this->letter = Letter;
    }

    int getDist(Coords &other){
        return abs(other.col - this->col) + abs(other.row - this->row);
    }
};

struct Move{
    int sourceCol;
    int destCol;
    char letter;

    Move(int Source, int Dest, char Letter):sourceCol(Source), destCol(Dest), letter(Letter){}

    void printMove(){
        std::cout << "Moved letter " << letter << " from " << sourceCol << " to " << destCol << std::endl;
    }
};

class BlockStack{
    public:

    int depth;
    int numCols; // Represents the number of stacks in the object
    int numBlocks; // Represents the number of Block objects in all stacks
    int stepsForScramble; // Obtained from the input file. Represents an upper bound for the total number of steps in the optimal solution

    std::vector< std::list<Block> > blockColumns;

    std::vector<Move> movesMade; // Keep track of the moves done!

    BlockStack(){
        depth = 0;
        numCols = -1;
        numBlocks = -1;
        stepsForScramble = -1;
    }

    BlockStack(std::string Filename, std::vector< std::list<Block> >& goalState);
    BlockStack(std::vector< std::list<Block> >& blockListVec);
    BlockStack(BlockStack* other);

    void moveBlock(char blockLetter, int col);
    void moveBlock(int col1, int col2);

    void printStacks();
    void printGoal(std::vector< std::list<Block> >& goalState);

    // Returns the coordinate if a letter is in a block stack. returns -1 otherwise
    Coords findLetter(char letter);

    std::vector<BlockStack> createChildren();

    // The key will be a string containing the order of the letters in the stacks
    std::string getKey();

    // Comparison operators
    bool operator<(const BlockStack& other) const;
    
    bool operator==(const BlockStack& other) const;

};

#endif