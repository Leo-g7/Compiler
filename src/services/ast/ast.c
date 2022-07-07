#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

// Create a new AST node

// Create a new integer ast tree
ast_t *ast_new_integer(long value)
{
    ast_t *node = (ast_t *)malloc(sizeof(ast_t));
    node->integer = value;
    node->type = AST_INTEGER;

    return node;
}

// Create a new variable ast tree
ast_t *ast_new_variable(char *name, int type)
{
    ast_t *node = (ast_t *)malloc(sizeof(ast_t));
    node->var.name = name;
    node->var.type = type;
    node->type = AST_VARIABLE;

    return node;
}

// Create a new binary ast tree
ast_t *ast_new_binary(ast_binary_e op, ast_t *left, ast_t *right)
{
    ast_t *node = (ast_t *)malloc(sizeof(ast_t));
    node->binary.op = op;
    node->binary.left = left;
    node->binary.right = right;
    node->type = AST_BINARY;

    return node;
}

// Create a new function ast tree
ast_t *ast_new_function(char *name, int return_type, ast_list_t *params, ast_list_t *stmts)
{
    ast_t *node = (ast_t *)malloc(sizeof(ast_t));
    node->function.name = name;
    node->function.return_type = return_type;
    node->function.params = params;
    node->function.stmts = stmts;

    node->type = AST_FUNCTION;
    return node;
}

// Create a new function call ast tree
ast_t *ast_new_fncall(char *name, ast_list_t *args)
{
    ast_t *node = (ast_t *)malloc(sizeof(ast_t));
    node->call.name = name;
    node->call.args = args;
    node->type = AST_FNCALL;

    return node;
}

// Create a new composed statment ast tree
ast_t *ast_new_comp_stmt(ast_list_t *stmts)
{
    ast_t *node = (ast_t *)malloc(sizeof(ast_t));
    node->compound_stmt.stmts = stmts;
    node->type = AST_COMPOUND_STATEMENT;

    return node;
}

// Create a new assignment ast tree
ast_t *ast_new_assignment(ast_t *lvalue, ast_t *rvalue)
{
    ast_t *node = (ast_t *)malloc(sizeof(ast_t));
    node->assignment.lvalue = lvalue;
    node->assignment.rvalue = rvalue;
    node->type = AST_ASSIGNMENT;

    return node;
}

// Create a new declaration ast tree
ast_t *ast_new_declaration(ast_t *lvalue, ast_t *rvalue)
{
    ast_t *node = (ast_t *)malloc(sizeof(ast_t));
    node->declaration.lvalue = lvalue;
    node->declaration.rvalue = rvalue;
    node->type = AST_DECLARATION;

    return node;
}

// Create a new condition ast tree
ast_t *ast_new_condition(ast_t *condition, ast_t *valid, ast_t *invalid)
{
    ast_t *node = (ast_t *)malloc(sizeof(ast_t));
    node->branch.condition = condition;
    node->branch.valid = valid;
    node->branch.invalid = invalid;
    node->type = AST_CONDITION;

    return node;
}

// Create a new loop ast tree
ast_t *ast_new_loop(ast_t *condition, ast_t *stmt)
{
    ast_t *node = (ast_t *)malloc(sizeof(ast_t));
    node->loop.condition = condition;
    node->loop.stmt = stmt;
    node->type = AST_LOOP;

    return node;
}

// Create a new return ast tree
ast_t *ast_new_return(ast_t *expr)
{
    ast_t *node = (ast_t *)malloc(sizeof(ast_t));
    node->ret.expr = expr;
    node->type = AST_RETURN;

    return node;
}

// Create a new list ast tree
ast_list_t *ast_list_new_node(ast_t *elem)
{
    ast_list_t *node = (ast_list_t *)malloc(sizeof(ast_list_t));
    node->ast = elem;
    node->next = NULL;
    return node;
}

// Append an ast to the list
ast_list_t *ast_list_add(ast_list_t **list, ast_t *elem)
{
    ast_list_t *node = ast_list_new_node(elem);
    if (*list == NULL)
    {
        *list = node;

        return node;
    }
    else
    {
        ast_list_t *last = *list;
        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = node;

        return *list;
    }
}

void ast_display(ast_t *node, int level) {
    printf("start", node, level);
    if (node == NULL)
        return;
        
    for (int i = 0; i < level; i++)
        printf("  ");
    switch (node->type)
    {
    case AST_INTEGER:
        printf("int");
        printf("%ld\n", node->integer);
        break;
    case AST_VARIABLE:
        printf("var\n");
        printf("%s\n", node->var.name);
        printf("%d\n", node->var.type);
        break;
    case AST_BINARY:
        printf("bin\n");
        printf("%d\n", node->binary.op);
        ast_display(node->binary.left, level + 1);
        ast_display(node->binary.right, level + 1);
        break;
    // case AST_FUNCTION:
    //     printf("func\n");
    //     printf("%s\n", node->function.name);
    //     printf("%d\n", node->function.return_type);
    //     ast_display(node->function.params, level + 1);
    //     ast_display(node->function.stmts, level + 1);
    //     break;
    // case AST_FNCALL:
    //     printf("fncall\n");
    //     printf("%s\n", node->call.name);
    //     ast_display(node->call.args, level + 1);
    //     break;
    // case AST_COMPOUND_STATEMENT:
    //     printf("comp\n");
    //     ast_display(node->compound_stmt.stmts, level + 1);
    //     break;
    // case AST_ASSIGNMENT:
    //     printf("assign\n");
    //     ast_display(node->assignment.lvalue, level + 1);
    //     ast_display(node->assignment.rvalue, level + 1);
    //     break;
    // case AST_DECLARATION:
    //     printf("decl\n");
    //     ast_display(node->declaration.lvalue, level + 1);
    //     ast_display(node->declaration.rvalue, level + 1);
    //     break;
    // case AST_CONDITION:
    //     printf("cond\n");
    //     ast_display(node->branch.condition, level + 1);
    //     ast_display(node->branch.valid, level + 1);
    //     ast_display(node->branch.invalid, level + 1);
    //     break;
    // case AST_LOOP:
    //     printf("loop\n");
    //     ast_display(node->loop.condition, level + 1);
    //     ast_display(node->loop.stmt, level + 1);
    //     break;
    // case AST_RETURN:
    //     printf("ret\n");
    //     ast_display(node->ret.expr, level + 1);
    //     break;
    }

    printf("end");
}


