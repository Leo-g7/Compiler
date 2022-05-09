#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "../ast/ast.h"
#include "../buffer/buffer.h"

// Return the next char* in the buffer and put the cursor at the end of this char*
char *lexer_getalphanum (buffer_t * buffer) {
  long counter = buffer->it;
  char *alphanum = malloc(BUF_SIZE);
  int x = 0;

  while (buf_eof(buffer) == false)
  {
    char c = buf_getchar(buffer);

    if(++counter < buffer->it || (isalpha(c) == 0 && !isdigit(c) && ispunct(c) == 0))
    {
      buf_rollback(buffer,buffer->it-counter+1);
      break;
    }
    else
    {
      alphanum[x++] = c;
    }
  }
  alphanum[x] = '\0';

  return alphanum;
}

// Return the next char* in the buffer and don't move the cursor
char *lexer_getalphanum_rollback(buffer_t * buffer){
  long counter = buffer->it;
  long initialpos = buffer->it;
  int x = 0;
  char *alphanum = malloc(BUF_SIZE);

  while (buf_eof(buffer) == false)
  {
    char c = buf_getchar(buffer);

    if(++counter < buffer->it || (isalpha(c) == 0 && !isdigit(c) && ispunct(c) == 0))
    {
      buf_rollback(buffer,buffer->it-initialpos);
      break;
    }
    else
    {
      alphanum[x++] = c;
    }
  }
  alphanum[x] = '\0';

  return alphanum;
}

// Return the next char* in the buffer if convert it to a long or else return 0
long lexer_getnumber (buffer_t * buffer){

  long counter = buffer->it;
  char *alphanum = malloc(BUF_SIZE);
  int x = 0;

  while (buf_eof(buffer) == false)
  {
    char c = buf_getchar(buffer);

    if(++counter < buffer->it || (!isdigit(c) && !(x == 0 && c == '-'))  )
    {
      buf_rollback(buffer,buffer->it-counter+1);
      break;
    }
    else
    {
      alphanum[x++] = c;
    }
  }
  alphanum[x] = '\0';
  char* endPtr = NULL;
  long result = strtol(alphanum,&endPtr,10);

  if (alphanum != NULL) free(alphanum);

  return result;
}

// Loop through lexers and tests the syntax
void parser(buffer_t * buffer) {
  while (buf_eof(buffer) == false)
  {
    char *getalphanum = lexer_getalphanum(buffer);
    printf("%s\n",getalphanum);

    buf_skipblank(buffer);

    if (getalphanum != NULL)
    {
      free(getalphanum);
    }
  }
}
