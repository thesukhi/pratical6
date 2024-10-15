#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_SIZE 100
struct CharStack {
 int top;
 char elements[MAX_SIZE];
};
int isCharStackEmpty(struct CharStack *stack) {
 return stack->top == -1;
}
char charPeek(struct CharStack *stack) {
 return stack->elements[stack->top];
}
char charPop(struct CharStack *stack) {
 if (!isCharStackEmpty(stack))
 return stack->elements[stack->top--];
 return '\0';
}
void charPush(struct CharStack *stack, char ch) {
 stack->elements[++stack->top] = ch;
}
int charPrecedence(char ch) {
 switch (ch) {
 case '+':
 case '-':
 return 1;
 case '*':
 case '/':
 return 2;
 case '^':
 return 3;
 }
 return -1;
}
// Convert infix to postfix
void convertInfixToPostfix(char *expression) {
 struct CharStack stack;
 stack.top = -1;
 int i, j;
 char output[MAX_SIZE];
 for (i = 0, j = 0; expression[i]; i++) {
 if (isalnum(expression[i])) {
 output[j++] = expression[i];
 } else if (expression[i] == '(') {
 charPush(&stack, expression[i]);
 } else if (expression[i] == ')') {
 while (!isCharStackEmpty(&stack) && charPeek(&stack) != '(')
 output[j++] = charPop(&stack);
 charPop(&stack); // Remove '('
 } else {
 while (!isCharStackEmpty(&stack) && charPrecedence(expression[i]) <=
charPrecedence(charPeek(&stack)))
 output[j++] = charPop(&stack);
 charPush(&stack, expression[i]);
 }
 }
 while (!isCharStackEmpty(&stack))
 output[j++] = charPop(&stack);
 output[j] = '\0';
 printf("Postfix Expression: %s\n", output);
}
void reverseString(char *str) {
 int length = strlen(str);
 for (int i = 0; i < length / 2; i++) {
 char temp = str[i];
 str[i] = str[length - i - 1];
 str[length - i - 1] = temp;
 }
}
// Convert infix to prefix
void convertInfixToPrefix(char *expression) {
 reverseString(expression);
 struct CharStack stack;
 stack.top = -1;
 int i, j;
 char output[MAX_SIZE];
 for (i = 0, j = 0; expression[i]; i++) {
 if (isalnum(expression[i])) {
 output[j++] = expression[i];
 } else if (expression[i] == ')') {
 charPush(&stack, expression[i]);
 } else if (expression[i] == '(') {
 while (!isCharStackEmpty(&stack) && charPeek(&stack) != ')')
 output[j++] = charPop(&stack);
 charPop(&stack);
 } else {
 while (!isCharStackEmpty(&stack) && charPrecedence(expression[i]) <
charPrecedence(charPeek(&stack)))
 output[j++] = charPop(&stack);
 charPush(&stack, expression[i]);
 }
 }
 while (!isCharStackEmpty(&stack))
 output[j++] = charPop(&stack);
 output[j] = '\0';
 reverseString(output);
 printf("Prefix Expression: %s\n", output);
}
struct IntStack {
 int top;
 int elements[MAX_SIZE];
};
int isIntStackEmpty(struct IntStack *stack) {
 return stack->top == -1;
}
int intPop(struct IntStack *stack) {
 return stack->elements[stack->top--];
}
void intPush(struct IntStack *stack, int value) {
 stack->elements[++stack->top] = value;
}
// Evaluate postfix expression
int evaluatePostfixExpression(char *expression) {
 struct IntStack stack;
 stack.top = -1;
 int i;
 for (i = 0; expression[i]; i++) {
 if (isdigit(expression[i])) {
 intPush(&stack, expression[i] - '0');
 } else {
 int val1 = intPop(&stack);
 int val2 = intPop(&stack);
 switch (expression[i]) {
 case '+':
 intPush(&stack, val2 + val1);
 break;
 case '-':
 intPush(&stack, val2 - val1);
 break;
 case '*':
 intPush(&stack, val2 * val1);
 break;
 case '/':
 intPush(&stack, val2 / val1);
 break;
 }
 }
 }
 return intPop(&stack);
}
int main() {
 int option;
 char expression[MAX_SIZE];
 do {
 printf("\nMenu:\n");
 printf("1. Infix to Postfix\n");
 printf("2. Infix to Prefix\n");
 printf("3. Evaluate Postfix\n");
 printf("4. Exit\n");
 printf("Enter your choice: ");
 scanf("%d", &option);
 getchar();
 switch (option) {
 case 1:
 printf("Enter infix expression: ");
 fgets(expression, MAX_SIZE, stdin);
 expression[strcspn(expression, "\n")] = 0;
 convertInfixToPostfix(expression);
 break;
 case 2:
 printf("Enter infix expression: ");
 fgets(expression, MAX_SIZE, stdin);
 expression[strcspn(expression, "\n")] = 0;
 convertInfixToPrefix(expression);
 break;
 case 3:
 printf("Enter postfix expression: ");
 fgets(expression, MAX_SIZE, stdin);
 expression[strcspn(expression, "\n")] = 0;
 printf("Result of Postfix Evaluation: %d\n", evaluatePostfixExpression(expression));
 break;
 case 4:
 printf("Exit the Program.\n");
 exit(0);
 default:
 printf("Invalid choice!\n");
 }
 } while (1);
 return 0;
}