#ifndef COMMAAUTOMATON_H
#define COMMAAUTOMATON_H
#include "Token.h"
#include "Automaton.h"

class CommaAutomaton : public Automaton
{
public:
    CommaAutomaton() : Automaton(TokenType::COMMA) {}  // Call the base constructor

    void S0(const std::string& input);

};

#endif // COMMAAUTOMATON_H