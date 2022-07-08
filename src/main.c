#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "services/buffer/buffer.h"
#include "services/lexer/lexer.h"
#include "utils/stack.h"
#include "services/parser/parser.h"
#include "services/parser/expression.h"

ast_t* convertExpressionIntoAst(ast_list_t* entryAst);
bool operandPriority(char* op1, char* op2);
// void exitProgram(char* msg);
int main(int argc, char *argv[]) 
{
  if (argc == 2 || argc == 5)
  {
    //testConversion();
    char *filename = argv[1];
    if (filename != NULL)
    {
      FILE *file = fopen(filename, "r");
      if (file != NULL)
      {
        parser(file);
      }
      else
      {
        printf("unable to open the file: %s \n", filename);
      }
      return 0;
    }
  }
  else
  {
    printf("Invalid parameter, Compiler <file name> \n");
    return ERROR_INVALID_PARAMETER;
  }
}