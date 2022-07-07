#ifndef SYMBOL_H
#define SYMBOL_H
#include "../ast/ast.h"

// Symbol table, linked list of symbols
typedef struct symbol_t
{
    char *name;
    int type;
    int attributes;
    struct symbol_t *next;
} symbol_t;

symbol_t *sym_new(char *name, int type, ast_t *attributes);
void sym_delete(symbol_t *sym);
void sym_remove(symbol_t **table, symbol_t *sym);
void sym_add(symbol_t **table, symbol_t *sym);
symbol_t *sym_search(symbol_t *table, char *name);

#endif