#ifndef STACK_H
#define STACK_H
#include "../utils/stack.h"

struct stack_entry;
struct stack_t;
struct stack_t *newStack(void);
char* copyString(char *str);
void push(struct stack_t *theStack, char *value);
char* top(struct stack_t *theStack);
void pop(struct stack_t *theStack);
void clear (struct stack_t *theStack);
void destroyStack(struct stack_t **theStack);

#endif /* STACK_H */