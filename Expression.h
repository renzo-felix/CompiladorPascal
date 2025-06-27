//
// Created by User on 27/06/2025.
//

#ifndef EXPRESSION_H
#define EXPRESSION_H



#pragma once

//#include "imp/Value.h"
//#include "imp/Type.h"
//#include "visitors/Visitor.h"
//#include "visitors/TypeVisitor.h"


#include <string>
#include <vector>

using namespace std;

enum class TypeExp { IntegerType, LongIntType, BoolType, VoidType };

string typeToString(TypeExp type);

enum class BinaryOp {
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    GT,
    GE,
    LT,
    LE,
    EQUAL
};

class VariableDeclaration;

using namespace std;

using VariableDeclarationList = vector<VariableDeclaration*>;

// Base class for all expressions in the syntax tree.
// Represents general expressions in the grammar.
class Expression {
public:
    virtual ~Expression() = 0;
    virtual int accept(Visitor* v) = 0;
  //  virtual Type* accept(TypeVisitor* v) =0;
};

class Statement {
public:
    virtual ~Statement() = 0;
    virtual int accept(Visitor* v) = 0;
   // virtual void accept(TypeVisitor* v) = 0;
};

using StatementList = vector<Statement*>;
using ExpressionList = vector<Expression*>;

// Represents a numeric literal expression.
// Grammar Rule: NumberExpression -> integer
// Used in mathematical expressions and assignments to hold constant integer
// values.
class NumberExpression final : public Expression {
public:
    int value;

    explicit NumberExpression(int v);
    ~NumberExpression() override;

    int accept(Visitor* v) override;
    // Type* accept(TypeVisitor* v) override;
};

// Represents an identifier (variable or function name).
// Grammar Rule: IdentifierExpression -> identifier
// Used to represent variable names and function names in expressions.
class IdentifierExpression : public Expression {
public:
    string name;

    explicit IdentifierExpression(string name);
    ~IdentifierExpression() override;

    int accept(Visitor* v) override;
   // Type* accept(TypeVisitor* v) override;
};

// Represents a list of identifiers separated by commas.
// Grammar Rule: IdentifierList = IdentifierExpression { ','
// IdentifierExpression } Used in variable declarations, parameter lists, and
// other parts of the syntax where multiple identifiers are needed.
class IdentifierList {
public:
    vector<Expression*> identifiers;
    explicit IdentifierList(Expression* identifiers);
    explicit IdentifierList(vector<Expression*> ids);
    ~IdentifierList();
    void add(Expression* id) { identifiers.push_back(id); }

    void add(IdentifierList* ids) {
        if (ids) {
            identifiers.insert(identifiers.end(), ids->identifiers.begin(),
                               ids->identifiers.end());
        }
    }

    IdentifierList() = default;
};

// Represents a binary operation (e.g., addition, subtraction).
// Grammar Rule: BinaryExpression -> Expression BinOp Expression
// Used in expressions involving binary operations, such as arithmetic and
// comparison.
class BinaryExpression : public Expression {
public:
    Expression *left, *right;
    string type;
    BinaryOp op;

    BinaryExpression(Expression* l, Expression* r, BinaryOp op, string tyOp);
    ~BinaryExpression() override;

    int accept(Visitor* v) override;
   // Type* accept(TypeVisitor* v) override;
};

// Represents a function call expression with a name and arguments.
// Grammar Rule: FunctionCallExpression -> identifier '(' [Expression { ','
// Expression}] ')' Used to represent calls to functions within expressions.
class FunctionCallExpression : public Expression {
public:
    string name;
    vector<Expression*> arguments;

    FunctionCallExpression(string name, vector<Expression*> arguments);
    ~FunctionCallExpression() override;

    int accept(Visitor* v) override;
   // Type* accept(TypeVisitor* v) override;
};

// Represents a variable declaration with type and identifiers.
// Grammar Rule: VariableDeclaration -> IdentifierList ':' Type ';'
// Used in the variable declaration section of blocks.

class ListVariableDeclaration {
public:
    vector<VariableDeclaration*> lista_Id;
    ListVariableDeclaration();
    explicit ListVariableDeclaration(vector<VariableDeclaration*> lista_Id_);

    void add(VariableDeclaration* identifiers) {
        lista_Id.push_back(identifiers);
    }

    ~ListVariableDeclaration();

    int accept(Visitor* v);
   // void accept(TypeVisitor* v);
};

class VariableDeclaration {
public:
    TypeExp type;
    IdentifierList* identifiers;

    VariableDeclaration(TypeExp type, IdentifierList* identifiers);
    ~VariableDeclaration();

    void accept(Visitor* v);
   // void accept(TypeVisitor* v);
};

// Represents an assignment statement.
// Grammar Rule: AssignStmnt -> Identifier ":=" Expression
// Used to assign values to variables.
class AssignStmnt : public Statement {
public:
    std::string variableName;
    Expression* expression;
    AssignStmnt(std::string id, Expression* rhs);
    ~AssignStmnt() override;

    int accept(Visitor* v) override;
  //  void accept(TypeVisitor* v) override;
};

// Represents a 'writeln' statement for outputting expressions.
// Grammar Rule: WriteStatement -> 'writeln' '(' Expression ')'
// Used for printing values to the console.
class WriteStatement : public Statement {
public:
    Expression* e;
    explicit WriteStatement(Expression* e);
    ~WriteStatement() override;

    int accept(Visitor* v) override;
   // void accept(TypeVisitor* v) override;
};

// Represents a conditional statement with 'if' and optional 'else' branches.
// Grammar Rule: ConditionalStatement -> 'if' Expression 'then' Statement [
// 'else' Statement ] Used to execute statements based on a boolean condition.
class ConditionalStatement : public Statement {
public:
    Expression* condition = nullptr;
    StatementList thenBranch;
    StatementList elseBranch;
    ConditionalStatement(Expression* condition, StatementList thenBranch,
                         StatementList elseBranch);
    ~ConditionalStatement() override;

    int accept(Visitor* v) override;
    //void accept(TypeVisitor* v) override;
};

// Represents a 'for' loop statement with a loop variable and range.
// Grammar Rule: ForStatement -> 'for' IdentifierExpression ':=' Expression 'to'
// Expression 'do' Statement Used to repeat a block of statements over a range
// of values.
class ForStatement : public Statement {
public:
    Expression* idx = nullptr;
    Expression* start = nullptr;
    Expression* end = nullptr;
    StatementList body;

    ForStatement() = default;
    ForStatement(Expression* idx, Expression* start, Expression* end,
                 StatementList doStmnt);
    ~ForStatement() override;

    int accept(Visitor* v) override;
   // void accept(TypeVisitor* v) override;
};

// Represents a parameter with identifiers and a type.
// Grammar Rule: Parameter -> IdentifierList ':' Type
// Used in function declarations to define parameter names and types.
class Parameter {
public:
    IdentifierList* ids;
    TypeExp type;

    Parameter(IdentifierList* ids, TypeExp type);
    ~Parameter();

    void accept(Visitor* v);
   // Type* accept(TypeVisitor* v);
};

using ParamList = vector<Parameter*>;

// Represents a function declaration with a name, parameters, return type, and
// body. Grammar Rule: FunctionDec -> 'function' IdentifierExpression '('
// [ParamList] ')' ':' Type ';' Block ';' Used in blocks to declare functions
// that can be called within the program.
class FunctionDec {
public:
    Expression* name;
    ParamList params;
    Expression* type;
    vector<Statement*> statementList;
    FunctionDec(Expression* name, ParamList params, Expression* type,
                vector<Statement*> block);
    ~FunctionDec();

    int accept(Visitor* v);
   // void accept(TypeVisitor* v);
};

// Represents a list of function declarations (subprograms).
// Grammar Rule: SubProgramDec -> {FunctionDec}
// Used in blocks to group multiple function declarations.
class SubProgramDec {
public:
    vector<FunctionDec*> functions;
    explicit SubProgramDec(vector<FunctionDec*> fs);
    ~SubProgramDec();

    int accept(Visitor* v);
   // void accept(TypeVisitor* v);
};

// Represents a block containing variable declarations, subprograms, and
// statements. Grammar Rule: Block -> VarDecList SubPrograms StatementList Used
// as the main body of functions and the main program.
class Block {
public:
    SubProgramDec* subProgram;
    ListVariableDeclaration* varDecList;
    StatementList statements;
    Block(ListVariableDeclaration* varDecList, SubProgramDec* subProgram,
          StatementList statements);
    ~Block();

    int accept(Visitor* v);
   // void accept(TypeVisitor* v);
};

// Represents the entire program with a name and main block.
// Grammar Rule: Program -> 'program' IdentifierExpression ';' Block '.'
// Used to define the structure of a Pascal program, including variable
// declarations and functions.
class Program {
public:
    string name;
    Block* block;

    Program(string name, Block* block);
    ~Program();

    int accept(Visitor* v);
  //  void accept(TypeVisitor* v);
};

#endif //EXPRESSION_H
