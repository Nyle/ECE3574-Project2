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
    std::vector<Drawable> todraw;
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
    // Add a new expression to draw
    void addToDraw(Drawable exp);
    // Get the list of expressions that need to be drawn. Clears the list of
    // Expressions to draw
    std::vector<Drawable> getToDraw();
};


#endif // ENVIRONMENT_H
