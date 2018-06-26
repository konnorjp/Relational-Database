#ifndef Query_h
#define Query_h

#include "Predicate.h"
#include "Token.h"
#include "Lex.h"

class Query {
public:
    Query(Lex* lex) {
        predicate = new Predicate(lex);
        lex->assertToken(Q_MARK, true);
        lex->advance();
    }
    ~Query() {
        delete predicate;
    }
    std::string toString() {
        std::stringstream result;
        result << "  " << predicate->toString() << "?";
        return result.str();
    }
    Predicate* getPredicate() { return predicate; };
private:
    Predicate* predicate;
};

#endif /* Query_h */
