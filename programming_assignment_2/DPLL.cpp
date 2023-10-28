#include "DPLL.h"

using namespace std;

bool useUCH = false;

bool DPLL_Satisfiable(CNFKnowledgeBase kb, std::shared_ptr<CNFSentence> s){
    
    std::vector<ASSIGNMENT> model = kb.extractModel();

    if (s == NULL){
        return DPLL(kb, model);
    }

    return false;
}

// Note: It is super important that model is pass by copy rather than pass by reference
bool DPLL(CNFKnowledgeBase kb, std::vector<ASSIGNMENT> model){
    
    int modelCheck = kb.checkAssignment(model);
    
    if (modelCheck != NOT_SET){
        return modelCheck; // Model check will be true or false
    }

    if (useUCH){
        // apply heuristic
        // return heuristic
    }

    int unassignedIndex = kb.findUnassignedLiteralIndex();
    
    model[unassignedIndex] = TRUE;
    bool withTrue = DPLL(kb, model);

    if (withTrue){
        return true;
    }

    model[unassignedIndex] = FALSE;
    bool withFalse = DPLL(kb, model);

    return withFalse;
}

int main(int argc, char ** argv){

    // If the last argument is "+UCH", use the UC heuristic!
    if ((string)argv[argc-1] == "+UCH"){
        useUCH = true;
        cout << "Using UCH...\n";
    }else{
        cout << "NOT using UCH...\n";
    }

    if (argc == 1){
        cout << "Usage: ./DPLL <KB-FILENAME> <FACTS>* <+UCH>*";
        exit(0);
    }

    string filename = argv[1];

    cout << "Filename = " << filename << endl;

    auto kb = CNFKnowledgeBase();
    kb.loadKB(filename);
    kb.addFacts(argc, argv);
    
    kb.printKB();

    cout << DPLL_Satisfiable(kb, NULL) << endl;
    kb.printAssignments();
}