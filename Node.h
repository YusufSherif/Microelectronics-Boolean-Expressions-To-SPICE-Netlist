//
// Created by Yusuf Sherif on 5/12/20.
//

#ifndef PROJECT_NODE_H
#define PROJECT_NODE_H

#include <string>
#include "GateFactory.h"

class Node {
private:
    std::string nodeName;
    static GateFactory GF;
    vector<Gate> GV;

public:

    Node(); //For creating intermediate nodes

    Node(const Node &old);

    Node(const std::string &p_str); //To create named nodes

    Node(const char x);

    Node operator!();

    Node operator&(const Node &rhs);

    Node operator|(const Node &rhs);

    Node &operator=(const Node &rhs);

    Node operator()(const Node &inner);

    ~Node() = default;

    std::string get_circuit_string();
};

GateFactory Node::GF;

Node::Node() {
    nodeName = to_string(GF.get_wire());
}

Node::Node(const Node &old) {
    nodeName = old.nodeName;
    GV = old.GV;
}

Node::Node(const std::string &p_str) {
    nodeName = p_str;
}

Node::Node(const char x) {
    nodeName = string(1,x);
}

Node Node::operator!() {
    Gate x = GF.create_not_gate(this->nodeName);
    Node s(x.getOutputNode());
    s.GV = this->GV;
    s.GV.push_back(x);
    return s;
}

Node Node::operator&(const Node &rhs) {
    Gate x = GF.create_and_gate(this->nodeName, rhs.nodeName);
    Node s(x.getOutputNode());
    s.GV = this->GV;
    s.GV.insert(std::end(s.GV), std::begin(rhs.GV), std::end(rhs.GV));
    s.GV.push_back(x);
    return s;
}

Node Node::operator|(const Node &rhs) {
    Gate x = GF.create_or_gate(this->nodeName, rhs.nodeName);
    Node s(x.getOutputNode());
    s.GV = this->GV;
    s.GV.insert(std::end(s.GV), std::begin(rhs.GV), std::end(rhs.GV));
    s.GV.push_back(x);
    return s;
}


Node& Node::operator=(const Node& rhs) {
    string output_wire = rhs.nodeName;
    if (!rhs.GV.empty()) {
        this->GV = rhs.GV;
        GV.back().change_output_node(output_wire, this->nodeName);
    }
    else this->nodeName = rhs.nodeName;
    return *this;
}

std::string Node::get_circuit_string() {
    std::string gen_out;
    for (auto & i : GV) {
        gen_out += i.getDirectiveString() + "\n";
    }
    return gen_out;
}

#endif //PROJECT_NODE_H