#include "ast.h"
#include <stdlib.h>

ast_t* ast_new_integer (long value) {
    ast_t* node = (ast_t*) malloc(sizeof(ast_t));
    node->integer = value;
    node->type = AST_INTEGER;

    return node;
}
