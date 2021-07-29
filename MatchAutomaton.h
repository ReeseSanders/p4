#ifndef PROJECT1_MATCHAUTOMATON_H
#define PROJECT1_MATCHAUTOMATON_H

#include "Automaton.h"
#include <map>

class MatchAutomaton : public Automaton
{
private:
    std::map<char, TokenType> toMatch {
        {',',TokenType::COMMA},
        {'.',TokenType::PERIOD},
        {'?', TokenType::Q_MARK},
        {'*', TokenType::MULTIPLY},
        {'+', TokenType::ADD},
        {'(', TokenType::LEFT_PAREN},
        {')', TokenType::RIGHT_PAREN}
    };
public:
    MatchAutomaton() : Automaton(TokenType::UNDEFINED) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //PROJECT1_MATCHAUTOMATON_H
