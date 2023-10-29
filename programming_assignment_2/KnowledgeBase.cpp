#include "KnowledgeBase.h"
using namespace std;

unsigned int countWordsInString(std::string const& str)
{
    std::stringstream stream(str);
    return std::distance(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>());
}

void CNFKnowledgeBase::printKB(){
    for (int i = 0; i < sentences.size(); i++){
        sentences.at(i)->printSentence();
    }
}

void CNFKnowledgeBase::printAssignments(){
    cout << "Truth assignments for each literal: " << allLiterals.size() << endl;
    for (int i = 0; i < allLiterals.size(); i++){
        cout << allLiterals.at(i)->name << " : " << allLiterals.at(i)->assign << endl;
    }

    cout << "\n";
}

void CNFKnowledgeBase::printTruePropositions(){
    cout << "Just the Satisfied (true) propositions:\n";

    for (int i = 0; i < allLiterals.size(); i++){
        if (allLiterals.at(i)->assign == TRUE){
            cout << allLiterals.at(i)->name << " ";
        }
    }
    cout << "\n\n";
}

// Returns a pointer to the Literal object specified by the name
std::shared_ptr<Literal> CNFKnowledgeBase::findLiteral(std::string name){

    for (int i = 0; i < allLiterals.size(); i++){
        if (allLiterals.at(i)->name == name){
            return allLiterals.at(i);
        }
    }
    
    return NULL;
}

void CNFKnowledgeBase::loadKB(std::string filename){
    ifstream kbFile(filename);
    
    if (kbFile.fail()){
        cout << "Could not open knowledge base file " << filename << endl;
    }

    string currLine;

    string currLiteralName;
    bool negated = false;

    while(getline(kbFile, currLine)) {
        istringstream ss(currLine);

        if (currLine.empty()){
            continue;
        }

        if (currLine.at(0) == '#' || currLine.at(0) == '\n' || currLine.at(0) == '\0'){
            continue;
        }
        
        // Parse through each word at each line and create "CNFLiteral" objects
        auto newSentence = make_shared<CNFSentence>();
        while(!ss.eof()){
            ss >> currLiteralName;

            if (ss.fail()){
                continue;
            }

            if (currLiteralName.empty()){
                continue;
            }

            bool negated = false;

            if (currLiteralName.at(0) == '-'){
                currLiteralName.erase(0, 1);
                negated = true;
            }

            shared_ptr<Literal> l = findLiteral(currLiteralName);

            if (l == NULL){
                l = make_shared<Literal>(currLiteralName, NOT_SET);
                allLiterals.push_back(l);
            }

            shared_ptr<CNFLiteral> CNFl = make_shared<CNFLiteral>(l, negated);

            newSentence->literals.push_back(CNFl);
        }

        sentences.push_back(newSentence);
    }
}

// Given a literal name, will add it to the knowledge base as a known fact
void CNFKnowledgeBase::addFact(std::string name){
    bool negated = false;

    if (name.at(0) == '-'){
        name.erase(0, 1);
        negated = true;
    }
    
    auto l = findLiteral(name);
    
    if (l != NULL){
        l->assign = !negated;
    }else{
        l = make_shared<Literal>(name, !negated);
    }

    auto newSentence = make_shared<CNFSentence>();
    newSentence->literals.push_back(make_shared<CNFLiteral>(l, negated));
    sentences.push_back(newSentence);
}

void CNFKnowledgeBase::addFacts(int argc, char** argv){
    for (int i = 2; i < argc; i++){
        if ((string)argv[i] == "+UCH"){
            continue;
        }
        addFact(argv[i]);
    }
}

void CNFKnowledgeBase::assignModel(std::vector<ASSIGNMENT>& model){
    if (model.size() != allLiterals.size()){
        cout << "The size of the provided model does not match the size of the number of literals.\n";
        cout << "Model size: " << model.size() << endl;
        cout << "Number of literals: " << allLiterals.size() << endl;
        return;
    }

    size_t n = model.size();

    for (int i = 0; i < n; i++){
        allLiterals.at(i)->assign = model.at(i);
    }
}

std::vector<ASSIGNMENT> CNFKnowledgeBase::extractModel(){
    std::vector<ASSIGNMENT> a;
    int n = allLiterals.size();

    for (int i = 0; i < n; i++){
        a.push_back(allLiterals.at(i)->assign);
    }

    return a;
}
// Every index in model T corresponds to the assignment of a literal in allLiterals
// In other words: model.size() == allLiterals.size()
// model.at(i) corresponds to the assignment of allLiterals.at(i)
ASSIGNMENT CNFKnowledgeBase::checkAssignment(std::vector<ASSIGNMENT>& model){
    assignModel(model);

    bool notSetFound = false;

    for (int i = 0; i < sentences.size(); i++){
        int currEval = sentences.at(i)->evalSentence();

        if (currEval == FALSE){
            return currEval;
        }
        else if (currEval == NOT_SET){
            notSetFound = true;
        }
    }

    if (notSetFound){
        return NOT_SET;
    }

    return TRUE;
}

// Returns NULL if all literals have already been assigned
// Otherwise, returns a pointer to the first literal that has not been assigned
std::shared_ptr<Literal> CNFKnowledgeBase::findUnassignedLiteral(){
    
    for (int i = 0; i < allLiterals.size(); i++){
        if (allLiterals.at(i)->assign == NOT_SET){
            return allLiterals.at(i);
        }
    }

    return NULL;
}

// Returns -1 if all literals have already been assigned
// Otherwise, returns the index of the first literal that has not been assigned in allLiterals
int CNFKnowledgeBase::findUnassignedLiteralIndex(){
    
    for (int i = 0; i < allLiterals.size(); i++){
        if (allLiterals.at(i)->assign == NOT_SET){
            return i;
        }
    }

    return -1;
}

// Returns NULL if there are no unit clauses in the KB
// Otherwise, returns a pointer to the CNF Literal object in the sentence
std::shared_ptr<CNFLiteral> CNFKnowledgeBase::findUnitClause(){
    std::shared_ptr<CNFLiteral> uc = NULL;

    for (int i = 0; i < sentences.size(); i++){
        uc = sentences.at(i)->isUnitClause();

        if (uc != NULL){
            return uc;
        }
    }

    return NULL;
}

std::string CNFKnowledgeBase::getLiteralName(int index){

    if (index < 0 || index >= allLiterals.size()){
        cout << "Cannot access literal at index " << index << endl;
        cout << "Number of literals = " << allLiterals.size() << endl;    
        return "";
    }

    return allLiterals.at(index)->name;
}

int CNFKnowledgeBase::getLiteralIndex(std::string lName){
    for (int i = 0; i < allLiterals.size(); i++){
        if (lName == allLiterals.at(i)->name){
            return i;
        }
    }

    return -1;
}
