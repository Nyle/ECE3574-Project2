#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <map>
#include <string>
#include <vector>
#include "expression.hpp"
#include "environmentprocedures.hpp"

class Environment {
private:
    std::map<std::string, EnvFunc> map;    
public:
    // default constructor
    Environment();
    // Define a symbol. Returns true on success, false on failure (function)
    void define(std::string symbol, EnvFunc func);
    // Define a symbol. Returns true on success, false on failure (literal exp)
    void define(std::string symbol, Expression exp);
    // Retrieve the given symbol. Returns None Expression if symbol is not
    // defined
    EnvFunc retrieve(std::string symbol);
};


#endif // ENVIRONMENT_H
