#include "KnowledgeBase.h"

using namespace std;

void printSentence(shared_ptr<CNFSentence> s){
    cout << "[ ";

    for (auto l = s->literals.begin(); l != s->literals.end(); l++){
        
        if ((*l)->negated){
            cout << "not ";    
        }

        cout << (*l)->name;

        if (l != (s->literals.end() - 1)){
            cout << ", ";
        }else{
            cout << " ";
        }
    }
    
    cout << "]\n";
}

void CNFKnowledgeBase::loadKB(std::string filename){
    ifstream kbFile(filename);
    string currLine;

    string currLiteralName;
    bool negated = false;

    while(std::getline(kbFile, currLine)) {
        istringstream ss(currLine);
        
        // Parse through each word at each line and create "CNFLiteral" objects
        auto newSentence = make_shared<CNFSentence>();

        while(!ss.eof()){
            ss >> currLiteralName;

            if (ss.fail()){
                continue;
            }

            // check if the literal is negated:
            if (currLiteralName.at(0) == '-'){
                // Delete the first character of the string
                currLiteralName.erase(0, 1);
                negated = true;
            }else{
                negated = false;
            }

            if (find(literalNames.begin(), literalNames.end(), currLiteralName) == literalNames.end()){
                literalNames.push_back(currLiteralName);
            }
            
            auto newLiteral = make_shared<CNFLiteral>(currLiteralName, negated);
            newSentence->literals.push_back(newLiteral);
        }
        
        this->sentences.push_back(newSentence);
        printSentence(newSentence);
    }
}

// Used to add facts/independent literals into the knowledge base
void CNFKnowledgeBase::addLiteral(std::string literalName){
    auto l = make_shared<CNFLiteral>();

    if (literalName.at(0) == '-'){
        literalName.erase(0, 1);
        l->negated = true;
    }else{
        l->negated = false;
    }

    l->name = literalName;
    l->assign = NOT_SET;

    if (find(literalNames.begin(), literalNames.end(), literalName) == literalNames.end()){
        literalNames.push_back(literalName);
    }

    auto s = make_shared<CNFSentence>();
    s->literals.push_back(l);
    sentences.push_back(s);
}

void CNFKnowledgeBase::addLiterals(int argc, char** argv){
    for (int i = 0; i < argc; i++){
        string currLiteralName = argv[i];

        if (currLiteralName == "+UCH"){
            continue;
        }

        addLiteral(currLiteralName);
    }
}

void CNFKnowledgeBase::assignModel(std::vector<ASSIGNMENT>& model){
    if (model.size() != literalNames.size()){
        cout << "The size of the provided model does not match the number of literals: \n";
        cout << "Size of model: " << model.size() << endl;
        cout << "Number of literals: " << literalNames.size() << endl;
        return;
    }

    size_t n = model.size(); // The number of literals
    size_t n_s = this->sentences.size(); // The number of sentences

    for (int i = 0; i < n; i++){
        auto currLiteralName = literalNames.at(i);
        ASSIGNMENT a = model.at(i);

        for (int j = 0; j < n_s; j++){
            auto currSentence = sentences[j];

            for (int k = 0; k < currSentence->literals.size(); k++){
                auto currLiteral = currSentence->literals.at(k);
                if (currLiteral->name == currLiteralName){
                    if (currLiteral->negated){
                        if (a == TRUE){
                            currLiteral->assign = FALSE;
                        }
                        else if (a == FALSE){
                            currLiteral->assign = TRUE;
                        }
                        else{
                            currLiteral->assign = NOT_SET;
                        }

                    }else{
                        currLiteral->assign = a;
                    }
                }
            }
        }
    }
}

// Every index in model T corresponds to the assignment of a literal in literalNames
// In other words: model.size() == literalNames.size()
// model.at(i) corresponds to the assignment of literalNames.at(i)
bool CNFKnowledgeBase::checkAssignment(std::vector<ASSIGNMENT>& model){
    assignModel(model);

    for (auto currSentence = sentences.begin(); currSentence != sentences.end(); currSentence++){
        if ((*currSentence)->evalSentence() == TRUE){
            continue;
        }else{
            return false;
        }
    }

    return true;
}