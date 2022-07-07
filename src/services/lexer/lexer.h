#ifndef LEXER_H
#define LEXER_H
#include "../buffer/buffer.h"

void free_lexer(char *lexer);
char *lexer_getalphanum (buffer_t * buffer);
char * lexer_getalphanum_rollback(buffer_t * buffer);
long lexer_getnumber (buffer_t * buffer);
char *move_to_next_lexem(buffer_t * buffer);

#endif /* LEXER_H */