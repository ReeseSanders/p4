#ifndef PROJECT1_TUPLE_H
#define PROJECT1_TUPLE_H
#include <string>
#include <iostream>
#include <vector>

class Tuple {
private:
    std::vector<std::string> myTup;

public:
    Tuple(){}

    void add(std::vector<std::string> toAdd){myTup = toAdd;}

    bool operator< (const Tuple & other)const;

    std::string at(int index);

    int getSize();

    std::vector<std::string> GetVector(){return myTup;}



};

#endif //PROJECT1_TUPLE_H
