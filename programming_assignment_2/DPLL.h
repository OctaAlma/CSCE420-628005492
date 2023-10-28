#ifndef DPLL_FUNCTIONS
#define DPLL_FUNCTIONS

#include "KnowledgeBase.h"

bool DPLL_Satisfiable(CNFKnowledgeBase kb, std::shared_ptr<CNFSentence> s);

bool DPLL(CNFKnowledgeBase kb, std::vector<ASSIGNMENT> model);

#endif