#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'') {
        inputRead = 1;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input) {
    if (input[index] == '\n') {
        newLines++;
    }
    if (index >= input.size()) {
        type = TokenType::UNDEFINED;
        return;
    }
    if (input[index] == '\'') {
        if (input[index+1] == '\'') {
            index+=2;
            inputRead+=2;
            S1(input);
            return;
        } else {
            inputRead++;
            return;
        }
    }
    inputRead++;
    index++;
    S1(input);
    return;
}
