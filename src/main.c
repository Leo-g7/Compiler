#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include "services/parser/parser.h"

int main(int argc, char *argv[])
{
  if (argc == 2 || argc == 5)
  {
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