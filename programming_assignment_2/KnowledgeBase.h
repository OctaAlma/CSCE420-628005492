#ifndef KNOWLEDGE_BASE
#define KNOWLEDGE_BASE

#include <iostream> 
#include <unordered_map>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

#define ASSIGNMENT int
enum Assignments{
    NOT_SET = -1,
    FALSE,
    TRUE
};

struct Literal{
    std::string name;
    int assign;

    Literal(): name(""), assign(NOT_SET){}
    Literal(std::string name, ASSIGNMENT assign):name(name), assign(assign){}
};

struct CNFLiteral{
    std::shared_ptr<Literal> literal;
    bool negated = false;

    CNFLiteral():literal(NULL), negated(false){}
    CNFLiteral(std::shared_ptr<Literal> l, bool neg):literal(l), negated(neg){}
};

struct CNFSentence{
    std::vector<std::shared_ptr<CNFLiteral> > literals; 

    // Returns -1 if there are literals that have not been set
    // Returns 0 if the sentence evaluates to false
    // Returns 1 if the sentence evaluates to true
    int evalSentence(){
        bool eval = false;

        for (auto currLiteral = literals.begin(); currLiteral != literals.end(); currLiteral++){
            
            if ((*currLiteral)->literal->assign == NOT_SET){
                return -1;
            
            }else{
                bool value = (*currLiteral)->literal->assign;
                
                if ((*currLiteral)->negated){
                    value = !value;
                }

                eval = eval || value;
            }
        }

        return eval;
    }

    // If the sentence has a unit literal, returns a pointer to the literal that is not set yet
    // Otherwise, returns NULL
    std::shared_ptr<CNFLiteral> isUnitClause(){
        if (literals.size() == 1){
            return literals.at(0);
        }

        std::shared_ptr<CNFLiteral> unitLiteral = NULL;

        int numNotSet = 0;

        for (auto currLiteral = literals.begin(); currLiteral != literals.end(); currLiteral++){
            if ((*currLiteral)->literal->assign == NOT_SET){

                if (unitLiteral != NULL){
                    return NULL;
                }
                else{
                    unitLiteral = (*currLiteral);
                }

            }
        }

        return unitLiteral;
    }

    void printSentence(){
        std::cout << "[ ";

        for (auto l = literals.begin(); l != literals.end(); l++){
            
            if ((*l)->negated){
                std::cout << "NOT ";    
            }

            std::cout << (*l)->literal->name;

            if (l != (literals.end() - 1)){
                std::cout << " OR ";
            }else{
                std::cout << " ";
            }
        }
        
        std::cout << "]\n";
    }
};

class CNFKnowledgeBase{
    private:
    std::vector<std::shared_ptr<CNFSentence> > sentences;  
    std::vector<std::shared_ptr<Literal> > allLiterals;

    std::shared_ptr<Literal> findLiteral(std::string name);

    public:
    void printKB();
    void loadKB(std::string filename);
    void addFact(std::string s);
    void addFacts(int argc, char** argv);
    void assignModel(std::vector<ASSIGNMENT>& model);
    std::vector<ASSIGNMENT> extractModel();
    std::shared_ptr<Literal> findUnassignedLiteral();
    int findUnassignedLiteralIndex();

    // Every index in model T corresponds to the assignment of a literal in literalNames
    // In other words: model.size() == literalNames.size()
    // model.at(i) corresponds to the assignment of literalNames.at(i)
    ASSIGNMENT checkAssignment(std::vector<ASSIGNMENT>& model);
    void printAssignments();
    void printTruePropositions();
    std::string getLiteralName(int index);
};

#endif
