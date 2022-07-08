#ifndef GENERATOR_H
#define GENERATOR_H

#include "../buffer/buffer.h"
#include "../symbol/symbol.h"
#include "../ast/ast.h"
// create a translator from an ast to a typescript file

typedef struct generator_t {
    FILE *fd;
    ast_t *ast;
    symbol_t *symbol_table;
    buffer_t *buffer;
    size_t indent;
    bool is_locked;
} generator_t;

void generator_init(generator_t *generator, FILE *fd, ast_t *ast);
void generator_delete(generator_t *generator);
void generator_generate(generator_t *generator);

#define GENERATOR_H
#endif /* GENERATOR_H */