#ifndef Scheme_h
#define Scheme_h

#include <vector>
#include "Id.h"
#include "Token.h"
#include "Lex.h"

class Scheme {
public:
    Scheme(Lex* lex);
    ~Scheme(){
        for(unsigned long i = 0; i < columnNames.size(); i++) {
            delete columnNames[i];
        }
    }
    std::string toString();
    Id* getSchemeId() { return schemeId; };
    std::vector<Id*> getColumnNames() { return columnNames; };
private:
    Id* schemeId;
    std::vector<Id*> columnNames;
};

#endif /* Scheme_h */
