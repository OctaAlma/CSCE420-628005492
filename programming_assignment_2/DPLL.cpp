#include "DPLL.h"

using namespace std;

bool useUCH = false;
unsigned int DPLLcalls = 0;

bool DPLL_Satisfiable(CNFKnowledgeBase kb, std::shared_ptr<CNFSentence> s){
    
    std::vector<ASSIGNMENT> model = kb.extractModel();

    if (s == NULL){
        return DPLL(kb, model);
    }

    return false;
}

// Note: It is super important that model is pass by copy rather than pass by reference
bool DPLL(CNFKnowledgeBase kb, std::vector<ASSIGNMENT> model){
    DPLLcalls++;

    int modelCheck = kb.checkAssignment(model);
    
    if (modelCheck != NOT_SET){
        return modelCheck; // Model check will be true or false
    }

    if (useUCH){
        // apply heuristic
        // return heuristic
    }

    int unassignedIndex = kb.findUnassignedLiteralIndex();
    string lName = kb.getLiteralName(unassignedIndex);
    
    cout << "Trying " << lName << " = T\n";
    model[unassignedIndex] = TRUE;
    bool withTrue = DPLL(kb, model);
    
    if (withTrue){
        return true;
    }
    
    cout << "Trying " << lName << " = F\n";
    model[unassignedIndex] = FALSE;
    bool withFalse = DPLL(kb, model);

    return withFalse;
}

int main(int argc, char ** argv){

    // If the last argument is "+UCH", use the UC heuristic!
    if ((string)argv[argc-1] == "+UCH"){
        useUCH = true;
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
    bool isSatisfiable = DPLL_Satisfiable(kb, NULL);
    cout << "\n";
    
    if (isSatisfiable){
        cout << "Solution (model):\n";
        kb.printAssignments();
        kb.printTruePropositions();
    }else{

    }

    cout << "Total DPLL calls: " << DPLLcalls << endl;
    cout << "UCH = ";
    if (useUCH == true){
        cout << "True\n";
    }else{
        cout << "False\n";
    }

    return 0;
}