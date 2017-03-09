#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <queue>
#include <istream>

class Expression;

typedef std::string Token;
typedef std::queue<Token> TokenList;

// Split the given stream into a set of tokens, stored as a vector of strings
TokenList tokenize(std::istream & in);

// Construct an AST from the list of tokens
Expression constructast(TokenList & tokens);

#endif
