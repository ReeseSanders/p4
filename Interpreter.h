#ifndef PROJECT1_INTERPRETER_H
#define PROJECT1_INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"
#include "Relation.h"
#include "Predicate.h"
#include <iostream>
#include <string>
#include <set>

class Interpreter {
private:
    DatalogProgram myProgram;
    Database myDatabase;
    int numPasses;

public:
    Interpreter(DatalogProgram newProgram){
        myProgram = newProgram;
        numPasses = 0;
    }

    void Interpret();

    Relation evaluatePredicate(Predicate p);

    Relation evaluateRule(Rule r);

};

#endif //PROJECT1_INTERPRETER_H
