#ifndef INPUTCHARS_H_
#define INPUTCHARS_H_

#include <sstream>
#include <fstream>

class InputChars {
public:
    InputChars(char* filename) {
        char nextChar;
        std::ifstream fs;
        fs.open(filename);
        while(!fs.fail()) {
            fs.get(nextChar);
            if(fs.fail()) nextChar = EOF;
            inputList << nextChar;
        }
        fs.close();
        currentLineNumber = 1;
    }
    ~InputChars() {}
    
    char getTop();
    bool isNextCharA(char c);
    bool isEOFile();
    unsigned getCurrentLineNumber();
    void advance();
private:
    std::stringstream inputList;
    unsigned currentLineNumber;
    char currentChar;
};

#endif 
