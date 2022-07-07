#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h> // import isdigit
#include "services/buffer/buffer.h"
#include "services/lexer/lexer.h"
#include "services/ast/ast.h"
#include "utils/stack.h"

ast_t* convertExpressionIntoAst(ast_list_t* entryAst);
bool operandPriority(char* op1, char* op2);
// void exitProgram(char* msg);
int main(int argc, char *argv[]) 
{
  return 0;
}

// int main(int argc, char *argv[]) {
//   if (argc == 2 || argc == 5) {
//     ast_list_t* first;
//     first->ast = ast_new_integer(10);
//     ast_list_t* second;
//     second->ast = ast_new_operand('+', NULL);
//     ast_list_t* third = ast_new_integer(2);
//     second->next = third;
//     first->next = second;
//   }
// }

// take the expression and returning the ast expression (output)
//ast_t* convertExpressionIntoAst(ast_list_t* entryAst) {
  // int exprsLength = strlen(expression);
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
  // return output;
//}

// check if string is a number
// bool isNumber(char* value) {
//   for(int i=0; i < strlen(value); i++) {
//     if(!isdigit(value[i])) return false;
//   }
//   return true;
// }





// left priority == true, right priority == false
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

