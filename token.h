//
// Created by User on 27/06/2025.
//

#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

class Token {
public:
    enum Type {
        PROGRAM,
        VAR,
        INTEGER,
        LONGINT,
        BOLEAN,
        FUNCTION,
        BEGIN,
        END,
        IF,
        THEN,
        ELSE,
        FOR,
        TO,
        DO,
        WRITELN,
        IDENTIFIER,
        INTEGER_LITERAL,
        ASSIGN,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        EQUAL,
        NOT_EQUAL,
        LESS,
        LESS_EQUAL,
        GREATER,
        GREATER_EQUAL,
        SEMICOLON,
        COLON,
        COMMA,
        PERIOD,
        LEFT_PAREN,
        RIGHT_PAREN,
        EOF_TOKEN,
        ERROR,
        UNKNOWN,
        CARET,//^
        ARRAY,
        OF,
        LEFT_BRACKET,
        RIGHT_BRACKET,
        DOT_DOT
    };

    Type type;
    std::string text;

    explicit Token(Type type);

    Token(Type type, const string& c);

    Token(Type type, const std::string& source, int first, int last);

    friend std::ostream& operator<<(std::ostream& outs, const Token& tok);

    friend std::ostream& operator<<(std::ostream& outs, const Token* tok);
};


#endif //TOKEN_H
