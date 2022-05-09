#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include "services/buffer/buffer.h"
#include "services/lexer/lexer.h"
#include "services/ast/ast.h"

int main(int argc, char *argv[])
{
  if (argc == 2 || argc == 5)
  {
    char *filename = argv[1];
    if (filename != NULL)
    {
      buffer_t buffer;
      FILE *file = fopen(filename, "r");

      if (file != NULL)
      {
        // buf_init(&buffer, file);
        // buf_lock(&buffer);
        // parser(&buffer);

        ast_t *node = ast_new_integer(10);
        printf("%d\n", node->integer);

        if (node != NULL)
        {
          free(node);
        }
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