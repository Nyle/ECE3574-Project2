#include "expression.hpp"
#include "environment.hpp"
#include "interpreter_semantic_error.hpp"
#include "interpreter_syntax_error.hpp"
#include <iostream>
#include <sstream>

Expression::Expression() {
    this->type = None;
    this->arguments = Args();
}

Expression::Expression(bool value) : Expression() {
    this->type = Bool;
    this->b = value;
}

Expression::Expression(double value) : Expression() {
    this->type = Number;
    this->d = value;
}

Expression::Expression(const std::string & value) : Expression() {
    this->type = Symbol;
    this->s = value;
}

Expression::Expression(const Expression & exp) {
    this->type = exp.type;
    switch(this->type) {
    case None:
        break;
    case Bool:
        this->b = exp.b;
        break;
    case Number:
        this->d = exp.d;
        break;
    case Symbol:
        this->s = exp.s;
        break;
    }
    this->arguments = Args(exp.arguments);
}

std::string Expression::getsymbol() const {
    if (this->type != Symbol) {
        throw InterpreterSemanticError(
            "Error: expected expression to be of type Symbol");
    }
    return this->s;
}

double Expression::getnumber() const {
    if (this->type != Number) {
        throw InterpreterSemanticError(
            "Error: expected expression to evaluate to Number");
    }
    return this->d;
}

double Expression::getnumber(Environment & env) const {
    return this->eval(env).getnumber();
}

bool Expression::getbool() const {
    if (this->type != Bool) {
        throw InterpreterSemanticError(
            "Error: expected expression to evaluate to Bool");
    }
    return this->b;
}

bool Expression::getbool(Environment & env) const {
    return this->eval(env).getbool();
}

bool Expression::operator==(const Expression & exp) const noexcept {
    return this->type == exp.type && ( // Same type
        // Same value
        this->type == None ||
        (this->type == Bool && this->b == exp.b) ||
        (this->type == Number && this->d == exp.d) ||
        (this->type == Symbol && this->s == exp.s)) &&
        // Same number of arguments
        this->arguments.size() == exp.arguments.size();
}

void Expression::addargument(Expression exp) {
    if (this->type != Symbol) {
        throw InterpreterSyntaxError(
            "Error: only symbols can have arguments");
    }
    this->arguments.push_back(exp);
}

Args Expression::getargs() const {
    return this->arguments;
}

Expression Expression::eval(Environment & env) const {
    if (this->type != Symbol) { return *this; }
    return env.retrieve(this->s)(this->arguments, env);
}

std::string Expression::to_string() const {
    std::stringstream tmp;
    switch (this->type) {
    case None:
        return "()";
        break;
    case Bool:
        return (this->b ? "True" : "False");
        break;
    case Number:
        tmp << this->d;
        return tmp.str();
        break;
    case Symbol:
        return this->s;
    }
}

std::ostream& operator<<(std::ostream &strm, const Expression &exp) {
    strm << "(" << exp.to_string();
    for (const auto &arg: exp.getargs()) { strm << arg; }
    strm << ")";
    return strm;
}
