#ifndef PARSER_H
#define PARSER_H
#include "../buffer/buffer.h"
#include "../lexer/lexer.h"
#include "../ast/ast.h"

char* parser(FILE* file);
bool isExpectedLexem(char *lexem, char *expected);

void analyze_function(buffer_t * buffer);
void analyze_function_params(buffer_t * buffer);
#endif /* PARSER_H */