#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "../buffer/buffer.h"

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
      alphanum[x] = '\0';
      break;
    }
    else
    {
      alphanum[x++] = c;
    }
  }

  return alphanum;
}

char * lexer_getalphanum_rollback(buffer_t * buffer){
  long counter = buffer->it;
  long initialpos = buffer->it;
  int x = 0;
  char *alphanum = malloc(BUF_SIZE);

  while (buf_eof(buffer) == false)
  {
    char c = buf_getchar(buffer);

    if(++counter < buffer->it || (isalpha(c) == 0 && !isdigit(c) && ispunct(c) == 0))
    {
      alphanum[x] = '\0';
      buf_rollback(buffer,buffer->it-initialpos);
      break;
    }
    else
    {
      alphanum[x++] = c;
    }
  }


  return alphanum;
}

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
      alphanum[x] = '\0';
      break;
    }
    else
    {
      alphanum[x++] = c;
    }
  }

  char* endPtr = NULL;
  long result = strtol(alphanum,&endPtr,10);

  if (alphanum != NULL) free(alphanum);

  return result;
}