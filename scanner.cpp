//
// Created by User on 27/06/2025.
//

#include "scanner.h"


#include <iostream>

using namespace std;

Scanner::Scanner(std::string input) : input(std::move(input)), position(0) {}

char Scanner::currentChar() const {
    return position < input.size() ? input[position] : '\0';
}

void Scanner::advance() {
    if (position < input.size()) {
        position++;
    }
}

void Scanner::skipWhitespace() {
    while (currentChar() == ' ' || currentChar() == '\t' || currentChar() == '\n' || currentChar() == '\r') {
        advance();
    }
}

void Scanner::skipWhitespaceAndComments() {
    while (true) {
        while (currentChar() == ' ' || currentChar() == '\t' || currentChar() == '\n' || currentChar() == '\r') {
            advance();
        }

        if (currentChar() == '{') {
            advance();
            while (currentChar() != '}' && currentChar() != '\0') {
                advance();
            }
            if (currentChar() == '}') {
                advance();
            }
            else {
                cerr << "Error: Unterminated block comment" << endl;
                return;
            }
        }
        else if (currentChar() == '/' && input[position + 1] == '/') {
            advance();
            advance();
            while (currentChar() != '\n' && currentChar() != '\r' && currentChar() != '\0') {
                advance();
            }
        }
        else
            break;
    }
}

bool Scanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool Scanner::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Scanner::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}

Token* Scanner::getNextToken() {
    skipWhitespaceAndComments();
    if (position >= input.size()) {
        return new Token(Token::EOF_TOKEN);
    }

    char c = currentChar();

    // Identifiers and keywords
    if (isAlpha(c)) {
        return identifier();
    }

    // Numbers
    if (isDigit(c)) {
        return number();
    }

    switch (c) {
    case '+':
        return singleCharacterToken(Token::Type::PLUS);
    case '-':
        return singleCharacterToken(Token::Type::MINUS);
    case '*':
        return singleCharacterToken(Token::Type::MULTIPLY);
    case '/':
        return singleCharacterToken(Token::Type::DIVIDE);
    case '=':
        return singleCharacterToken(Token::Type::EQUAL);
    case '<':
        advance();
        if (currentChar() == '=') {
            advance();
            return new Token(Token::Type::LESS_EQUAL, "<=");
        }
        else if (currentChar() == '>') {
            advance();
            return new Token(Token::Type::NOT_EQUAL, "<>");
        }
        return new Token(Token::Type::LESS, "<");
    case '>':
        advance();
        if (currentChar() == '=') {
            advance();
            return new Token(Token::Type::GREATER_EQUAL, ">=");
        }
        return new Token(Token::Type::GREATER, ">");
    case ':':
        advance();
        if (currentChar() == '=') {
            advance();
            return new Token(Token::Type::ASSIGN, ":=");
        }
        return new Token(Token::Type::COLON, ":");
    case ';':
        return singleCharacterToken(Token::Type::SEMICOLON);
    case ',':
        return singleCharacterToken(Token::Type::COMMA);

    case '(':
        return singleCharacterToken(Token::Type::LEFT_PAREN);
    case ')':
        return singleCharacterToken(Token::Type::RIGHT_PAREN);
    case '^':
            return singleCharacterToken(Token::Type::CARET);

    case '[':
            return singleCharacterToken(Token::Type::LEFT_BRACKET);

    case ']':
            return singleCharacterToken(Token::Type::RIGHT_BRACKET);

    case '.':
            advance();
        if (currentChar() == '.') {
            advance();
            return new Token(Token::Type::DOT_DOT, "..");
        }
        return new Token(Token::Type::PERIOD, ".");

    default:
        cerr << "Error: cannot recognize single character token " << c << endl;
        return new Token(Token::Type::ERROR);
    }

}

Token* Scanner::singleCharacterToken(Token::Type type) {
    char c = currentChar();
    advance();
    return new Token(type, std::string(1, c));
}

Token* Scanner::identifier() {
    std::string lexeme;
    while (isAlphaNumeric(currentChar()) && currentChar() != '.') {
        lexeme += currentChar();
        advance();
    }

    if (lexeme == "program") return new Token(Token::Type::PROGRAM, lexeme);
    if (lexeme == "var") return new Token(Token::Type::VAR, lexeme);
    if (lexeme == "integer" || lexeme == "Integer") return new Token(Token::Type::INTEGER, lexeme);
    if (lexeme == "longint" || lexeme == "Longint") return new Token(Token::Type::LONGINT, lexeme);
    if (lexeme == "function") return new Token(Token::Type::FUNCTION, lexeme);
    if (lexeme == "begin") return new Token(Token::Type::BEGIN, lexeme);
    if (lexeme == "end") return new Token(Token::Type::END, lexeme);
    if (lexeme == "if") return new Token(Token::Type::IF, lexeme);
    if (lexeme == "then") return new Token(Token::Type::THEN, lexeme);
    if (lexeme == "else") return new Token(Token::Type::ELSE, lexeme);
    if (lexeme == "for") return new Token(Token::Type::FOR, lexeme);
    if (lexeme == "to") return new Token(Token::Type::TO, lexeme);
    if (lexeme == "do") return new Token(Token::Type::DO, lexeme);
    if (lexeme == "writeln") return new Token(Token::Type::WRITELN, lexeme);
    if (lexeme == "array") return new Token(Token::Type::ARRAY, lexeme);
    if (lexeme == "of") return new Token(Token::Type::OF, lexeme);



    return new Token(Token::Type::IDENTIFIER, lexeme);
}

Token* Scanner::number() {
    std::string lexeme;
    while (isDigit(currentChar())) {
        lexeme += currentChar();
        advance();
    }
    return new Token(Token::Type::INTEGER_LITERAL, lexeme);
}


void test_scanner(Scanner* scanner) {
    Token* current;
    cout << "Iniciando Scanner:" << endl << endl;
    while ((current = scanner->getNextToken())->type != Token::EOF_TOKEN) {
        if (current->type == Token::ERROR) {
            cout << "Error en scanner - carácter inválido: " << current->text
                    << endl;
            break;
        }
        cout << *current << endl;
        delete current;
    }
    cout << "TOKEN(EOF_TOKEN)" << endl;
    delete current;
}