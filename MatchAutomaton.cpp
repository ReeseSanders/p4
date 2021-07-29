#include "MatchAutomaton.h"
#include "Token.h"

void MatchAutomaton::S0(const std::string& input) {
    if (toMatch.count(input[0])) {
        inputRead = 1;
        this->type = toMatch[input[0]];
    }
    else {
        Serr();
    }
}

