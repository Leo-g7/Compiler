#include "../buffer/buffer.h"
#include "../lexer/lexer.h"
#include "../ast/ast.h"
#include "../symbol/symbol.h"
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

void analyze_return(buffer_t * buffer)
{
  char* lexem = move_to_next_lexem(buffer);

  while(!is_expected_lexem(lexem, ";") ){
    lexem = move_to_next_lexem(buffer);
  }
}

void analyze_condition(buffer_t * buffer)
{
  char* lexem = move_to_next_lexem(buffer);

  //explore to verify if there is a "sinon" or a "sinon si"
  while(!is_expected_lexem(lexem, "}")){
    lexem = move_to_next_lexem(buffer);
  }
  
  // proceed to the analysis of the expression in the if statement
}

void analyze_loop(buffer_t * buffer)
{
  char* lexem = move_to_next_lexem(buffer);

  while(!is_expected_lexem(lexem, "}") ){
    lexem = move_to_next_lexem(buffer);
    printf("%s\n", lexem);
  }
}

void analyze_init(buffer_t * buffer)
{
  char* lexem = move_to_next_lexem(buffer);

  while(!is_expected_lexem(lexem, ";") ){
    lexem = move_to_next_lexem(buffer);
  }
}

void analyze_assignation(buffer_t * buffer)
{
  char* lexem = move_to_next_lexem(buffer);

  while(!is_expected_lexem(lexem, ";") ){
    lexem = move_to_next_lexem(buffer);
  }
}

void analyze_instruction(buffer_t * buffer,char* lexem)
{
  if(is_expected_lexem(lexem, "retourner"))
  {
    analyze_return(buffer);
  }
  else if(is_expected_lexem(lexem, "si")|| is_expected_lexem(lexem, "sinon"))
  {
    analyze_condition(buffer);
  }
  else if(is_expected_lexem(lexem, "tantque"))
  {
    analyze_loop(buffer);
  }
  else if(is_expected_lexem(lexem, "entier"))
  {
    analyze_init(buffer);
  }
  //detect assignation thanks to symbol table

  // else if(){
  //   analyze_assignation(buffer);
  // }
}

void analyze_function_body(buffer_t * buffer)
{
  char* lexem = move_to_next_lexem(buffer);

  if(!is_expected_lexem(lexem, "{"))
  {
    printf("Error: Missing curly braces\n");
    exit(1);
  }

  while(!is_expected_lexem(lexem, "}") && buf_eof(buffer) == false){
    lexem = move_to_next_lexem(buffer);
    analyze_instruction(buffer,lexem);

    // use this line to print "}" or every instruction first word
    // do not work for "sinon" and "sinon si" and assignation
    //printf("%s\n", lexem);
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

  //printf("%s\n", functionName);

  // I mad every analyze function return void but they should return ast_list_t*

  //ast_list_t *stmts =
  analyze_function_body(buffer);

  //ast_new_function(functionName, return_type, params, stmts)

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
