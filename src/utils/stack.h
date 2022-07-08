#ifndef STACK_H
#define STACK_H

/**
 * Type for individual stack entry
 */
typedef struct stack_entry {
  char data[15];
  struct stack_entry *next;
} stack_entry;

/**
 * Type for stack instance
 */
typedef struct stack_t
{
  stack_entry *head;
  size_t stackSize;  // not strictly necessary, but
                     // useful for logging
} stack_t;

struct stack_t *newStack();
char *copyString(char *str);
void push(struct stack_t *theStack, char *value);
char *top(struct stack_t *theStack);
void pop(struct stack_t *theStack);
void clear (struct stack_t *theStack);
void destroyStack(struct stack_t **theStack);

#endif /* STACK_H */