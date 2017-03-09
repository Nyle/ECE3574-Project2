#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <cstdlib>
#include <string>
#include <vector>

class Environment;
class Expression;

typedef std::vector<Expression> Args;

enum Type {None, Bool, Number, Symbol};

class Expression {
private:
    // Fields for the attom value
    bool b;
    double d;
    std::string s;
    // Fields for the type of attom value
    Type type;
    Args arguments;
public:
    // Default construct an Expression of type None; for cases with errors
    Expression();
    // Construct an Expression with a single Boolean atom with value
    Expression(bool value);
    // Construct an Expression with a single Number atom with value
    Expression(double value);
    // Construct an Expression with a single Symbol atom with value
    Expression(const std::string & value);
    // Copy constructor
    Expression(const Expression & exp);
    // Returns the symbol
    std::string getsymbol() const;
    // returns the literal numerical value
    double getnumber() const;
    // Evaluates and returns numerical result
    double getnumber(Environment & env) const;
    // returns the literal boolean value
    bool getbool() const;
    // Evaluates and returns boolean result
    bool getbool(Environment & env) const;
    // Equality operator for two Expressions, two expressions are equal if the
    // have the same type, atom value, and number of arguments
    bool operator==(const Expression & exp) const noexcept;
    // Add an expression as the last argument
    void addargument(Expression exp);
    // Get the arguments
    Args getargs() const;
    // Return the result of evaluating this expression
    Expression eval(Environment & env) const;
    // Return the attom as a string
    std::string to_string() const;
};

#endif // EXPRESSION_HPP

// Overload of << to allow easy printing
std::ostream& operator<<(std::ostream &strm, const Expression &exp);
