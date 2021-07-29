#include "Relation.h"
#include <sstream>
#include <map>
#include <set>

Relation::Relation(std::string toName, Header toHeader){
    name = toName;
    myHeader = toHeader;
    isQuery = false;

    //for test
    /*std::vector<std::string> vect{"hello", "Oh No", "Goodbye"};
    std::vector<std::string> vecta{"Stop", "Boo", "Left"};
    Tuple test(vect);
    Tuple testa(vecta);
    addTuple(test);
    addTuple(testa);
    toString();*/
}

void Relation::addTuple(Tuple toAdd){
    myTuples.insert(toAdd);
}

std::string Relation::toString(){
    std::string relation = "";
    unsigned int iter = 1;

    if (myHeader.GetSizeQ() != 0) {
        relation += "\n";
    }
    if (isQuery == false) {
        for (Tuple t : myTuples) {
            relation += "  ";
            for (int i = 0; i < t.getSize(); i++) {
                relation += myHeader.at(i) + "=" + t.at(i);
                if ((i + 1) != t.getSize()) {
                    relation += ", ";
                } else {
                    relation += "\n";
                }
            }
        }
    } else {
        for (Tuple t : myTuples) {
            relation += "  ";
            for (int i = 0; i < t.getSize(); i++) {
                relation += myHeader.atQ(i) + "=" + t.at(i);
                if ((i + 1) != t.getSize()) {
                    relation += ", ";
                } else {
                    if(iter != myTuples.size()) {
                        relation += "\n";
                    }
                }
            }
            iter++;
        }

    }
    return relation;
}

Relation Relation::Evaluate(Predicate pred) {
    //std::cout << "In Relation::Evaluate" << std::endl;
    Header head;
    std::vector<std::string> pr = pred.getString();
    std::set<std::string> varCheck;
    std::vector<std::string> toH;
    for (unsigned int i = 0; i < pr.size(); i++){
        if (pr.at(i).at(0) != '\'') {
            varCheck.insert(pr.at(i));
        }
    }
    for (auto it = varCheck.begin(); it != varCheck.end(); it++){
        toH.push_back(*it);
    }
    head.add(pr);
    Relation toReturn(pred.getHead(), head);
    for (Tuple t : myTuples) {
        std::vector<std::string> p = pr;
        std::vector<std::string> headVecAdd;
        std::map<std::string, std::string> checker;
        for (unsigned int i = 0; i < p.size(); i++) {
            if (p.at(i).at(0) != '\'') {
                if (checker.find(p.at(i)) == checker.end()) {
                    headVecAdd.push_back(p.at(i));
                    checker.insert(std::pair<std::string, std::string>(p.at(i), t.at(i)));
                    p.at(i) = t.at(i);

                } else {
                    if (t.at(i) == checker.at(p.at(i))) {
                        p.at(i) = t.at(i);
                    } else {
                        p.at(i) = "error";
                    }
                }
            }
        }
        if(checker.empty()) {
            //std::cout << "Checker is empty" << std::endl;
        }
        if (p == t.GetVector()) {
            Tuple toAdd;
            std::vector<std::string> toTupple;
            for (auto c : headVecAdd) {
                toTupple.push_back(checker.at(c));
            }
            toAdd.add(toTupple);
            toReturn.addQHead(headVecAdd);
            toReturn.addTuple(toAdd);
        }
    }
    toReturn.QueryFlag();
    return toReturn;
}

Relation Relation::EvaluateR(Predicate pred) {
    //std::cout << "In Relation::Evaluate" << std::endl;
    Header head;
    std::vector<std::string> pr = pred.getString();
    std::set<std::string> varCheck;
    std::vector<std::string> toH;
    for (unsigned int i = 0; i < pr.size(); i++){
            varCheck.insert(pr.at(i));
    }
    for (auto it = varCheck.begin(); it != varCheck.end(); it++){
        toH.push_back(*it);
    }
    head.add(pr);
    Relation toReturn(pred.getHead(), head);
    for (Tuple t : myTuples) {
        std::vector<std::string> p = pr;
        std::vector<std::string> headVecAdd;
        std::map<std::string, std::string> checker;
        for (unsigned int i = 0; i < p.size(); i++) {
            if (p.at(i).at(0) != '\'') {
                if (checker.find(p.at(i)) == checker.end()) {
                    headVecAdd.push_back(p.at(i));
                    checker.insert(std::pair<std::string, std::string>(p.at(i), t.at(i)));
                    p.at(i) = t.at(i);

                } else {
                    if (t.at(i) == checker.at(p.at(i))) {
                        p.at(i) = t.at(i);
                    } else {
                        p.at(i) = "error";
                    }
                }
            } else {
                    if (t.at(i) == p.at(i)) {
                        headVecAdd.push_back(p.at(i));
                        checker.insert(std::pair<std::string, std::string>(p.at(i), t.at(i)));

                        p.at(i) = t.at(i);
                    } else {
                        p.at(i) = "error";
                    }
            }
        }
        if(checker.empty()) {
            //std::cout << "Checker is empty" << std::endl;
        }
        if (p == t.GetVector()) {
            Tuple toAdd;
            std::vector<std::string> toTupple;
            for (auto c : headVecAdd) {
                toTupple.push_back(checker.at(c));
            }
            toAdd.add(toTupple);
            toReturn.addQHead(headVecAdd);
            toReturn.addTuple(toAdd);
        }
    }
    toReturn.QueryFlag();
    return toReturn;
}

void Relation::QueryFlag(){
    isQuery = true;
    std::vector<std::string> headVec = myHeader.GetHead();
    name = name + "(";
    for (unsigned int i = 0; i < headVec.size(); i++){
        name += headVec.at(i);
        if (i < headVec.size()-1) {
            name += ",";
        }
    }
    name += ")? ";
    if (myTuples.empty()) {
        name += "No";
    } else {
        name += "Yes(";
        name += std::to_string(myTuples.size());
        name += ")";
    }
}

Relation Relation::Join(Relation toJoin){
    //this is a stubbed function
    //Will always return a relation
    //Two headers can always be combined
    //There might not be any tuples that can be combined
    std::vector<std::string> headA = myHeader.GetHead();
    std::vector<std::string> headB = toJoin.GetHead();
    std::vector<int> matchA;
    std::vector<int> matchB;

    for (unsigned int i = 0; i < headA.size(); i++) {
        for (unsigned int j = 0; j < headB.size(); j++) {
            if (headA.at(i) == headB.at(j)) {
                matchA.push_back(i);
                matchB.push_back(j);
            }
        }
    }
    std::vector<std::string> combHead = headA;
    if (matchA.size() > 0){
        for (unsigned int i = 0; i < matchB.size(); i++) {
            headB.erase(headB.begin()+matchB.at(i));
        }
    }
    for (auto a : headB){
        combHead.push_back(a);
    }
    Header uniHead;
    uniHead.add(combHead);
    Relation uni("Union", uniHead);
    std::set<Tuple> tupleB = toJoin.GetTuples();
    if (matchA.size() > 0) {
        for(auto i : myTuples) {//look at first tuples
            for(auto k : tupleB) {//Look at to match tuple list
                bool isMatch = true;
                for(unsigned int j = 0; j < matchA.size(); j++) { //Look at every match
                    if(i.at(matchA.at(j)) != k.at(matchB.at(j))) {
                        isMatch = false;
                    }  //compare all tupleB values to the key match value
                }
                if (isMatch){
                    std::vector<std::string> tupleComb = i.GetVector();
                    std::vector<std::string> tupleBComb = k.GetVector();
                    for (auto l : matchB){
                        tupleBComb.erase(tupleBComb.begin()+l);
                    }
                    for (auto p : tupleBComb){
                        tupleComb.push_back(p);
                    }
                    Tuple tupUni;
                    tupUni.add(tupleComb);
                    uni.addTuple(tupUni);
                }
            }
        }
    } else {
        for(auto i : myTuples) {//look at first tuples
            for (auto k : tupleB) {//Look at to match tuple list
                std::vector<std::string> tupleComb = i.GetVector();
                std::vector<std::string> tupleBComb = k.GetVector();
                for (auto p : tupleBComb){
                    tupleComb.push_back(p);
                }
                Tuple tupUni;
                tupUni.add(tupleComb);
                uni.addTuple(tupUni);
            }
        }
    }
    //std::cout << uni.toString() << std::endl;
    return uni;
}

Relation Relation::Project(Predicate pred){
    std::vector<std::string> p = pred.getString();
    std::vector<std::string> h = myHeader.GetHead();
    std::vector<int> matchIndex;

    for (unsigned int i = 0; i < p.size(); i++){
        for (unsigned int j = 0; j < h.size();j++) {
            if(p.at(i) == h.at(j)) {
                matchIndex.push_back(j);
            }
        }
    }

    Header pro;
    pro.add(p);
    Relation proj(pred.getHead(), pro);
    for (auto i : myTuples){
        std::vector<std::string> nTup;

        for (unsigned int j = 0; j < matchIndex.size(); j++){

            //std::cout << std::endl << matchIndex.at(j) << std::endl;
            //std::cout << matchIndex.size() << std::endl;
            //std::cout << i.getSize() << std::endl;
            nTup.push_back(i.at(matchIndex.at(j)));
        }

        Tuple projected;
        projected.add(nTup);
        proj.addTuple(projected);
    }

    //std::cout << proj.toString() << std::endl;
    return proj;
}

Relation Relation::Subtract(std::set<Tuple> minus){
    Relation diff(name, myHeader);
    for (auto i : myTuples){
        if (minus.find(i) == minus.end()){
            diff.addTuple(i);
        }
    }
    return diff;
}
