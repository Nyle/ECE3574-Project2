#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <cstdlib>
#include <string>
#include <vector>
#include <tuple>

class Environment;
class Expression;

typedef std::vector<Expression> Args;
typedef std::tuple<double, double> Point;

enum Type {NONE, BOOL, NUMBER, SYMBOL, POINT, LINE, ARC};

struct Line {
    Point p1, p2;
    bool operator==(const Line & l) const { return p1 == l.p1 && p2 == l.p2;  }
};

struct Arc {
    Point center, start;
    double angle;
    bool operator==(const Arc & a) const {
        return center == a.center && start == a.start && angle == a.angle;
    }
};

struct Drawable {
    Type type;
    Point point;
    Line line;
    Arc arc;
};
    
class Expression {
private:
    // Fields for the attom value
    bool b;
    double d;
    std::string s;
    Point p;
    Line l;
    Arc a;
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
    // Construct an Expression with a single Point attom with value
    Expression(const Point & value);
    // Construct an Expression with a single Line attom with value
    Expression(const Point & p1, const Point & p2);
    // Construct an Expression with a single Arc attom with value
    Expression(const Point & center,
               const Point & start,
               double angle);
    // Copy constructor
    Expression(const Expression & exp);
    // Returns the symbol
    std::string getsymbol() const;
    // Evaluates and returns numerical result
    double getnumber(Environment & env) const;
    // Evaluates and returns boolean result
    bool getbool(Environment & env) const;
    // Returns literal Point value
    Point getpoint(Environment & env) const;
    // Returns literal drawable value
    Drawable getdrawable(Environment & env) const;
    // Equality operator for two Expressions, two expressions are equal if the
    // have the same type, atom value, and number of arguments
    bool operator==(const Expression & exp) const noexcept;
    // Add an expression as the last argument
    void addargument(Expression exp);
    // Get the arguments
    Args getargs() const;
    // Return the result of evaluating this expression
    Expression eval(Environment & env) const;
    // Return the result of evaluating this expression, checking that the
    // result is the correct type
    Expression eval(Environment & env, Type t) const;
    // Return the attom as a string
    std::string to_string() const;
    // Returns the type if it is one of the drawing types. If it is not a
    // drawing type this throws an error
    Type getdrawtype() const;
};

// Overload of << to allow easy printing
std::ostream& operator<<(std::ostream &strm, const Expression &exp);

#endif // EXPRESSION_HPP

