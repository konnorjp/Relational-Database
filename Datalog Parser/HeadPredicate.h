#ifndef HeadPredicate_h
#define HeadPredicate_h

#include "Predicate.h"

class HeadPredicate {
public:
    HeadPredicate(Lex* lex);
    ~HeadPredicate() {}
    std::string toString();
    Id* getHeadId() { return headId; };
    std::vector<Id*> getIds() { return ids; };
private:
    Id* headId;
    std::vector<Id*> ids;
};


#endif /* HeadPredicate_h */
