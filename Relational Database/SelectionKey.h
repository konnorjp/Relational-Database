#ifndef SelectionKey_h
#define SelectionKey_h

#include <iostream>
#include "Row.h"

class SelectionKey {
public:
    SelectionKey(){}
    virtual ~SelectionKey(){}
    virtual bool satisfies(Row row) = 0;
};

#endif /* SelectionKey_h */
