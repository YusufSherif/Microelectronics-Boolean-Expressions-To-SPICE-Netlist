//
// Created by Yusuf Sherif on 5/12/20.
//

#ifndef PROJECT_DIRECTIVE_H
#define PROJECT_DIRECTIVE_H

#include <string>

class Directive {
private:
    std::string name;
    std::string drain;
    std::string gate;
    std::string source;
    std::string body;
    std::string type;
public:
    Directive() = default;

    Directive(const std::string &p_name, const std::string &p_drain, const std::string &p_gate,
              const std::string &p_source, const std::string &p_body,
              const std::string &p_type) {
        setDirective(p_name, p_drain, p_gate, p_source, p_body, p_type);
    }

    void
    setDirective(const std::string &p_name, const std::string &p_drain, const std::string &p_gate,
                 const std::string &p_source, const std::string &p_body,
                 const std::string &p_type) {
        name = p_name;
        drain = p_drain;
        gate = p_gate;
        source = p_source;
        body = p_body;
        type = p_type;
    }

    std::string toString() {
        return ("M" + name) + " " + drain + " " + gate + " " + source + " " + body + " " + type;
    }

    void replace_node_matches_with(const std::string &old, const std::string &replacement) {
        if (drain == old) drain = replacement;
        if (gate == old) gate = replacement;
        if (source == old) source = replacement;
        if (body == old) body = replacement;
        if (type == old) type = replacement;
    }

    ~Directive() = default;
};


#endif //PROJECT_DIRECTIVE_H
