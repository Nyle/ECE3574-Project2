#include <cmath>
#include <functional>
#include "environment.hpp"
#include "interpreter_semantic_error.hpp"

void Environment::define(std::string symbol, EnvFunc func) {
    if (this->map.count(symbol)) {
        throw InterpreterSemanticError(
            "Error: can not redefine symbol: \"" + symbol + "\"");
    }
    this->map[symbol] = func;
}

void Environment::define(std::string symbol, Expression exp) {
    this->define(symbol, [exp](Args args, Environment &env) {
        return exp;
    });
}

EnvFunc Environment::retrieve(std::string symbol) {
    if (this->map.count(symbol)) {
        return this->map[symbol];
    } 
    throw InterpreterSemanticError(
        "Error: undefined symbol: \"" + symbol + "\"");
}

Environment::Environment() {
    this->todraw = std::vector<Drawable>();
    this->map = std::map<std::string, EnvFunc>();
    // Put in default environment
    this->define("define", DefineFn());
    this->define("begin", BeginFn());
    this->define("if", IfFn());
    this->define("not", NotFn());
    this->define("and", BinaryBoolFn(std::logical_and<bool>()));
    this->define("or", BinaryBoolFn(std::logical_or<bool>()));
    this->define("<", CmpFn(std::less<float>()));
    this->define("<=", CmpFn(std::less_equal<float>()));
    this->define(">", CmpFn(std::greater<float>()));
    this->define(">=", CmpFn(std::greater_equal<float>()));
    this->define("=", CmpFn(std::equal_to<float>()));
    this->define("+", PlusMulFn(std::plus<float>()));
    this->define("*", PlusMulFn(std::multiplies<float>()));
    this->define("-", SubFn());
    this->define("/", DivFn());
    this->define("pi", Expression(atan2(0, -1)));
    this->define("draw", DrawFn());
    this->define("point", PointFn());
    this->define("line", LineFn());
    this->define("arc", ArcFn());
    this->define("sin", SinFn());
    this->define("cos", CosFn());
    this->define("arctan", ArctanFn());
}

void Environment::addToDraw(Drawable exp) {
    this->todraw.push_back(exp);
}

std::vector<Drawable> Environment::getToDraw() {
    std::vector<Drawable> res = this->todraw;
    this->todraw = std::vector<Drawable>();
    return res;
}
