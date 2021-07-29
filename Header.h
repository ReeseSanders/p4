#ifndef PROJECT1_HEADER_H
#define PROJECT1_HEADER_H
#include <iostream>
#include <vector>

class Header {
private:
    std::vector<std::string> attributes;
    std::vector<std::string> qattributes;

public:
    Header(){};

    std::string at(int index);

    std::string atQ(int index);

    int getSize();

    void add(std::vector<std::string> toAdd);

    std::vector<std::string> GetHead() {return attributes;}
    std::vector<std::string> GetQHead() {return qattributes;}
    void RenameHead(std::vector<std::string> rename){attributes = rename;}
    void addQ(std::vector<std::string> toAdd){qattributes = toAdd;}
    int GetSizeQ(){return qattributes.size();}
};

#endif //PROJECT1_HEADER_H
