#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <cstdlib>
#include <fstream>
#include "expression.hpp"
#include "environment.hpp"

class Interpreter {
private:
    Expression ast;
    Environment env;
    std::string parsingerror = "";
public:
    // Default construct an Interpreter with the default environment and an
    // empty AST
    Interpreter();

    // Given a vtscript program as a std::istream, attempt to parse into an
    // internal AST return true on success, false on failure
    bool parse(std::istream & expression) noexcept;

    // Get a string describing the error encountered during parsing
    std::string getparsingerror() const;

    void printast(std::ostream & out);

    // Evaluate the current AST and return the resulting Expression
    // throws InterpreterSemanticError if a semantic error is encountered
    // the exception message string should document the nature of the semantic
    // error
    // If there is a semantic error the state of the environment is reset to how
    // it was before the evaluation started
    Expression eval();

    // Gets the list of expressions that need to be drawn
    std::vector<Drawable> getToDraw();
};
    
#endif // INTERPRETER_HPP
