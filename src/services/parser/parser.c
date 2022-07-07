#include "../buffer/buffer.h"
#include "../lexer/lexer.h"
#include "../ast/ast.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool is_expected_lexem (char *lexem, char *expected)
{
  if (strcmp(lexem, expected))
  {
    return false;
  }
  return true;
}

void analyze_function_params(buffer_t * buffer) {
  ast_list_t* params;
  char* lexer = move_to_next_lexer(buffer);

  if(!is_expected_lexem(lexer, "("))
  {
    printf("Error: function wrongly defined\n");
    exit(1);
  }
  else if(is_expected_lexem(lexer, "("))
  {
    lexer = move_to_next_lexer(buffer);
    while (!is_expected_lexem(lexer, ")"))
    {
      printf("%s\n", lexer);
      lexer = move_to_next_lexer(buffer);
    }
  }

  free_lexer(lexer);
}

void analyze_function(buffer_t * buffer) {
  buf_move_lock(buffer);
  char *functionName = move_to_next_lexer(buffer);
  ast_list_t *params;
  analyze_function_params(buffer);
  int return_type;
}

// Loop through lexers and tests the syntax
void parser(FILE *file)
{
  buffer_t buffer;
  buf_init(&buffer, file);
  buf_lock(&buffer);

  ast_list_t *ast_list;

  while (buf_eof(&buffer) == false)
  {
    char *lexer = move_to_next_lexer(&buffer);

    if (!is_expected_lexem(lexer, "fonction") && buffer.lock == 0)
    {
      printf("Error: first lexem must be function\n");
      exit(1);
    }
    else if (is_expected_lexem(lexer, "fonction"))
    {
      analyze_function(&buffer);
    }
  }
}
