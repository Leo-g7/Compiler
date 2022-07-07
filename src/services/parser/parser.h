#ifndef PARSER_H
#define PARSER_H
#include "../buffer/buffer.h"
#include "../lexer/lexer.h"
#include "../ast/ast.h"

bool is_expected_lexem (char *lexem, char *expected);
int get_variable_type(char *lexem);
int analyze_type(buffer_t * buffer);
void analyze_return(buffer_t * buffer);
void analyze_condition(buffer_t * buffer);
void analyze_loop(buffer_t * buffer);
void analyze_init(buffer_t * buffer);
void analyze_assignation(buffer_t * buffer);
void analyze_instruction(buffer_t * buffer,char* lexem);
void analyze_function_body(buffer_t * buffer);
ast_list_t* analyze_function_params(buffer_t * buffer);
void analyze_function(buffer_t * buffer);
void parser(FILE *file);
#endif /* PARSER_H */