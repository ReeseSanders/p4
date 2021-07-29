#include "Predicate.h"


void Predicate::PushBack(Token* next){
    IDStrings.push_back(next);
    strs.push_back(next->DesString());
}

std::string Predicate::ToString(){
    std::string pred = head->DesString() + "(";
    for (unsigned int i = 0; i < IDStrings.size(); i++) {
        pred += IDStrings.at(i)->DesString();
        if (i != IDStrings.size()-1) {
            pred += ",";
        }
    }
    pred += ")";
    return pred;
}

bool Predicate::success(){
    return ifsuccess;
}

std::vector<std::string> Predicate::getString(){
    return strs;
}

bool Predicate::isID(int index) {
    if (IDStrings.at(index)->GetType() == TokenType::ID) {
        return true;
    } else {
        return false;
    }
}
