#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "../ast/ast.h"

void testConversion();
ast_t* convertExpressionIntoAst(ast_list_t* entryAst);
bool operandPriority(char *op1, char *op2);
char* getValueFromAst(ast_t* ast);
bool isNumber(char* value);
void exitProgram(char* msg);
char* strfromlonglong(long value); 

#endif /* EXPRESSION_H */