#include "DPLL.h"

using namespace std;

bool DPLL_Satisfiable(CNFKnowledgeBase kb, std::shared_ptr<CNFSentence> s){
    return false;
}

bool DPLL(CNFKnowledgeBase kb, std::vector<ASSIGNMENT> model){
    
    int modelCheck = kb.checkAssignment(model);
    if (modelCheck == TRUE){
        return true;
    }else if (modelCheck == FALSE){
        return false;
    }

    
    
    return false;
}

int main(int argc, char ** argv){

    bool useUCH = false;
    // If the last argument is "+UCH", use the UC heuristic!
    if ((string)argv[argc-1] == "+UCH"){
        useUCH = true;
        cout << "Using UCH...\n";
    }else{
        cout << "NOT using UCH...\n";
    }

    auto kb = CNFKnowledgeBase();
    kb.loadKB("./dimacsFiles/t1.dm");
}