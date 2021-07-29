#ifndef PROJECT1_DATALOGPROGRAM_H
#define PROJECT1_DATALOGPROGRAM_H
#include <vector>
#include <string>
#include <set>
#include "Token.h"
#include "Predicate.h"
#include "Rule.h"

class DatalogProgram {
private:
    std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Rule> rules;
    std::vector<Predicate> query;
    std::set<std::string> domains;

public:
    DatalogProgram(){}

    void addScheme(Predicate toAdd);
    void addFacts(Predicate toAdd);
    void addRules(Rule toAdd);
    void addQuery(Predicate toAdd);
    void addDomains(std::string toAdd);

    std::vector<Predicate> getScheme() {return schemes;}
    std::vector<Predicate> getFacts() {return facts;}
    std::vector<Predicate> getQuery() {return query;}
    std::vector<Rule> getRules() {return rules;}

    std::string toString();
};

#endif //PROJECT1_DATALOGPROGRAM_H
