#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "../ast/ast.h"

void testConversion();
ast_t* convertExpressionIntoAst(ast_list_t* entryAst);
bool operandPriority(char* op1, char* op2);

#endif /* EXPRESSION_H */