#ifndef Lex_h
#define Lex_h

#include <iostream>
#include <vector>
#include "InputChars.h"
#include "Token.h"

class Lex {
public:
    Lex(char* filename) {
        InputChars* inputPtr = new InputChars(filename);
        this->input = inputPtr;
        currentTokenLoc = 0;
        createTokens();
    }
    ~Lex() {}
    
    void createTokens();
    Token getTop();
    Token peek();
    bool assertToken(tokenType tokentype, bool throwThis);
    bool isEOFile();
    void advance();
    unsigned long getSize() { return tokens.size();}
    
private:
    void colonOrColonDash();
    void string();
    void ident();
    void comment();
    void multiLineComment();
    void whitespace();
    
    int currentTokenLoc;
    InputChars* input;
    std::vector<Token> tokens;
};

#endif 
