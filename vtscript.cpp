#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "tokenize.hpp"
#include "expression.hpp"
#include "environment.hpp"
#include "interpreter.hpp"
#include "interpreter_semantic_error.hpp"
#include <functional>

int repl();
int run(std::istream &in, Interpreter & interp);
int run(std::istream & in);

int main(int argc, char * argv[]) {
    if (argc == 1) { // REPL
        return repl();
    }
    if (argc == 3 && std::string(argv[1]) == "-e") { // from cmdline
        std::stringstream lstream(argv[2]);
        return run(lstream);
    }
    if (argc == 2 && std::string(argv[1]).substr(0, 2) == "-e") {
        // from cmdline
        std::stringstream lstream(std::string(argv[1]).substr(2));
        return run(lstream);
    }
    if (argc == 2) {     // Run from a file
        std::ifstream in(argv[1]);
        if (!in.is_open()) {
            std::cerr << "Error: unable to open the given file\n";
            return EXIT_FAILURE;
        }
        return run(in);
    } 
    std::cerr << "Error: Too many inputs\n";
    return EXIT_FAILURE;
}

// get input from repl and evaluate untill eof
int repl() {
    Interpreter interp = Interpreter();
    std::string line;
    std::cout << "vtscript> ";
    while (std::getline(std::cin, line)) {
        if (line.size() != 0) {// ignore empty input
            std::stringstream lstream(line);
            if (run(lstream, interp) == EXIT_FAILURE) {
                interp = Interpreter(); // reset on error
            }
        }
        std::cout << "vtscript> ";
    }
    return EXIT_SUCCESS;
}

int run(std::istream &in, Interpreter & interp) {
   if (!interp.parse(in)) {
       std::cerr << interp.getparsingerror() << "\n";
       return EXIT_FAILURE;
    }
    try {
        std::cout << interp.eval() << "\n";
    } catch (InterpreterSemanticError e) {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

// parse and run the given 
int run(std::istream & in) {
    Interpreter interp = Interpreter();
    return run(in, interp);
}
