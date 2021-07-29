#include "Parser.h"

Parser::Parser(std::vector<Token*> tokens) {
    //std::cout << "In Parser constructor" << std::endl;
    this->tokens = tokens;
    index = 0;
    sindex =0;
    //std::cout << "In Parser constructor" << std::endl;
}
Parser::~Parser(){
    /*for (unsigned int i = 0; i <tokens.size(); i++) {
        delete tokens.at(i);
    }
    tokens.clear();*/
}

bool Parser::Match(TokenType toMatch){
    while (tokens.at(index)->GetType() == TokenType::COMMENT) {
        //std::cout << "This is a comment" << std::endl;
        index++;
    }
    if (tokens.at(index)->GetType() == toMatch) {
        index++;
        return(true);
    } else {return(false);}
}


DatalogProgram Parser::Parse() {
    //std::cout << "In Parse()" << std::endl;
    if (datalogProgram()) {
        //std::cout << "Success!" << std::endl;
        //std::cout << myProgram.toString() << std::endl;
    } else {
        //std::cout << "Failure!" << std::endl;
        //std::cout << tokens.at(22)->ToString() << std::endl;
        //std::cout << index << std::endl;
        std::cout << tokens.at(index)->ToString() << std::endl;
    }
    return myProgram;
}

bool Parser::datalogProgram(){
    //std::cout << "In datalogProgram()" << std::endl;
    if (!Match(TokenType::SCHEMES)) {return false;}
    if (!Match(TokenType::COLON)) {return false;}
    if (!scheme()) {return false;}
    if (!schemeList()) {return false;}
    if (!Match(TokenType::FACTS)) {return false;}
    if (!Match(TokenType::COLON)) {return false;}
    if (!factList()) {return false;}
    if (!Match(TokenType::RULES)) {return false;}
    if (!Match(TokenType::COLON)) {return false;}
    if (!ruleList()) {return false;}
    if (!Match(TokenType::QUERIES)) {return false;}
    if (!Match(TokenType::COLON)) {return false;}
    if (!query()) {return false;}
    if (!queryList()) {return false;}
    if (!Match(TokenType::EOF_TYPE)) {return false;}
    return true;
}

bool Parser::schemeList(){
   // std::cout << "In schemeList()" << std::endl;
    if (Match(TokenType::ID)) {
        index--;
        if (!scheme()) {return false;}
        if (!schemeList()) {return false;}
        return true;
    } else {return true;}
}
bool Parser::factList(){
    //std::cout << "In factList()" << std::endl;
    if (Match(TokenType::ID)) {
        index--;
        if (!fact()) {return false;}
        if (!factList()) {return false;}
        return true;
    } else {return true;}
}
bool Parser::ruleList(){
    //std::cout << "In ruleList()" << std::endl;
    if (Match(TokenType::ID)) {
        index--;
        if (!rule()) {return false;}
        if (!ruleList()) {return false;}
        return true;
    } else {return true;}
}
bool Parser::queryList(){
    //std::cout << "In queryList()" << std::endl;
    if (Match(TokenType::ID)) {
        index--;
        if (!query()) {return false;}
        if (!queryList()) {return false;}
        return true;
    } else {return true;}
}

bool Parser::scheme(){
    //std::cout << "In scheme()" << std::endl;
    if (!Match(TokenType::ID)) {return false;}
    Predicate toAdd(tokens.at(index-1));
    if (!Match(TokenType::LEFT_PAREN)) {return false;}
    if (!Match(TokenType::ID)) {return false;}
    toAdd.PushBack(tokens.at(index-1));
    idList(toAdd) ;
    if (!toAdd.success()) {return false;}
    if (!Match(TokenType::RIGHT_PAREN)) {return false;}
    myProgram.addScheme(toAdd);
    //std::cout << toAdd.ToString() << std::endl;
    return true;
}
bool Parser::fact(){
    //std::cout << "In fact()" << std::endl;
    if (!Match(TokenType::ID)) {return false;}
    Predicate toAdd(tokens.at(index-1));
    if (!Match(TokenType::LEFT_PAREN)) {return false;}
    if (!Match(TokenType::STRING)) {return false;}
    toAdd.PushBack(tokens.at(index-1));
    myProgram.addDomains(tokens.at(index-1)->DesString());
    stringList(toAdd);
    if (!toAdd.success()) {return false;}
    if (!Match(TokenType::RIGHT_PAREN)) {return false;}
    if (!Match(TokenType::PERIOD)) {return false;}
    myProgram.addFacts(toAdd);
    return true;
}
bool Parser::rule(){
    //std::cout << "In rules()" << std::endl;
    Rule newRule;
    Predicate headPred = headPredicate();
    if (!headPred.success()) {return false;}
    newRule.AddHeadPredicate(headPred);
    if (!Match(TokenType::COLON_DASH)) {return false;}
    Predicate follow = predicate();
    if (!follow.success()) {return false;}
    newRule.AddFollowingPred(follow);
    std::vector<Predicate> followers;
    if (!predicateList(followers)) {return false;}
    if (!Match(TokenType::PERIOD)) {return false;}
    for (unsigned int i = 0; i < followers.size(); i++) {
        newRule.AddFollowingPred(followers.at(i));
    }
    myProgram.addRules(newRule);
    return true;
}
bool Parser::query(){
   //std::cout << "In query()" << std::endl;
    Predicate toAdd = predicate();
    if (!toAdd.success()){return false;}
    if (!Match(TokenType::Q_MARK)) {return false;}
    myProgram.addQuery(toAdd);
    return true;
}

Predicate Parser::headPredicate(){
    //std::cout << "In headPredicate()" << std::endl;
    Predicate failed;
    if (!Match(TokenType::ID)) {return failed;}
    Predicate toAdd(tokens.at(index-1));
    if (!Match(TokenType::LEFT_PAREN)) {return failed;}
    if (!Match(TokenType::ID)) {return failed;}
    toAdd.PushBack(tokens.at(index-1));
    idList(toAdd); //need to fix to check if it worked
    if (!Match(TokenType::RIGHT_PAREN)) {return failed;}
    return toAdd;
}
Predicate Parser::predicate(){
    //std::cout << "In predicate()" << std::endl;
    Predicate failed;
    if (!Match(TokenType::ID)) {return failed;}
    Predicate toAdd(tokens.at(index-1));
    if (!Match(TokenType::LEFT_PAREN)) {return failed;}
    if (!parameter()) {return failed;}
    toAdd.PushBack(tokens.at(index-1));
    if (!parameterList(toAdd)) {return failed;}
    if (!Match(TokenType::RIGHT_PAREN)) {return failed;}
    return toAdd;
}

bool Parser::predicateList(std::vector<Predicate> &following){
    //std::cout << "In predicateList()" << std::endl;
    Predicate failed;
    if (Match(TokenType::COMMA)) {
        Predicate toAdd = predicate();
        if (!toAdd.success()) {return false;}
        following.push_back(toAdd);
        if (!predicateList(following)) {return false;}
        return true;
    } else {
        return true;
    }
}
bool Parser::parameterList(Predicate &toAdd){
   // std::cout << "In parameterList()" << std::endl;
    if (Match(TokenType::COMMA)) {
        if (!parameter()) {return false;}
        toAdd.PushBack(tokens.at(index-1));
        if (!parameterList(toAdd)) {return false;}
        return true;
    } else {
        return true;
    }
}
Predicate Parser::stringList(Predicate &toAdd){
    //std::cout << "In stringList()" << std::endl;
    Predicate failed;
    if (Match(TokenType::COMMA)) {
        if (!Match(TokenType::STRING)) {return failed;}
        toAdd.PushBack(tokens.at(index-1));
        myProgram.addDomains(tokens.at(index-1)->DesString());
        stringList(toAdd);
        if (!toAdd.success()){return failed;}
        return toAdd;
    } else {
        return toAdd;
    }
}
Predicate Parser::idList(Predicate &toAdd){
    //std::cout << "In idList()" << std::endl;
    Predicate failed;
    if (Match(TokenType::COMMA)) {
        if (!Match(TokenType::ID)) {return failed;}
        toAdd.PushBack(tokens.at(index-1));
        idList(toAdd);
        if (!toAdd.success()){return failed;}
        return toAdd;
    } else {
        return toAdd;
    }
}
bool Parser::parameter(){
    //std::cout << "In parameter()" << std::endl;
    if (Match(TokenType::STRING)) {return true;}
    else if (Match(TokenType::ID)) {return true;}
    else {return false;}
}
