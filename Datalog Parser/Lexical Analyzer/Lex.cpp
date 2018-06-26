#include "Lex.h"
#include <iostream>

void Lex::createTokens() {
    char currentChar;
    unsigned lineNumber = 1;
    input->advance();
    while(!input->isEOFile()) {
        currentChar = input->getTop();
        lineNumber = input->getCurrentLineNumber();
        switch(currentChar) {
            case ',':
                tokens.push_back(Token(COMMA, ",", lineNumber));
                input->advance();
                break;
            case '.':
                tokens.push_back(Token(PERIOD, ".", lineNumber));
                input->advance();
                break;
            case '?':
                tokens.push_back(Token(Q_MARK, "?", lineNumber));
                input->advance();
                break;
            case '(':
                tokens.push_back(Token(LEFT_PAREN, "(", lineNumber));
                input->advance();
                break;
            case ')':
                tokens.push_back(Token(RIGHT_PAREN, ")", lineNumber));
                input->advance();
                break;
            case ':': colonOrColonDash(); break;
            case '*':
                tokens.push_back(Token(MULTIPLY, "*", lineNumber));
                input->advance();
                break;
            case '+':
                tokens.push_back(Token(ADD, "+", lineNumber));
                input->advance();
                break;
            case '\'': string(); break;
            case '#': comment(); break;
            default:
            {
                if (isalpha(currentChar)) ident();
                else if (isspace(currentChar)) whitespace();
                else {
                    std::string str;
                    str += currentChar;
                    tokens.push_back(Token(UNDEFINED, str, lineNumber));
                    input->advance();
                }
            }
        }
    }
    if (input->isEOFile()) {
        tokens.push_back(Token(EOFILE, "", input->getCurrentLineNumber()));
    }
}

Token Lex::getTop() {
    Token* current = &tokens[currentTokenLoc];
    advance();
    return *current;
}


Token Lex::peek() {
    return tokens[currentTokenLoc];
}

bool Lex::assertToken(tokenType tokentype, bool throwThis) {
    if (tokens[currentTokenLoc].getTokenType() == tokentype) {
        return true;
    }
    else if (throwThis) {
        throw tokens[currentTokenLoc];
    }
    return false;
}

bool Lex::isEOFile() {
    return (tokens[currentTokenLoc].getTokenType() == EOFILE);
}


void Lex::advance() {
    if (currentTokenLoc < tokens.size() - 1) {
        currentTokenLoc++;
    }
}

void Lex::colonOrColonDash() {
    unsigned lineNumber = input->getCurrentLineNumber();
    input->advance();
    char nextChar = input->getTop();
    if (nextChar == '-') {
        tokens.push_back(Token(COLON_DASH, ":-", lineNumber));
        input->advance();
    }
    else {
        tokens.push_back(Token(COLON, ":", lineNumber));
    }
}

void Lex::string() {
    std::string str;
    str += input->getTop();
    unsigned lineNumber = input->getCurrentLineNumber();
    input->advance();
    bool reachedEndOfString = false;
    while(!reachedEndOfString) {
        char currentChar = input->getTop();
        if (currentChar == '\'') {
            input->advance();
            char nextChar = input->getTop();
            if (nextChar == '\'') { //nextChar is a , or ) etc. but then I do nothing and move on
                str += currentChar;
                str += nextChar;
                input->advance();
            }
            else {
                str += currentChar;
                reachedEndOfString = true;
            }
        }
        else if (input->isEOFile()) {
            tokens.push_back(Token(UNDEFINED, str, lineNumber));
            return;
        }
        else {
            str += currentChar;
            input->advance();
        }
    }
    tokens.push_back(Token(STRING, str, lineNumber));
    /*if(input->getTop() != EOF) input->advance(); This allows me to read the commas and paren because I advance, but I don't get the correct EOF output*/
}

void Lex::ident() {
    std::string str;
    char currentChar = input->getTop();
    unsigned lineNumber = input->getCurrentLineNumber();
    bool isKeyword = false;
    while((isalpha(currentChar) || isdigit(currentChar))) {
        str += currentChar;
        input->advance();
        currentChar = input->getTop();
    }
    if (str == "Schemes" && !isalpha(currentChar) && !isdigit(currentChar)) {
        tokens.push_back(Token(SCHEMES, str, lineNumber));
        isKeyword = true;
    }
    else if (str == "Facts" && !isalpha(currentChar) && !isdigit(currentChar)) {
        tokens.push_back(Token(FACTS, str, lineNumber));
        isKeyword = true;
    }
    else if (str == "Rules" && !isalpha(currentChar) && !isdigit(currentChar)) {
        tokens.push_back(Token(RULES, str, lineNumber));
        isKeyword = true;
    }
    else if (str == "Queries" && !isalpha(currentChar) && !isdigit(currentChar)) {
        tokens.push_back(Token(QUERIES, str, lineNumber));
        isKeyword = true;
    }
    else {
        tokens.push_back(Token(ID, str, lineNumber));
    }
}

void Lex::multiLineComment() {
    std::string str = "#|";
    unsigned lineNumber = input->getCurrentLineNumber();
    input->advance();
    bool reachedEndOfComment = false;
    while(!reachedEndOfComment) {
        char currentChar = input->getTop();
        if (currentChar == '|') {
            str += currentChar;
            input->advance();
            char nextChar = input->getTop();
            if (nextChar == '#') {
                str += nextChar;
                //tokens.push_back(Token(COMMENT, str, lineNumber));
                input->advance();
                return;
            }
        }
        else if (input->isEOFile()) {
            tokens.push_back(Token(UNDEFINED, str, lineNumber));
            return;
        }
        else {
            str += currentChar;
            input->advance();
        }
    }
}

void Lex::comment() {
    std::string str;
    str += input->getTop();
    input->advance();
    //unsigned lineNumber = input->getCurrentLineNumber();
    bool reachedEndOfComment = false;
    while(!reachedEndOfComment) {
        char currentChar = input->getTop();
        if (currentChar == '|' && str.length() < 2) {
            multiLineComment();
            return;
        }
        else if (currentChar == '\n') {
            //tokens.push_back(Token(COMMENT, str, lineNumber));
            input->advance();
            return;
        }
        else if (input->isEOFile()) {
            //tokens.push_back(Token(COMMENT, str, lineNumber));
            return;
        }
        else {
            str += currentChar;
            input->advance();
        }
    }
}

void Lex::whitespace() {
    while(isspace(input->getTop())) {
        input->advance();
    }
}
