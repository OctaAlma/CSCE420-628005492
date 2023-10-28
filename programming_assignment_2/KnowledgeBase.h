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

struct CNFLiteral{
    std::string name;
    bool negated;
    
    int assign;

    CNFLiteral(){
        name = "";
        negated = false;
        assign = FALSE;
    }

    CNFLiteral(std::string name, bool negated):name(name), negated(negated){
        assign = FALSE;
    }
};

struct CNFSentence{
    std::vector<std::shared_ptr<CNFLiteral> > literals; 

    bool eval = false;

    int evalSentence(){

        for (auto currLiteral = literals.begin(); currLiteral != literals.end(); currLiteral++){
            if ((*currLiteral)->assign == NOT_SET){
                std::cout << "Literal " << (*currLiteral)->name << " does not have an assigned value.\n";
                return -1;
            }else{
                eval = eval || (*currLiteral)->assign;
            }
        }

        return eval;
    }
};

class CNFKnowledgeBase{
    private:
    std::vector<std::shared_ptr<CNFSentence> > sentences;  
    std::vector<std::string> literalNames;

    public:
    void loadKB(std::string filename);
    void addLiteral(std::string s);
    void assignModel(std::vector<ASSIGNMENT>& model);

    // Every index in model T corresponds to the assignment of a literal in literalNames
    // In other words: model.size() == literalNames.size()
    // model.at(i) corresponds to the assignment of literalNames.at(i)
    bool checkAssignment(std::vector<ASSIGNMENT>& model);
};

