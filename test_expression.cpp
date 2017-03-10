#include "catch.hpp"

#include <string>
#include <sstream>

#include "expression.hpp"
#include "interpreter_syntax_error.hpp"
#include "interpreter_semantic_error.hpp"

TEST_CASE("Test copying expression of type none", "[expression]") {
    Expression exp = Expression();

    REQUIRE_NOTHROW(Expression copy = Expression(exp));
}

TEST_CASE("Test converting None type expression to string", "[expression]") {
    Expression exp = Expression();
    std::string expasstring = exp.to_string();
    REQUIRE(expasstring == "None");
}

TEST_CASE("Test converting Symbol type expression to string", "[expression]") {
    std::string attom = "test";
    Expression exp = Expression(attom);
    std::string expasstring = exp.to_string();
    REQUIRE(expasstring == attom);
}

TEST_CASE("Test adding argument to None type expression",
          "[expression]") {
    Expression arg = Expression(5.0);
    Expression exp = Expression();
    REQUIRE_THROWS_AS(exp.addargument(arg), InterpreterSyntaxError);
}

TEST_CASE("Test adding argument to Float type expression",
          "[expression]") {
    Expression arg = Expression(5.0);
    Expression exp = Expression(2.0);
    REQUIRE_THROWS_AS(exp.addargument(arg), InterpreterSyntaxError);
}

TEST_CASE("Test adding argument to Bool type expression",
          "[expression]") {
    Expression arg = Expression(5.0);
    Expression exp = Expression(true);
    REQUIRE_THROWS_AS(exp.addargument(arg), InterpreterSyntaxError);
}

TEST_CASE("Test adding argument to String type expression",
          "[expression]") {
    std::string attom = "test";
    Expression arg = Expression(5.0);
    Expression exp = Expression(attom);
    REQUIRE_NOTHROW(exp.addargument(arg));
}

TEST_CASE("Test getting Symbol value from non Symbol expression",
          "[expression]") {
    Expression exp = Expression();
    REQUIRE_THROWS_AS(exp.getsymbol(), InterpreterSemanticError);
}
