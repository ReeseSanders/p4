#include "Tuple.h"

bool Tuple::operator< (const Tuple & other) const{
    return this->myTup < other.myTup;
}

std::string Tuple::at(int index){
    return myTup.at(index);
}

int Tuple::getSize(){
    return myTup.size();
}
