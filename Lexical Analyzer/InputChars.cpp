#include "InputChars.h"
#include <iostream>

char InputChars::getTop() {
    return currentChar;
}

bool InputChars::isNextCharA(char c) {
    return (inputList.peek() == c);
}

bool InputChars::isEOFile() {
    return isNextCharA(EOF);
}

unsigned InputChars::getCurrentLineNumber() {
    return currentLineNumber;
}

void InputChars::advance() {
    inputList.get(currentChar);
    if (inputList.fail()) currentChar = EOF;
    if (currentChar == '\n') currentLineNumber++;
}
