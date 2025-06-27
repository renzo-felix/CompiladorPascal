//
// Created by User on 27/06/2025.
//

#ifndef VISITOR_H
#define VISITOR_H



#pragma once


class NumberExpression;
class IdentifierExpression;
class BinaryExpression;
class FunctionCallExpression;
class ListVariableDeclaration;
class VariableDeclaration;
class IdentifierList;
class AssignStmnt;
class WriteStatement;
class ConditionalStatement;
class ForStatement;
class Parameter;
class FunctionDec;
class SubProgramDec;
class Block;
class Program;

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual int visit(NumberExpression* n) = 0;
    virtual int visit(IdentifierExpression* i) = 0;
    virtual int visit(BinaryExpression* b) = 0;
    virtual int visit(FunctionCallExpression* f) = 0;
    virtual int visit(Parameter* p) = 0;
    virtual void visit(IdentifierList* i) = 0;
    virtual void visit(ListVariableDeclaration* l) = 0;
    virtual void visit(VariableDeclaration* v) = 0;
    virtual void visit(FunctionDec* f) = 0;
    virtual void visit(SubProgramDec* s) = 0;
    virtual void visit(AssignStmnt* a) = 0;
    virtual void visit(WriteStatement* w) = 0;
    virtual void visit(ConditionalStatement* c) = 0;
    virtual void visit(ForStatement* f) = 0;
    virtual void visit(Block* b) = 0;
    virtual void visit(Program* p) = 0;
};

class PrintVisitor : public Visitor {
public:
    void imprimir(Program* program);

    int visit(NumberExpression* n) override;
    int visit(IdentifierExpression* i) override;
    int visit(BinaryExpression* b) override;
    int visit(FunctionCallExpression* f) override;
    int visit(Parameter* p) override;
    void visit(IdentifierList* i) override;
    void visit(ListVariableDeclaration* l) override;
    void visit(VariableDeclaration* v) override;
    void visit(FunctionDec* f) override;
    void visit(SubProgramDec* s) override;
    void visit(AssignStmnt* a) override;
    void visit(WriteStatement* w) override;
    void visit(ConditionalStatement* c) override;
    void visit(ForStatement* f) override;
    void visit(Block* b) override;
    void visit(Program* p) override;

private:
    int indentLevel = 0;
    void increaseIndent() { indentLevel++; }
    void decreaseIndent() { indentLevel--; }
    void printIndent() const;
};


#endif //VISITOR_H
