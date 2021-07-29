#include "DatalogProgram.h"

void DatalogProgram::addScheme(Predicate toAdd){
    schemes.push_back(toAdd);
}

void DatalogProgram::addFacts(Predicate toAdd){
    facts.push_back(toAdd);
}

void DatalogProgram::addRules(Rule toAdd){
    rules.push_back(toAdd);
}
void DatalogProgram::addQuery(Predicate toAdd){
    query.push_back(toAdd);
}

void DatalogProgram::addDomains(std::string toAdd){
    domains.insert(toAdd);
}

std::string DatalogProgram::toString(){
    std::string result = "Schemes(" + std::to_string(schemes.size()) + "):" + "\n";
    for (unsigned int i = 0; i < schemes.size(); i++) {
        result += "  " + schemes.at(i).ToString() + "\n";
    }

    result += "Facts(" + std::to_string(facts.size()) + "):" + "\n";
    for (unsigned int i = 0; i < facts.size(); i++) {
        result += "  " + facts.at(i).ToString() + ".\n";
    }

    result += "Rules(" + std::to_string(rules.size()) + "):" + "\n";
    for (unsigned int i = 0; i < rules.size(); i++) {
        result += "  " + rules.at(i).ToString() + "\n";
    }

    result += "Queries(" + std::to_string(query.size()) + "):" + "\n";
    for (unsigned int i = 0; i < query.size(); i++) {
        result += "  " + query.at(i).ToString() + "?\n";
    }

    result += "Domain(" + std::to_string(domains.size()) + "):";
    for (auto it = domains.begin(); it != domains.end(); it++) {
            result += "\n  " + *it;
    }

    return result;
}
