#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

symbol_t *sym_new(char *name, int type, ast_t *attributes) {
    symbol_t *node = (symbol_t *)malloc(sizeof(symbol_t));
    node->name = name;
    node->type = type;
    node->attributes = attributes;
    return node;
}

void sym_delete(symbol_t *sym) {
    free(sym);
}

void sym_remove(symbol_t **table, symbol_t *sym) {
    symbol_t *tmp = *table;
    if (tmp == sym) {
        *table = tmp->next;
        return;
    }

    while (tmp->next != NULL) {
        if (tmp->next == sym) {
            tmp->next = tmp->next->next;
            return;
        }
        tmp = tmp->next;
    }
}

void sym_add(symbol_t **table, symbol_t *sym) {
    symbol_t *tmp = *table;
    if (tmp == NULL) {
        *table = sym;
        return;
    }
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = sym;
}

symbol_t *sym_search(symbol_t *table, char *name) {
    symbol_t *tmp = table;
    while (tmp != NULL) {
        if (strcmp(tmp->name, name) == 0) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}
void sym_print_list(symbol_t *table) {
    symbol_t *tmp = table;
    while (tmp != NULL) {
        printf("%s\n", tmp->name);
        tmp = tmp->next;
    }
}
