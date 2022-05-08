#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include "services/buffer/buffer.h"
#include "services/lexer/lexer.h"

int main(int argc, char* argv[])
{
  if (argc == 2)
  {
    char *filename = argv[1];
    if (filename != NULL)
    {
      buffer_t buffer;
      FILE* file = fopen(filename, "r");
      if (file != NULL)
      {
        buf_init(&buffer, file);

         char *getalphanum = lexer_getalphanum(&buffer);
        printf("%s\n",getalphanum);

        buf_print(&buffer);

        if (getalphanum != NULL)
        {
          free(getalphanum);
        }

        char *getalphanum_rollback = lexer_getalphanum_rollback(&buffer);

        buf_print(&buffer);

        if (getalphanum_rollback != NULL)
        {
          free(getalphanum_rollback);
        }

        long getnumber = lexer_getnumber(&buffer);

        printf("%ld\n",getnumber);

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