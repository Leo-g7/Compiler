#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "../ast/ast.h"
#include "../buffer/buffer.h"

// Return the next char* in the buffer and put the cursor at the end of this char*
void free_lexer(char *lexer) {
  if (lexer != NULL)
  {
    free(lexer);
  }
}

char *lexer_getalphanum (buffer_t * buffer) {
  long counter = buffer->it;
  char *alphanum = malloc(BUF_SIZE);
  int x = 0;

  while (buf_eof(buffer) == false)
  {
    char c = buf_getchar(buffer);

    if(++counter < buffer->it || (isalpha(c) && !isdigit(c) && ispunct(c)) )
    {
      buf_rollback(buffer,buffer->it-counter+1);
      break;
    }
    else
    {
      //Horrible code but it work
      if(ispunct(c) && x>0)
      {
        buf_rollback(buffer,buffer->it-counter+1);
        alphanum[x] = '\0';
        return alphanum;
      }

      alphanum[x++] = c;

      if(ispunct(c) && x==1)
      {
        alphanum[x] = '\0';
        return alphanum;
      }
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

    if(++counter < buffer->it || (isalpha(c) && !isdigit(c) && ispunct(c) ))
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

char *move_to_next_lexem(buffer_t * buffer) {
  buf_skipblank(buffer);
  return lexer_getalphanum(buffer);
}