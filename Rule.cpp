#include "Rule.h"

void Rule::AddHeadPredicate(Predicate toAdd){
    headPredicate = toAdd;
}

void Rule::AddFollowingPred(Predicate toAdd){
    followingPred.push_back(toAdd);
}

std::string Rule::ToString(){
    std::string ruleString = headPredicate.ToString() + " :- ";
    for (unsigned int i = 0; i < followingPred.size(); i++){
        if (i != followingPred.size()-1) {
            ruleString += followingPred.at(i).ToString() + ",";
        } else {ruleString += followingPred.at(i).ToString() + ".";}
    }
    return ruleString;
}
