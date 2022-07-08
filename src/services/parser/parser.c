#include "../buffer/buffer.h"
#include "../lexer/lexer.h"
#include "../ast/ast.h"
#include "../symbol/symbol.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// compare two lexem
bool is_expected_lexem(char *lexem, char *expected)
{
  if (strcmp(lexem, expected))
  {
    return false;
  }
  return true;
}

// get a variable type as a string and return its matching enum type
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

// parse return params
int analyze_return_type(buffer_t * buffer)
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

// parse a return instruction
void analyze_return(buffer_t * buffer)
{
  char* lexem = move_to_next_lexem(buffer);

  while(!is_expected_lexem(lexem, ";") ){
    lexem = move_to_next_lexem(buffer);
  }
}

// parse a condition instruction
void analyze_condition(buffer_t * buffer)
{
  char* lexem = move_to_next_lexem(buffer);

  //explore to verify if there is a "sinon" or a "sinon si" and check their order
  while(!is_expected_lexem(lexem, "}")){
    lexem = move_to_next_lexem(buffer);
  }
}

// parse a loop instruction
void analyze_loop(buffer_t * buffer)
{
  char* lexem = move_to_next_lexem(buffer);

  while(!is_expected_lexem(lexem, "}") ){
    lexem = move_to_next_lexem(buffer);
  }
}

// parse a init instruction
void analyze_init(buffer_t * buffer)
{
  char* lexem = move_to_next_lexem(buffer);

  while(!is_expected_lexem(lexem, ";") ){
    lexem = move_to_next_lexem(buffer);
  }
}

// parse a assignation instruction
void analyze_assignation(buffer_t * buffer,char *lexem)
{
  while(!is_expected_lexem(lexem, ";") ){
    lexem = move_to_next_lexem(buffer);
  }
}

// parse all differents instruction block of a function
void analyze_instruction(buffer_t * buffer,char* lexem)
{
  if(is_expected_lexem(lexem, "retourner"))
  {
    analyze_return(buffer);
  }
  else if(is_expected_lexem(lexem, "si") || is_expected_lexem(lexem, "sinon"))
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
  else if(!is_expected_lexem(lexem, ";") && !is_expected_lexem(lexem, "}"))
  {
    analyze_assignation(buffer,lexem);
  }
}

// parse the function body
void analyze_function_body(buffer_t * buffer)
{
  char* lexem = move_to_next_lexem(buffer);

  if(!is_expected_lexem(lexem, "{"))
  {
    printf("Error: Missing curly braces\n");
    exit(1);
  }

  // loop through the function untill it find the final curly braces
  while(!is_expected_lexem(lexem, "}") && buf_eof(buffer) == false){
    lexem = move_to_next_lexem(buffer);
    analyze_instruction(buffer,lexem);
  }
}

// parse function params
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

// Loop through function and create an function ast
void analyze_function(buffer_t *buffer)
{
  // parse the function name, parameters and return type
  buf_move_lock(buffer);
  char *functionName = move_to_next_lexem(buffer);
  ast_list_t *params = analyze_function_params(buffer);
  int return_type = analyze_return_type(buffer);

  // I mad every analyze function return void but they should return ast_list_t*

  analyze_function_body(buffer);

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

    free_lexer(lexem);
  }
}
