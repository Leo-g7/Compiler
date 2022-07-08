#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generator_init(generator_t *generator, FILE *fd, ast_t *ast) {
    generator->fd = fd;
    generator->ast = ast;
}