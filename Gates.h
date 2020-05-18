#ifndef PROJECT_Gs_H
#define PROJECT_Gs_H

#include <iostream>
#include <string>
#include <vector>

#include "Directive.h"

using namespace std;

/*****************************************************************/

class Gate {
protected:
    std::vector<Directive> d_vec;
    std::string output_node;

    void push_directive(const Directive& d);
    //std::string get_ltspice_node_string(const std::string& w);


public:
    Gate() = default;

    Gate (const Gate &old_obj);

    std::string getDirectiveString();

    const std::string& getOutputNode();

    void change_output_node(const std::string& old_n, const std::string& new_n);

    ~Gate() = default;
};

/************/

Gate::Gate(const Gate &old_obj) {
    this->d_vec = old_obj.d_vec;
    output_node = old_obj.output_node;
}

void Gate::push_directive(const Directive& d) {
    d_vec.push_back(d);
}

std::string Gate::getDirectiveString() {
    std::string directive_string;
    for (size_t i = 0; i < d_vec.size(); i++) {
        directive_string += d_vec[i].toString() + "\n";
    }
    return directive_string;
}

const std::string& Gate::getOutputNode() {
    return output_node;
}

void Gate::change_output_node(const std::string& old_n, const std::string& new_n) {
    for (int i = 0; i < d_vec.size(); ++i) {
        d_vec[i].replace_node_matches_with(old_n, new_n);
    }
}

//std::string Gate::get_ltspice_node_string(const string &w) {
//    int l = int(3)-w.size();
//    if(l<=0)
//        return w;
//    else
//        return "N"+std::string(l,'0')+w;
//}

/*****************************************************************/

class G_AND : public Gate {
private:

public:
    G_AND(const string& input_a, const string& input_b, int w_counter, int m_counter);
};

/************/

G_AND::G_AND(const string& input_a, const string& input_b, int w_counter, int m_counter) {
    std::string pmos_1_d = to_string(w_counter++);
    std::string nmos_1_s = to_string(w_counter++);
    this->output_node = to_string(w_counter++);

    //Mname drain gate source body type
    push_directive(Directive((to_string(m_counter++)), pmos_1_d, input_b, "vdd", "vdd", "PMOS"));
    push_directive(Directive((to_string(m_counter++)), pmos_1_d, input_a, "vdd", "vdd", "PMOS"));
    push_directive(Directive((to_string(m_counter++)), this->output_node, pmos_1_d, "vdd", "vdd", "PMOS")); //part of Inverter

    push_directive(Directive((to_string(m_counter++)), pmos_1_d, input_a, nmos_1_s, nmos_1_s, "NMOS"));
    push_directive(Directive((to_string(m_counter++)), nmos_1_s, input_b, "0", "0", "NMOS"));
    push_directive(Directive((to_string(m_counter++)), this->output_node, pmos_1_d, "0", "0", "NMOS")); //part of Inverter
}

/*****************************************************************/

class G_OR : public Gate {
private:

public:
    G_OR(const string& input_a, const string& input_b, int w_counter, int m_counter);
};

/************/

G_OR::G_OR(const string& input_a, const string& input_b, int w_counter, int m_counter) {
    std::string pmos_1_d = to_string(w_counter++);
    std::string pmos_2_d = to_string(w_counter++);
    this->output_node = to_string(w_counter++);

    //Mname drain gate source body type
    push_directive(Directive((to_string(m_counter++)), pmos_1_d, input_a, "vdd", "vdd", "PMOS"));
    push_directive(Directive((to_string(m_counter++)), pmos_2_d, input_b, pmos_1_d, pmos_1_d, "PMOS"));
    push_directive(Directive((to_string(m_counter++)), this->output_node, pmos_2_d, "vdd", "vdd", "PMOS")); //part of Inverter

    push_directive(Directive((to_string(m_counter++)), pmos_2_d, input_a, "0", "0", "NMOS"));
    push_directive(Directive((to_string(m_counter++)), pmos_2_d, input_b, "0", "0", "NMOS"));
    push_directive(Directive((to_string(m_counter++)), this->output_node, pmos_2_d, "0", "0", "NMOS")); //part of Inverter

}

/*****************************************************************/

class G_NOT : public Gate {
private:

public:
    G_NOT(const string& input, int w_counter, int m_counter);
};

/************/

G_NOT::G_NOT(const string& input, int w_counter, int m_counter) {
    this->output_node = to_string(w_counter++);

    push_directive(Directive((to_string(m_counter++)), this->output_node, input, "vdd", "vdd", "PMOS"));
    push_directive(Directive((to_string(m_counter++)), this->output_node, input, "0", "0", "NMOS"));
}

/*****************************************************************/

#endif //PROJECT_Gs_H