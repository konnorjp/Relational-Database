#include "Token.h"
#include <sstream>

std::string Token::getValue() {
    return value;
}

tokenType Token::getTokenType() {
    return tokentype;
}

unsigned int Token::getLineNumber() {
    return lineNumber;
}

std::string Token::getTypeStringOrId() {
    std::string typ;
    switch(tokentype) {
        case ID: typ = "ID"; break;
        case STRING: typ = "STRING"; break;
        default: break;
    }
    return typ;
}

std::string Token::print() {
    std::stringstream printStatement;
    std::string typ;
    switch(tokentype) {
        case COMMA: typ = "COMMA"; break;
        case PERIOD: typ = "PERIOD"; break;
        case Q_MARK: typ = "Q_MARK"; break;
        case LEFT_PAREN: typ = "LEFT_PAREN"; break;
        case RIGHT_PAREN: typ = "RIGHT_PAREN"; break;
        case COLON: typ = "COLON"; break;
        case COLON_DASH: typ = "COLON_DASH"; break;
        case MULTIPLY: typ = "MULTIPLY"; break;
        case ADD: typ = "ADD"; break;
        case SCHEMES: typ = "SCHEMES"; break;
        case FACTS: typ = "FACTS"; break;
        case RULES: typ = "RULES"; break;
        case QUERIES: typ = "QUERIES"; break;
        case ID: typ = "ID"; break;
        case STRING: typ = "STRING"; break;
        case COMMENT: typ = "COMMENT"; break;
        case WHITESPACE: typ = "WHITESPACE"; break;
        case UNDEFINED: typ = "UNDEFINED"; break;
        case EOFILE: typ = "EOF"; break;
        default: break;
    }
    printStatement << "(" << typ << ",\"" << value << "\"," << lineNumber << ")";
    return printStatement.str();
}
