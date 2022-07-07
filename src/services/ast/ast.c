#include "ast.h"
#include <stdlib.h>

ast_t* ast_new_integer (long value) {
    ast_t* node = (ast_t*) malloc(sizeof(ast_t));
    node->integer = value;
    node->type = AST_INTEGER;

    return node;
}

ast_t* ast_new_operand(char* op, ast_t* ast) {
    ast_t* node = (ast_t*) malloc(sizeof(ast_t));
    node->operand.nextOper =  ast;
    node->operand.operValue = op;
    node->type = AST_OPERAND;
}
