#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initialize the symbol table
symbol_t *sym_new(char *name, int type, ast_t *attributes)
{
    // Allocate memory for the symbol
    symbol_t *node = (symbol_t *)malloc(sizeof(symbol_t));
    // Set the name, type, and attributes
    node->name = name;
    node->type = type;
    node->attributes = attributes;
    return node;
}

// Delete the symbol table
void sym_delete(symbol_t *sym)
{
    // Free the symbol
    free(sym);
}
// Remove the symbol from the table
void sym_remove(symbol_t **table, symbol_t *sym)
{
    symbol_t *tmp = *table;
    // If the symbol is the first one, set the table to the second one
    if (tmp == sym)
    {
        *table = tmp->next;
        return;
    }
    // Otherwise, find the symbol and remove it
    while (tmp->next != NULL)
    {
        // If the next symbol is the one to remove, remove it
        if (tmp->next == sym)
        {
            tmp->next = tmp->next->next;
            return;
        }
        tmp = tmp->next;
    }
}
// Add the symbol to the table
void sym_add(symbol_t **table, symbol_t *sym)
{
    symbol_t *tmp = *table;
    // If the table is empty, set the first symbol
    if (tmp == NULL)
    {
        *table = sym;
        return;
    }
    // Otherwise, find the last symbol and add it
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = sym;
}
// Find the symbol in the table
symbol_t *sym_search(symbol_t *table, char *name)
{
    symbol_t *tmp = table;
    while (tmp != NULL)
    {
        // If the name matches, return the symbol
        if (strcmp(tmp->name, name) == 0)
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}
// Print the symbol table
void sym_print_list(symbol_t *table)
{
    symbol_t *tmp = table;
    while (tmp != NULL)
    {
        // Print the symbol
        printf("%s\n", tmp->name);
        tmp = tmp->next;
    }
}
