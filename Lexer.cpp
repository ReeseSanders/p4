#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "MatchAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "IdAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"
#include <cctype>

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    for (unsigned int i = 0; i <automata.size(); i++) {
        delete automata.at(i);
    }
    automata.clear();
    for (unsigned int i = 0; i <tokens.size(); i++) {
        delete tokens.at(i);
    }
    tokens.clear();
}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new MatchAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new IdAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
}

void Lexer::Run(std::string& input) {
    int lineNumber = 1;
    while (input.size() > 0) {
        int maxRead = 0;
        Automaton* maxAutomaton = automata.at(0);
        if (!isspace(input.at(0))){
            for (unsigned int i = 0; i < automata.size(); i++) {
                 int inputRead = automata.at(i)->Start(input);
                 if (inputRead > maxRead) {
                     maxRead = inputRead;
                     maxAutomaton = automata.at(i);
                 }
            }
            if (maxRead > 0) {
                Token* newToken = maxAutomaton->CreateToken(input.substr(0,maxRead),lineNumber);
                lineNumber += maxAutomaton->NewLinesRead();
                tokens.push_back(newToken);
                //std::cout << newToken->ToString() << std::endl;
            } else {
                maxRead = 1;
                Token* newToken = new Token(TokenType::UNDEFINED, input.substr(0,maxRead), lineNumber);
                tokens.push_back(newToken);
            }
            input.erase(input.begin(), input.begin()+maxRead);
        } else {
            if (input.at(0) == '\n') {
                lineNumber++;
            }
            input.erase(input.begin(), input.begin()+1);
        }
    }
    tokens.push_back(new Token(TokenType::EOF_TYPE, "" , lineNumber));

    /*for(unsigned int i = 0; i < tokens.size(); i++) {
        std::cout << tokens.at(i)->ToString() << std::endl;
    }
    std::cout << "Total Tokens = " << tokens.size();*/
}

std::vector<Token*> Lexer::GetTokens(){
    return tokens;
};