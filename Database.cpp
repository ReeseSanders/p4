#include "Database.h"


void Database::insert(std::string name, Relation toAdd){
    myDatabase.insert(std::pair<std::string, Relation>(name, toAdd));
}

void Database::add(std::string name, Tuple toAdd) {
    myDatabase.at(name).addTuple(toAdd);
}

std::string Database::toString() {
    std::string full = "";
    for (std::pair<std::string, Relation> t : myDatabase) {
        full += t.first + "\n" + t.second.toString();
    }
    return full;
}

unsigned int Database::GetSizeOfRelation(std::string name){
    return myDatabase.at(name).GetTupSize();
}
