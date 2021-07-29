#ifndef PROJECT1_RELATION_H
#define PROJECT1_RELATION_H
#include <iostream>
#include <set>
#include <string>
#include "Tuple.h"
#include "Header.h"
#include "Predicate.h"

class Relation {
private:
    std::set<Tuple> myTuples;
    std::string name;
    Header myHeader;
    bool isQuery;

public:
    Relation(std::string toName, Header toHeader);
    void addTuple(Tuple toAdd);
    std::string toString();
    Relation Evaluate(Predicate pred);
    Relation EvaluateR(Predicate pred);
    std::string GetName(){return name;}
    void QueryFlag();
    void addQHead(std::vector<std::string> toAdd){myHeader.addQ(toAdd);}
    Relation Join(Relation toJoin);
    std::vector<std::string> GetHead() {return myHeader.GetHead();}
    std::set<Tuple> GetTuples(){return myTuples;}
    Relation Project(Predicate pred);
    unsigned int GetTupSize(){return myTuples.size();}
    void QueryUnFlag(){isQuery = false;}
    Relation Subtract(std::set<Tuple> minus);
};

#endif //PROJECT1_RELATION_H
