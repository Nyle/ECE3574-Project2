#include "expression.hpp"
#include "environment.hpp"
#include "interpreter_semantic_error.hpp"
#include "interpreter_syntax_error.hpp"
#include <iostream>
#include <sstream>
#include <cmath>

Expression::Expression() {
    this->type = NONE;
    this->arguments = Args();
}

Expression::Expression(bool value) : Expression() {
    this->type = BOOL;
    this->b = value;
}

Expression::Expression(double value) : Expression() {
    this->type = NUMBER;
    this->d = value;
}

Expression::Expression(const std::string & value) : Expression() {
    this->type = SYMBOL;
    this->s = value;
}

Expression::Expression(const Point & value) : Expression() {
    this->type = POINT;
    this->p = value;
}

Expression::Expression(const Point & p1, const Point & p2) : Expression() {
    this->type = LINE;
    this->l = {p1, p2};
}

Expression::Expression(const Point & center, const Point & start,
                       double angle) : Expression() {
    this->type = ARC;
    this->a = {center, start, angle};
}

Expression::Expression(const Expression & exp) {
    this->type = exp.type;
    switch(this->type) {
    case NONE:
        break;
    case BOOL:
        this->b = exp.b;
        break;
    case NUMBER:
        this->d = exp.d;
        break;
    case SYMBOL:
        this->s = exp.s;
        break;
    case POINT:
        this->p = exp.p;
    case LINE:
        this->l = exp.l;
    case ARC:
        this->a = exp.a;
    }
    this->arguments = Args(exp.arguments);
}

std::string Expression::getsymbol() const {
    if (this->type != SYMBOL) {
        throw InterpreterSemanticError(
            "Error: expected expression to be of type Symbol");
    }
    return this->s;
}

double Expression::getnumber(Environment & env) const {
    return this->eval(env, NUMBER).d;
}

bool Expression::getbool(Environment & env) const {
    return this->eval(env, BOOL).b;
}

Point Expression::getpoint(Environment & env) const {
    return this->eval(env, POINT).p;
}

Line Expression::getline(Environment & env) const {
    return this->eval(env, LINE).l;
}

Arc Expression::getarc(Environment & env) const {
    return this->eval(env, ARC).a;
}

// Compare if a and b are equal to within acceptable machine arithmatic error
bool almost_equal(double a, double b) {
    return std::abs(a - b) < std::numeric_limits<double>::epsilon();
}

bool Expression::operator==(const Expression & exp) const noexcept {
    return this->type == exp.type && ( // Same type
        // Same value
        this->type == NONE ||
        (this->type == BOOL && this->b == exp.b) ||
        (this->type == NUMBER && almost_equal(this->d, exp.d)) ||
        (this->type == SYMBOL && this->s == exp.s) ||
        (this->type == POINT && this->p == exp.p) ||
        (this->type == LINE && this->l == exp.l) ||
        (this->type == ARC && this->a == exp.a)) &&
        // Same number of arguments
        this->arguments.size() == exp.arguments.size();
}

void Expression::addargument(Expression exp) {
    if (this->type != SYMBOL) {
        throw InterpreterSyntaxError(
            "Error: only symbols can have arguments");
    }
    this->arguments.push_back(exp);
}

Args Expression::getargs() const {
    return this->arguments;
}

Expression Expression::eval(Environment & env) const {
    if (this->type != SYMBOL) { return *this; }
    return env.retrieve(this->s)(this->arguments, env);
}

Expression Expression::eval(Environment & env, Type t) const {
    Expression res = this->eval(env);
    if (res.type != t) {
        throw InterpreterSemanticError(
            "Error: expected expression to evaluate to a different type");
    }
    return res;
}

std::string point_to_string(Point p) {
    return std::to_string(std::get<0>(p)) + "," +
        std::to_string(std::get<1>(p));
}

std::string Expression::to_string() const {
    std::stringstream tmp;
    switch (this->type) {
    case NONE:
        return "None";
        break;
    case BOOL:
        return (this->b ? "True" : "False");
        break;
    case NUMBER:
        tmp << this->d;
        return tmp.str();
        break;
    case SYMBOL:
        return this->s;
    case POINT:
        return point_to_string(this->p);
    case LINE:
        return "(" + point_to_string(this->l.p1) + "),(" +
            point_to_string(this->l.p2) + ")";
    case ARC:
        return "(" + point_to_string(this->a.center) + "),(" +
            point_to_string(this->a.start) + ") " +
            std::to_string(this->a.angle);
    }
}

std::ostream& operator<<(std::ostream &strm, const Expression &exp) {
    strm << "(" << exp.to_string();
    for (const auto &arg: exp.getargs()) { strm << arg; }
    strm << ")";
    return strm;
}
