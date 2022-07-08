#ifndef SYMBOL_H
#define SYMBOL_H
#include "../ast/ast.h"
// Symbol table, linked list of symbols
typedef enum
{
    SYM_FUNCTION,
    SYM_VAR,
    SYM_PARAM,
} sym_type_t;

typedef struct symbol_t
{
    char *name;
    sym_type_t type;
    ast_t *attributes;
    struct symbol_t *function_table;
    struct symbol_t *next;
} symbol_t;

symbol_t *sym_new(char *name, int type, ast_t *attributes);
void sym_delete(symbol_t *sym);
void sym_remove(symbol_t **table, symbol_t *sym);
void sym_add(symbol_t **table, symbol_t *sym);
void sym_print_list(symbol_t *table);
symbol_t *sym_search(symbol_t *table, char *name);

#endif