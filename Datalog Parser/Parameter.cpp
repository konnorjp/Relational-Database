#include "Parameter.h"
#include "Id.h"
#include "StringClass.h"
#include "Expression.h"

Parameter* Parameter::createParameter(Lex* lex) {
    if (lex->assertToken(ID, false)) {
        return new Id(lex);
    }
    else if (lex->assertToken(STRING, false)) {
        return new StringClass(lex);
    }
    else {
        lex->assertToken(LEFT_PAREN, true);
        return new Expression(lex);
    }
}
