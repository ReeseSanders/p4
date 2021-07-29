#ifndef PROJECT1_PARSER_H
#define PROJECT1_PARSER_H
#include <vector>
#include <string>
#include "Token.h"
#include "DatalogProgram.h"
#include "Predicate.h"

class Parser {
private:
    std::vector<Token*> tokens;
    unsigned int index;
    std::vector<Predicate> schemes;
    unsigned int sindex;
    DatalogProgram myProgram;

public:
    Parser(std::vector<Token*> tokens);
    ~Parser();

    bool Match(TokenType toMatch);

    DatalogProgram Parse();

    bool datalogProgram();

    bool schemeList();
    bool factList();
    bool ruleList();
    bool queryList();

    bool scheme();
    bool fact();
    bool rule();
    bool query();

    Predicate headPredicate();
    Predicate predicate();

    bool predicateList(std::vector<Predicate> &following);
    bool parameterList(Predicate &toAdd);
    Predicate stringList(Predicate &toAdd);
    Predicate idList(Predicate &toAdd);
    bool parameter();
};

#endif //PROJECT1_PARSER_H