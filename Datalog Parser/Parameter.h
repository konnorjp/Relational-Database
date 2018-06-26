#ifndef Parameter_h
#define Parameter_h

#include <iostream>
#include "Lex.h"

class Parameter {
public:
    Parameter() {}
    virtual ~Parameter(){}
    virtual std::string toString() = 0;
    virtual std::string getType() = 0;
    static Parameter* createParameter(Lex* lex);
};

#endif /* Parameter_h */
