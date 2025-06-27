//
// Created by User on 27/06/2025.
//

#include "token.h"
#include <iostream>


using namespace std;

Token::Token(Type type) : type(type) { text = ""; }

Token::Token(Type type, const string& c) : type(type) { text = c; }

Token::Token(Type type, const string& source, int first, int last) : type(type) {
    text = source.substr(first, last);
}

std::ostream& operator<<(std::ostream& outs, const Token& tok) {
    switch (tok.type) {
    case Token::PROGRAM:
        outs << "TOKEN(PROGRAM)";
        break;
    case Token::PLUS:
        outs << "TOKEN(PLUS)";
        break;
    case Token::MINUS:
        outs << "TOKEN(MINUS)";
        break;
    case Token::MULTIPLY:
        outs << "TOKEN(MULTIPLY)";
        break;
    case Token::DIVIDE:
        outs << "TOKEN(DIV)";
        break;
    case Token::ERROR:
        outs << "TOKEN(ERROR)";
        break;
    case Token::RIGHT_PAREN:
        outs << "TOKEN(RIGHT_PAREN)";
        break;
    case Token::LEFT_PAREN:
        outs << "TOKEN(LEFT_PAREN)";
        break;
    case Token::BEGIN:
        outs << "TOKEN(BEGIN)";
        break;
    case Token::END:
        outs << "TOKEN(END)";
        break;
    case Token::IDENTIFIER:
        outs << "TOKEN(IDENTIFIER)";
        break;
    case Token::WRITELN:
        outs << "TOKEN(WRITELN)";
        break;
    case Token::ASSIGN:
        outs << "TOKEN(ASSIGN)";
        break;
    case Token::COLON:
        outs << "TOKEN(COLON)";
        break;
    case Token::SEMICOLON:
        outs << "TOKEN(SEMICOLON)";
        break;
    case Token::PERIOD:
        outs << "TOKEN(PERIOD)";
        break;
    case Token::LESS:
        outs << "TOKEN(LT)";
        break;
    case Token::LESS_EQUAL:
        outs << "TOKEN(LTE)";
        break;
    case Token::GREATER:
        outs << "TOKEN(GT)";
        break;
    case Token::GREATER_EQUAL:
        outs << "TOKEN(GTE)";
        break;
    case Token::EQUAL:
        outs << "TOKEN(EQ)";
        break;
    case Token::NOT_EQUAL:
        outs << "TOKEN(NEQ)";
        break;
    case Token::IF:
        outs << "TOKEN(IF)";
        break;
    case Token::THEN:
        outs << "TOKEN(THEN)";
        break;
    case Token::ELSE:
        outs << "TOKEN(ELSE)";
        break;
    case Token::COMMA:
        outs << "TOKEN(COMMA)";
        break;
    case Token::DO:
        outs << "TOKEN(DO)";
        break;
    case Token::VAR:
        outs << "TOKEN(VAR)";
        break;
    case Token::FOR:
        outs << "TOKEN(FOR)";
        break;
    case Token::TO:
        outs << "TOKEN(TO)";
        break;
    case Token::FUNCTION:
        outs << "TOKEN(FUN)";
        break;
    case Token::INTEGER:
        outs << "TOKEN(INTEGER)";
        break;
    case Token::INTEGER_LITERAL:
        outs << "TOKEN(INTEGER_LITERAL)";
        break;
    case Token::LONGINT:
        outs << "TOKEN(LONGINT)";
        break;
    case Token::CARET:
            outs << "TOKEN(CARET)";
        break;
    case Token::ARRAY:
            outs << "TOKEN(ARRAY)";
        break;
    case Token::OF:
            outs << "TOKEN(OF)";
    break;
        case Token::LEFT_BRACKET:
            outs << "TOKEN(LEFT_BRACKET)";
    break;
        case Token::RIGHT_BRACKET:
            outs << "TOKEN(RIGHT_BRACKET)";
    break;
        case Token::DOT_DOT:
            outs << "TOKEN(DOT_DOT)";
        break;

    default:
        outs << "TOKEN(UNKNOWN)";
        break;
    }
    return outs;
}

std::ostream& operator<<(std::ostream& outs, const Token* tok) {
    return outs << *tok;
}