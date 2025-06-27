//
// Created by User on 27/06/2025.
//

#ifndef SCANNER_H
#define SCANNER_H


#pragma once

#include <string>
#include "Token.h"

using namespace std;

class Scanner {
public:
    explicit Scanner(string input);

    Token* getNextToken();

private:
    std::string input;
    size_t position;

    char currentChar() const;

    void advance();

    void skipWhitespace();
    void skipWhitespaceAndComments();
    Token* identifier();

    Token* number();

    Token* singleCharacterToken(Token::Type type);

    static bool isAlpha(char c);

    static bool isDigit(char c);

    static bool isAlphaNumeric(char c);
};

void test_scanner(Scanner* scanner);

#endif //SCANNER_H
