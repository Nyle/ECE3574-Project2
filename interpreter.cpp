#include "interpreter.hpp"
#include "tokenize.hpp"
#include "interpreter_syntax_error.hpp"
#include "interpreter_semantic_error.hpp"

// For debugging
#include <iostream>

Interpreter::Interpreter() {
    this->env = Environment();
}

bool Interpreter::parse(std::istream & expression) noexcept {
    this->parsingerror = "";
    try {
        TokenList tokens = tokenize(expression);
        if (tokens.size() == 0) {
            this->parsingerror = "Error: program can not be blank";
            return false;
        }
        if (tokens.front() != "(") {
            this->parsingerror = "Error: program must start with '('";
            return false;
        }
        this->ast = constructast(tokens);
        if (tokens.size() != 0) {
            this->parsingerror = "Error: Extra Input";
            return false;
        }
    } catch(InterpreterSyntaxError & e) {
        this->parsingerror = e.what();
        return false;
    }
    return true;
}

std::string Interpreter::getparsingerror() const {
    return this->parsingerror;
}

Expression Interpreter::eval() {
    Environment bu = this->env;
    try {
        return this->ast.eval(this->env);
    } catch (InterpreterSemanticError e) {
        // Reset the environment to the prior state on error
        this->env = bu;
        throw e;
    }
}

std::vector<Drawable> Interpreter::getToDraw() {
    return this->env.getToDraw();
}
