#include "Header.h"

std::string Header::at(int index){
    return attributes.at(index);
}
std::string Header::atQ(int index){
    return qattributes.at(index);
}

int Header::getSize(){
    return attributes.size();
}

void Header::add(std::vector<std::string> toAdd) {
    attributes = toAdd;
}
