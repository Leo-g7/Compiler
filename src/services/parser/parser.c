#include "../buffer/buffer.h"
#include "../lexer/lexer.h"
#include "../ast/ast.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool is_expected_lexem(char *lexem, char *expected)
{
  if (strcmp(lexem, expected))
  {
    return false;
  }
  return true;
}

int get_variable_type(char *lexem) {
  if(!is_expected_lexem(lexem, "entier") && !is_expected_lexem(lexem, "rien"))
  {
    printf("Error: function parameter wrongly typed\n");
    exit(1);
  }else if(is_expected_lexem(lexem, "entier")){
    return AST_INTEGER;
  }else if(is_expected_lexem(lexem, "rien")){
    return AST_VOID;
  }else{
    printf("Error: Type does not exist\n");
    exit(1);
  }
}

int analyze_type(buffer_t * buffer)
{
  char* lexem = move_to_next_lexem(buffer);

  if(!is_expected_lexem(lexem, ":"))
  {
    printf("Error: wrong type declaration\n");
    exit(1);
  }else{
    lexem = move_to_next_lexem(buffer);
    return get_variable_type(lexem);
  }
}

ast_list_t* analyze_function_params(buffer_t * buffer) {
  ast_list_t* params  = NULL;
  char* lexem = move_to_next_lexem(buffer);

  if(!is_expected_lexem(lexem, "("))
  {
    printf("Error: function wrongly defined\n");
    exit(1);
  }
  else if(is_expected_lexem(lexem, "("))
  {
    while (!is_expected_lexem(lexem, ")"))
    {
      lexem = move_to_next_lexem(buffer);

      if(is_expected_lexem(lexem, ")"))break;

      int type = get_variable_type(lexem);
      lexem = move_to_next_lexem(buffer);

      char *name = lexem;
      lexem = move_to_next_lexem(buffer);

      ast_t *param = ast_new_variable(name, type);
      params = ast_list_add(&params,param);
    }
  }

  free_lexer(lexem);
  buf_move_lock(buffer);
  return params;
}

void analyze_function(buffer_t *buffer)
{
  buf_move_lock(buffer);
  char *functionName = move_to_next_lexem(buffer);
  ast_list_t *params = analyze_function_params(buffer);
  int return_type = analyze_type(buffer);

  if (params != NULL)
  {
    free(params);
  }
}

// Loop through lexers and tests the syntax
void parser(FILE *file)
{
  buffer_t buffer;
  buf_init(&buffer, file);
  buf_lock(&buffer);

  // create a ast_integer and display it
  // long value = 42;
  // ast_t *test = ast_new_integer(value);
  // ast_display(test, 0);

  // // same for ast_binary
  // ast_binary_e op = AST_PLUS;
  // ast_t *test2 = ast_new_binary(op, NULL, NULL);
  // ast_display(test2, 0);

  // same for function

  ast_list_t *ast_list;

  while (buf_eof(&buffer) == false)
  {
    char *lexem = move_to_next_lexem(&buffer);

    if (!is_expected_lexem(lexem, "fonction") && buffer.lock == 0)
    {
      printf("Error: first lexem must be function\n");
      exit(1);
    }
    else if (is_expected_lexem(lexem, "fonction"))
    {
      analyze_function(&buffer);
    }
  }
}
