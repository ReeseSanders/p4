#include "Interpreter.h"
#include "Header.h"
#include "Tuple.h"
#include "Rule.h"

void Interpreter::Interpret(){
    //std::cout << "In Interpreter::Interpret()" << std::endl;
    std::vector<Predicate> schemes = myProgram.getScheme();
    std::vector<Predicate> facts = myProgram.getFacts();

    for (unsigned int i = 0; i < schemes.size(); i++) {
        std::string name = schemes.at(i).getHead();
        Header headAdd;
        headAdd.add(schemes.at(i).getString());
        Relation myRel(name, headAdd);
        myDatabase.insert(name, myRel);
    }

    for (unsigned int i = 0; i < facts.size(); i++) {
        Tuple newTup;
        newTup.add(facts.at(i).getString());
        myDatabase.add(facts.at(i).getHead(), newTup);
    }

    //std::cout << myDatabase.toString() << std::endl;

    std::vector<Rule> rules = myProgram.getRules();

    std::cout << "Rule Evaluation" << std::endl;
    bool isChange = false;
    int indexer = 0;
    while(!isChange) {
        int check = numPasses;

        for (unsigned int i = 0; i < rules.size(); i++) {

            //std::cout << query.at(i).ToString() << std::endl;
            if (i != 0) {

            }
            Relation base = myDatabase.getRelation(rules.at(i).GetName());
            Relation eval = evaluateRule(rules.at(i));
            Relation after = myDatabase.getRelation(rules.at(i).GetName());

            std::cout << rules.at(i).ToString() << std::endl;
            if(check != numPasses){
                Relation toCout = after.Subtract(base.GetTuples());
                std::cout << toCout.toString();
            }
        }
        if(check == numPasses){
            isChange = true;
        }
        indexer++;
    }

    std::cout << std::endl << "Schemes populated after " << indexer << " passes through the Rules." << std::endl << std::endl; //finish formating

    std::vector<Predicate> query = myProgram.getQuery();
    // Relation eval = evaluatePredicate(query.at(0));
    //std::cout << eval.toString() << std::endl;
    std::cout << "Query Evaluation" << std::endl;
    for (unsigned int i = 0; i < query.size(); i++){
        //std::cout << query.at(i).ToString() << std::endl;
        if (i != 0) {
            std::cout << std::endl;
        }
        Relation eval = evaluatePredicate(query.at(i));
        std::cout << eval.GetName() << eval.toString();
    }
}

Relation Interpreter::evaluatePredicate(Predicate p){
    //std::cout << "Interpreter::evalutatePredicate()" << std::endl;
    Relation eval = myDatabase.getRelation(p.getHead());
    //std::cout << eval.toString() << std::endl;
    eval = eval.Evaluate(p);
    //std::cout << "Back to Interpreter::evalutatePredicate() from Relation::Evaluate()" << std::endl;
    //std::cout << eval.toString() << std::endl;
    return eval;

}

Relation Interpreter::evaluateRule(Rule r){
    //evaluatePredicate
    std::vector<Predicate> ps = r.GetPredicates();
    std::vector<Relation> toJoin;

    for (unsigned int i = 0; i < ps.size(); i++) {
        Relation toAdd = myDatabase.getRelation(ps.at(i).getHead());
        toAdd = toAdd.EvaluateR(ps.at(i));

        toAdd.QueryUnFlag();
        //std::cout << toAdd.toString() << std::endl;
        toJoin.push_back(toAdd);
    }
    //join
    //std::cout << toJoin.at(0).toString() << std::endl;
    if (toJoin.size() > 1) {
        for (unsigned int i = 0; i < toJoin.size()-1; i++){
            toJoin.at(0) = toJoin.at(0).Join(toJoin.at(i+1));
        }
    }
    //project & rename
    //std::cout << toJoin.at(0).toString() << std::endl;
    Relation projected = toJoin.at(0).Project(r.GetHeadPredicate());
    //union
    std::set<Tuple> unTup = projected.GetTuples();
    unsigned int numTup = myDatabase.GetSizeOfRelation(projected.GetName());
    for (auto i : unTup) {
        myDatabase.add(projected.GetName(), i);
    }
    if(numTup != myDatabase.GetSizeOfRelation(projected.GetName())){
        numPasses++;
    }
    return projected;
}
