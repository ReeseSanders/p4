#ifndef PROJECT1_PREDICATE_H
#define PROJECT1_PREDICATE_H
#include "Token.h"
#include <vector>

class Predicate {
private:
    bool ifsuccess = true;
    Token* head;
    std::vector<Token*> IDStrings;
    std::vector<std::string> strs;

public:
    Predicate(){ifsuccess = false;}
    Predicate(Token* newhead) {head = newhead;}

    void PushBack(Token* next);

    std::string ToString();
    bool success();
    std::vector<std::string> getString();
    std::string getHead(){return head->DesString();}
    int getSize(){return strs.size();}
    std::string at(int index){return strs.at(index);}
    bool isID(int index);
};

#endif //PROJECT1_PREDICATE_H
