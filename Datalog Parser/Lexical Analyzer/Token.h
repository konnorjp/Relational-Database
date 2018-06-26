/*
 Class: Token
 */
 
#ifndef Token_h
#define Token_h

#include <iostream>

enum tokenType { COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, WHITESPACE, UNDEFINED, EOFILE };

class Token {
public:
    Token(){}
    Token(tokenType tokentype, std::string value, unsigned lineNumber) {
        this->value = value;
        this->tokentype = tokentype;
        this->lineNumber = lineNumber;
    }
    ~Token() {}
    
    /* Returns the value of the token */
    std::string getValue();
    
    /* Returns the tokenType of the token */
    tokenType getTokenType();
    
    /* Returns lineNumber of the token */
    unsigned int getLineNumber();
    
    // Return type STRING or ID
    std::string getTypeStringOrId();
    
    std::string print();
    
private:
    std::string value;
    tokenType tokentype;
    unsigned int lineNumber;
};

#endif
