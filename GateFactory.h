
#ifndef PROJECT_GF_H
#define PROJECT_GF_H

#include "Gates.h"

class GateFactory {

private:
    int wire_counter;
    int M_counter;

public:
    GateFactory();

    G_AND create_and_gate(const string &input_a, const string &input_b);

    G_OR create_or_gate(const string &input_a, const string &input_b);

    G_NOT create_not_gate(const string &input);

    int get_wire();

    ~GateFactory() = default;

};

GateFactory::GateFactory() {
    wire_counter = 1;
    M_counter = 1;
}

G_NOT GateFactory::create_not_gate(const string &input) {
    wire_counter += 1;
    M_counter += 2;
    return G_NOT(input, wire_counter - 1, M_counter - 2);
}

G_AND GateFactory::create_and_gate(const string &input_a, const string &input_b) {
    wire_counter += 3;
    M_counter += 6;
    return G_AND(input_a, input_b, wire_counter - 3, M_counter - 6);
}

G_OR GateFactory::create_or_gate(const string &input_a, const string &input_b) {
    wire_counter += 3;
    M_counter += 6;
    return G_OR(input_a, input_b, wire_counter - 3, M_counter - 6);
}

int GateFactory::get_wire() {
    return wire_counter++;
}

#endif //PROJECT_GF_H