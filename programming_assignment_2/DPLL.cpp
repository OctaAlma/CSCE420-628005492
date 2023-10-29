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
// This will allow copies of the ASSIGNMENT vector to be generated at every DPLL call, preventing
// Previous models from getting assignments
bool DPLL(CNFKnowledgeBase kb, std::vector<ASSIGNMENT> model){
    DPLLcalls++;

    int modelCheck = kb.checkAssignment(model);
    
    if (modelCheck != NOT_SET){
        return modelCheck; // Model check will be true or false
    }

    if (useUCH){
        // apply heuristic
        std::shared_ptr<CNFLiteral> uc = kb.findUnitClause();

        if (uc != NULL){
            // There is a unit clause. Find its index in all literals:
            int ucIndex = kb.getLiteralIndex(uc->literal->name);
            model[ucIndex] = !uc->negated;
            cout << "Forcing " << uc->literal->name << " = " << !uc->negated << " by UCH\n";
            
            return DPLL(kb, model);
        }
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
    
    auto kb = CNFKnowledgeBase();
    kb.loadKB(filename);
    kb.addFacts(argc, argv);
    bool isSatisfiable = DPLL_Satisfiable(kb, NULL);
    cout << "\n";
    
    if (isSatisfiable){
        cout << "Solution (model):\n";
        kb.printAssignments();
        kb.printTruePropositions();
    }else{
        cout << "Unsatisfiable.\n";
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