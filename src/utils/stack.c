#include <stdlib.h>
#include <string.h>
#include "stack.h"

/**
 * Create a new stack instance
 */
struct stack_t *newStack()
{
  struct stack_t *stk = (stack_t*) malloc(sizeof(stack_t));
  if (stk)
  {
    stk->head = NULL;
    stk->stackSize = 0;
  }
  return stk;
}

/**
 * Make a copy of the string to be stored (assumes  
 * strdup() or similar functionality is not
 * available
 */
char *copyString(char *str)
{
  char *tmp = malloc(strlen(str) + 1);
  if (tmp)
    strcpy(tmp, str);
  return tmp;
}

/**
 * Push a value onto the stack
 */
void push(struct stack_t *theStack, char *value)
{
  struct stack_entry *entry = (stack_entry*) malloc(sizeof(stack_entry)); 
  if (entry)
  {
    strcpy(entry->data, value);
    entry->next = theStack->head;
    theStack->head = entry;
    theStack->stackSize++;
  }
  else
  {
    // handle error here
  }
}

/**
 * Get the value at the top of the stack
 */
char *top(struct stack_t *theStack)
{
  if (theStack && theStack->head)
    return theStack->head->data;
  else
    return NULL;
}

/**
 * Pop the top element from the stack; this deletes both 
 * the stack entry and the string it points to
 */
void pop(struct stack_t *theStack)
{
  if (theStack->head != NULL)
  {
    struct stack_entry *tmp = theStack->head;
    theStack->head = theStack->head->next;
    free(tmp->data);
    free(tmp);
    theStack->stackSize--;
  }
}

/**
 * Clear all elements from the stack
 */
void clear (struct stack_t *theStack)
{
  while (theStack->head != NULL)
    pop(theStack);
}

/**
 * Destroy a stack instance
 */
void destroyStack(struct stack_t **theStack)
{
  clear(*theStack);
  free(*theStack);
  *theStack = NULL;
}