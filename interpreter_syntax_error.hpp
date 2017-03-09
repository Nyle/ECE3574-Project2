#ifndef INTERPRETER_SYNTAX_ERROR_HPP
#define INTERPRETER_SYNTAX_ERROR_HPP

#include <exception>
#include <stdexcept>

class InterpreterSyntaxError: public std::runtime_error {
public:
    InterpreterSyntaxError(const std::string& message):
        std::runtime_error(message){};
};


#endif // INTERPRETER_SEMANTIC_ERROR_HPP
