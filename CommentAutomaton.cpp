#include "CommentAutomaton.h"

void CommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead = 1;
        index++;
        if (input[index] == '|') {
            inputRead++;
            index++;
            S1(input);
        } else {
            S2(input);
        }
    }
    else {
        Serr();
    }
}

void CommentAutomaton::S1(const std::string& input) {
    if (input[index] == '\n') {
        newLines++;
    }
    if (index == input.size()) {
        type = TokenType::UNDEFINED;
        return;
    }
    if (input[index] == '|') {
        if (input[index+1] == '#') {
            inputRead +=2;
            return;
        } else {
            inputRead++;
            index++;
            S1(input);
            return;
        }
    } else {
        index++;
        inputRead++;
        S1(input);
        return;
    }
}

void CommentAutomaton::S2(const std::string& input) {
    if ((input[index] == '\n') || (index == input.size())) {
        return;
    } else {
        inputRead++;
        index++;
        S2(input);
        return;
    }
}
