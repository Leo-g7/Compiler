#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "expression.h"
#include <ctype.h> // import isdigit
#include "../ast/ast.h"
#include "../../utils/stack.h"

ast_t* convertExpressionIntoAst(ast_list_t* entryAst);

void testConversion() {
  ast_list_t* ast_list = NULL;
  ast_list_add(&ast_list, ast_new_integer(13));
  char plus[] = "+";
  ast_list_add(&ast_list, ast_new_operand(plus));
  ast_list_add(&ast_list, ast_new_integer(2));
  convertExpressionIntoAst(ast_list);
}

//take the expression and returning the ast expression (output)
ast_t* convertExpressionIntoAst(ast_list_t* entryAst) {
  ast_list_t* loopAst = entryAst;
  bool loopFlag = true;
  int size = get_ast_size(entryAst);
  // create stack and add "\0" value
  stack_t* stk = newStack();
  push(stk, '\0');
  while(loopFlag) { // if next ast is not null
    if(loopAst->next == NULL) loopFlag = false;
    else {
      //if(!operandPriority(top(stk), loopAst->ast.)) {

      //}
      loopAst = next_ast(loopAst);
    }
  }
  // Stack *stack;
  // addElement(stack, '\0');
  // char* output = (char*) malloc(sizeof(char) * exprsLength);
  // int index = 0;
  // char jaj = expression[index];
  // while(expression[index] != '\0') {
  //   char c = expression[index];
  //   int len = strlen(stack);
  //   char test = stack[len];
  //   if(!operandPriority(test, c)) { // si haut de stack a une priorité plus basse que symbole
  //     stack = strcat(stack, &expression[index]);
  //     index++;
  //   } else {
  //     int stackIndex = strlen(stack - 1);
  //     do {
  //       strcpy(output, &stack[stackIndex]);
  //       stack[stackIndex] = '\0';
  //       stackIndex--;
  //     } while(!operandPriority(stack[stackIndex], output[strlen(output) - 1]));
  //   }
  // }
  // free(stack);
  ast_t* ast;
  return ast;
}
//take the expression and returning the ast expression (output)

char* getValueFromAst() {
  
}

// check if string is a number
bool isNumber(char* value) {
  for(int i=0; i < strlen(value); i++) {
    if(!isdigit(value[i])) return false;
  }
  return true;
}

//left priority == true, right priority == false
// bool operandPriority(char *op1, char *op2) {

//   if( op1 == '+' && op2 == '+') return true;
//   if( op1 == '+' && op2 == '-') return true;
//   if( op1 == '+' && op2 == '*') return false;
//   if( op1 == '+' && op2 == '/') return false;
//   if( op1 == '+' && isdigit(op2)) return false;
//   if( op1 == '+' && op2 == '\0') return  true; // test todo

//   if( op1 == '-' && op2 == '+') return true;
//   if( op1 == '-' && op2 == '-') return true;
//   if( op1 == '-' && op2 == '*') return false;
//   if( op1 == '-' && op2 == '/') return false;
//   if( op1 == '-' && isdigit(op2)) return false;
//   if( op1 == '-' && op2 == '\0') return  true;

//   if( op1 == '*' && op2 == '+') return true;
//   if( op1 == '*' && op2 == '-') return true;
//   if( op1 == '*' && op2 == '*') return true;
//   if( op1 == '*' && op2 == '/') return true;
//   if( op1 == '*' && isdigit(op2)) return false;
//   if( op1 == '*' && op2 == '\0') return  true;

//   if( op1 == '/' && op2 == '+') return true;
//   if( op1 == '/' && op2 == '-') return true;
//   if( op1 == '/' && op2 == '*') return true;
//   if( op1 == '/' && op2 == '/') return true;
//   if( op1 == '/' && isdigit(op2)) return false;
//   if( op1 == '/' && op2 == '\0') return  true;
  
//   if(isdigit(op1) && op2 == '+') return true;
//   if(isdigit(op1) && op2 == '-') return true;
//   if(isdigit(op1) && op2 == '*') return true;
//   if(isdigit(op1) && op2 == '/') return true;
//   if(isdigit(op1) && isdigit(op2)) exitProgram("Syntax error, no operand between numbers.\n");
//   if(isdigit(op1) && op2 == '\0') return  true;

//   if(op1 == '\0' && op2 == '+') return false;
//   if(op1 == '\0' && op2 == '-') return false;
//   if(op1 == '\0' && op2 == '*') return false;
//   if(op1 == '\0' && op2 == '/') return false;
//   if(op1 == '\0' && isdigit(op2)) return false;
//   if(op1 == '\0' && op2 == '\0') return  false;

//   exitProgram("Unvalid operand.\n");
// }

// void exitProgram(char* msg) {
//   printf(msg);
//   exit(0);
// }