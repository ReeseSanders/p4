#ifndef PROJECT1_DATABASE_H
#define PROJECT1_DATABASE_H
#include <iostream>
#include <map>
#include "Relation.h"
#include "Tuple.h"

class Database {
private:
    std::map<std::string, Relation> myDatabase;

public:
    Database(){}

    void insert(std::string name, Relation toAdd);

    void add(std::string name, Tuple toAdd);

    std::string toString();

    Relation getRelation(std::string name) {return myDatabase.at(name);}

    unsigned int GetSizeOfRelation(std::string name);
};

#endif //PROJECT1_DATABASE_H
