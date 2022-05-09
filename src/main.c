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
        buf_lock (&buffer);

        while (buf_eof(&buffer) == false)
        {
          char *getalphanum = lexer_getalphanum(&buffer);

          printf("%s\n",getalphanum);

          buf_skipblank(&buffer);

          if (getalphanum != NULL)
          {
            free(getalphanum);
          }
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