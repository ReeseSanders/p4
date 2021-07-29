#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>

enum class TokenType {
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    EOF_TYPE
};

class Token
{
private:

    TokenType type;
    std::string description;
    int line;

public:
    Token();
    Token(TokenType type, std::string description, int line);

    std::string ToString();
    std::string EnumToString();
    std::string DesString();


    TokenType GetType(){return type;}
};

#endif // TOKEN_H

