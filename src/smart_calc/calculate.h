#ifndef CALCULATE_H_
#define CALCULATE_H_

// ============================= STACK

typedef struct node {
  char ch;
  int priority;
  int associative;
  struct node *next;
} stack_o;

typedef struct noden {
  double value;
  struct noden *next;
} stack_n;

stack_o *push_o(char c, stack_o *root);
char pop_o(stack_o **root);

stack_n *push_n(double input, stack_n *root);
double pop_n(stack_n **root);

// ============================= CALC

int calculate(char *src, double *result, double valX);
int calc_func(char ch, stack_n **nums);
int SmartCalc(char *inputStr, double *result, double *argX);

// ============================= POLISH

#define is_operator(ch)                                             \
  (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '^' || \
   ch == '(' || ch == ')')
#define is_operators(ch)                                            \
  (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '^' || \
   ch == '(' || ch == 'o' || ch == 's' || ch == 'a' || ch == 'c' || \
   ch == 't' || ch == 'q' || ch == 'l' || ch == 'g' || ch == 'm' || ch == 'n')

#define is_prefix_f(ch)                                             \
  (ch == '~' || ch == 'o' || ch == 's' || ch == 'a' || ch == 'c' || \
   ch == 't' || ch == 'q' || ch == 'l' || ch == 'g' || ch == 'n')

#define is_binar_f(ch) \
  (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '^' || ch == 'm')

int reverse_polish(char *src, char *dst);
int reduce_infix(char *src, char *dst);
int check_brackets(char *src);
int set_priority(char ch);
int set_associative(char ch);
int parse_digits(char *src, char *dst, int *i, int *j);
void is_unary(char *src, int i);
int insertArgX(char *dst, int j, double *argX);
int isValid(char *str);

#endif
