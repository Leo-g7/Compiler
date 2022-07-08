#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "expression.h"
#include <ctype.h> // import isdigit
#include "../ast/ast.h"
#include "../../utils/stack.h"

void testConversion() {
  ast_list_t* ast_list = NULL;
  ast_list_add(&ast_list, ast_new_integer(1));
  char plus[2] = "+";
  ast_list_add(&ast_list, ast_new_operand(plus));
  ast_list_add(&ast_list, ast_new_integer(2));
  char mult[2] = "*";
  ast_list_add(&ast_list, ast_new_operand(mult));
  ast_list_add(&ast_list, ast_new_integer(3));
  char minus[2] = "-";
  ast_list_add(&ast_list, ast_new_operand(minus));
  ast_list_add(&ast_list, ast_new_integer(4));
  ast_list_add(&ast_list, ast_new_operand(plus));
  ast_list_add(&ast_list, ast_new_integer(5));

  convertExpressionIntoAst(ast_list);
}

char* strfromlonglong(long value);

//takes the expression and returns the ast expression (output)
ast_t* convertExpressionIntoAst(ast_list_t* entryAst) {
  ast_list_t* loopAst = entryAst;
  int size = get_ast_size(entryAst);
  // create output stack
  stack_t* output = newStack();
  // create stack and add "\0" value
  stack_t* stk = newStack();
  char endOfString[1] = "\0";
  push(stk, endOfString);
  while(true) { // if next ast is not null
    char* onTopElement;
    char* astValue;
    if(loopAst == NULL) break; // todo
    bool isLastStackElement = strcmp(top(stk), "\0") == 0;
    if(isLastStackElement && loopAst == NULL) break;
    astValue = getValueFromAst(loopAst->ast);
    onTopElement = top(stk);
    
    bool res = operandPriority(onTopElement, astValue);
    if(!res) {
      push(stk, astValue);
      loopAst = next_ast(loopAst);
    } else {
      char* lastElem;
      do {
        push(output, top(stk));
        printf("%s\b", onTopElement);
        pop(stk);
      } while(operandPriority(top(stk), top(output)));
    }
  }
  // set debug point here to see the objet (not complete)
  ast_t* ast;
  return ast;
}

// attributes are not the same according to the ast type, this functions check the ast type and returns the value of the ast
char* getValueFromAst(ast_t* ast) {
  if(ast->type == 1) { // AST_INTEGER
    char* str = strfromlonglong(ast->integer);
    return str;
  } else if(ast->type == 3) { // AST_OPERAND
    return ast->operand.operValue;
  }
}

// check if string is a number
bool isNumber(char* value) {
  if(strlen(value) == 0) return false;
  for(int i=0; i < strlen(value); i++) {
    char c = value[i];
    if(!isdigit(c)) return false;
  }
  return true;
}

//left priority == true, right priority == false
bool operandPriority(char *op1, char *op2) {

  if(strcmp(op1, "+") == 0 && strcmp(op2, "+") == 0) return true;
  if(strcmp(op1, "+") == 0 && strcmp(op2, "-") == 0) return true;
  if(strcmp(op1, "+") == 0 && strcmp(op2, "*") == 0) return false;
  if(strcmp(op1, "+") == 0 && strcmp(op2, "/") == 0) return false;
  if(strcmp(op1, "+") == 0 && isNumber(op2)) return false;
  if(strcmp(op1, "+") == 0 && strcmp(op2, "\0") == 0) return  true; // test todo

  if(strcmp(op1, "-") == 0 && strcmp(op2, "+") == 0) return true;
  if(strcmp(op1, "-") == 0 && strcmp(op2, "-") == 0) return true;
  if(strcmp(op1, "-") == 0 && strcmp(op2, "*") == 0) return false;
  if(strcmp(op1, "-") == 0 && strcmp(op2, "/") == 0) return false;
  if(strcmp(op1, "-") == 0 && isNumber(op2)) return false;
  if(strcmp(op1, "-") == 0 && strcmp(op2, "\0") == 0) return  true;

  if(strcmp(op1, "*") == 0 && strcmp(op2, "+") == 0) return true;
  if(strcmp(op1, "*") == 0 && strcmp(op2, "-") == 0) return true;
  if(strcmp(op1, "*") == 0 && strcmp(op2, "*") == 0) return true;
  if(strcmp(op1, "*") == 0 && strcmp(op2, "/") == 0) return true;
  if(strcmp(op1, "*") == 0 && isNumber(op2)) return false;
  if(strcmp(op1, "*") == 0 && strcmp(op2, "\0") == 0) return  true; 

  if(strcmp(op1, "/") == 0 && strcmp(op2,"+") == 0) return true;
  if(strcmp(op1, "/") == 0 && strcmp(op2,"-") == 0) return true;
  if(strcmp(op1, "/") == 0 && strcmp(op2,"*") == 0) return true;
  if(strcmp(op1, "/") == 0 && strcmp(op2,"/") == 0) return true;
  if(strcmp(op1, "/") == 0 && isNumber(op2)) return false;
  if(strcmp(op1, "/") == 0 && strcmp(op2, "\0") == 0) return  true;
  
  if(isNumber(op1) && strcmp(op2, "+") == 0) return true;
  if(isNumber(op1) && strcmp(op2, "-") == 0) return true;
  if(isNumber(op1) && strcmp(op2, "*") == 0) return true;
  if(isNumber(op1) && strcmp(op2, "/") == 0) return true;
  if(isNumber(op1) && isNumber(op2)) exitProgram("Syntax error, no operand between numbers.\n");
  if(isNumber(op1) && strcmp(op2, "\0") == 0) return  true;

  if(strcmp(op1, "\0") == 0 && strcmp(op2, "+") == 0) return false;
  if(strcmp(op1, "\0") == 0 && strcmp(op2, "-") == 0) return false;
  if(strcmp(op1, "\0") == 0 && strcmp(op2, "*") == 0) return false;
  if(strcmp(op1, "\0") == 0 && strcmp(op2, "/") == 0) return false;
  if(strcmp(op1, "\0") == 0 && isNumber(op2)) return false;
  if(strcmp(op1, "\0") == 0 && strcmp(op2, "\0") == 0) return  false;

  exitProgram("Unvalid operand.\n");
}

void exitProgram(char* msg) {
  printf(msg);
  exit(0);
}

char* strfromlonglong(long value) {
  char buf[32], *p;
  unsigned long v;

  v = (value < 0) ? -value: value;
  p = buf + 31;
  do{
    *p -- = '0' + (v%10);
    v /= 10;
  } while(v);
  if(value < 0) *p -- = '-';
  p ++;

  int len = 32 - (p - buf);
  char *s = (char*)malloc(sizeof(char) * (len + 1));
  memcpy(s, p, len);
  s[len] = '\0';
  return s;
}