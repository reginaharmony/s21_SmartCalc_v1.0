#include "calculate.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================= STACK

stack_o *push_o(char c, stack_o *root) {
  stack_o *tmp = malloc(sizeof(stack_o));
  tmp->priority = set_priority(c);
  tmp->associative = set_associative(c);
  tmp->ch = c;
  tmp->next = root;
  return tmp;
}

char pop_o(stack_o **root) {
  stack_o *tmp = *root;
  char c;
  if (*root == NULL)
    c = '\0';
  else
    c = tmp->ch, *root = tmp->next, free(tmp);
  return c;
}

stack_n *push_n(double input, stack_n *root) {
  stack_n *tmp = malloc(sizeof(stack_n));
  tmp->value = input;
  tmp->next = root;
  return tmp;
}

double pop_n(stack_n **root) {
  stack_n *tmp = *root;
  double output;
  if (*root == NULL)
    output = 0;
  else
    output = tmp->value, *root = tmp->next, free(tmp);
  return output;
}

// ============================= POLISH

int reduce_infix(char *src, char *dst) {
  int error = 1, i = 0, j = 0;
  for (; src[j] != '\0' && error; j++) {
    if (!strncmp(src + j, "sin(", 4))
      dst[i++] = 's', dst[i++] = ' ', j += 2;
    else if (!strncmp(src + j, "cos(", 4))
      dst[i++] = 'c', dst[i++] = ' ', j += 2;
    else if (!strncmp(src + j, "tan(", 4))
      dst[i++] = 't', dst[i++] = ' ', j += 2;
    else if (!strncmp(src + j, "atan(", 5))
      dst[i++] = 'a', dst[i++] = ' ', j += 3;
    else if (!strncmp(src + j, "acos(", 5))
      dst[i++] = 'o', dst[i++] = ' ', j += 3;
    else if (!strncmp(src + j, "asin(", 5))
      dst[i++] = 'n', dst[i++] = ' ', j += 3;
    else if (!strncmp(src + j, "sqrt(", 5))
      dst[i++] = 'q', dst[i++] = ' ', j += 3;
    else if (!strncmp(src + j, "log(", 4))
      dst[i++] = 'g', dst[i++] = ' ', j += 2;
    else if (!strncmp(src + j, "ln(", 3))
      dst[i++] = 'l', dst[i++] = ' ', j++;
    else if (!strncmp(src + j, "mod", 3))
      dst[i++] = 'm', dst[i++] = ' ', j += 2;
    else if (is_operator(src[j]) || src[j] == 'x')
      dst[i] = src[j], is_unary(dst, i), i++, dst[i++] = ' ';
    else if (isdigit(src[j]) || src[j] == '.')
      error = parse_digits(src, dst, &j, &i), j--;
    else if (src[j] == ' ')
      continue;
    else
      error = 0;
  }
  return i--, dst[i] = '\0', error;
}

int check_brackets(char *src) {
  // First loop: Check for error condition (empty brackets)
  for (int i = 0; src[i] != '\0'; i++) {
    if (src[i] == '(' && src[i + 1] == ')')
      return 0;  // Return  0 indicating an error
  }

  int count = 0;
  for (int i = 0; src[i] != '\0'; i++) {
    if (src[i] == '(')
      count++;
    else if (src[i] == ')')
      count--;
  }
  return count == 0;
}

int isValid(char *str) {
  char tsrc[512];
  int flag = check_brackets(str) && reduce_infix(str, tsrc);
  return flag;
}

int set_priority(char ch) {
  int priority = -1;
  if (ch == '^')
    priority = 3;
  else if (ch == 's' || ch == 'c' || ch == 't' || ch == 'q' || ch == 'l' ||
           ch == 'o' || ch == 'n' || ch == 'a' || ch == 'g' || ch == '~')
    priority = 4;
  else if (ch == '*' || ch == 'm' || ch == '/')
    priority = 2;
  else if (ch == '-' || ch == '+')
    priority = 1;

  return priority;
}

int set_associative(char ch) {
  int associative = -1;
  if (ch == '*' || ch == '/' || ch == '+' || ch == '-' || ch == 'm')
    associative = 0;
  else if (ch == '^')
    associative = 1;
  return associative;
}

int parse_digits(char *src, char *dst, int *i, int *j) {
  int temp_i = *i;
  int temp_j = *j;
  int error = 1;
  int dot_count = 0;
  while ((isdigit(src[temp_i]) || src[temp_i] == '.') && error) {
    if (src[temp_i] == '.') dot_count++;
    if (dot_count > 1) error = 0;
    dst[temp_j++] = src[temp_i++];
  }
  dst[temp_j++] = ' ';
  *i = temp_i;
  *j = temp_j;
  return error;
}

void is_unary(char *src, int i) {
  if (src[i] == '-' || src[i] == '+') {
    int temp_i = i;
    char change = (src[i] == '-') ? '~' : ' ';
    if (!i)
      src[temp_i] = change;
    else {
      i ? i-- : 0;
      for (; i > 0 && src[i] == ' ';) i--;
      if (is_binar_f(src[i]) || src[i] == '(') src[temp_i] = change;
    }
  }
}

int reverse_polish(char *tsrc, char *dst) {
  stack_o *opers = NULL;
  char src[512];
  int j = 0;
  int flag = check_brackets(tsrc) && reduce_infix(tsrc, src);
  if (flag) {
    for (int i = 0; src[i] != '\0' && i < 256 && flag;) {
      if (src[i] == '.' || isdigit(src[i]))
        flag = parse_digits(src, dst, &i, &j);
      if (src[i] == 'x') dst[j++] = src[i++], dst[j++] = ' ';
      if (is_prefix_f(src[i]) || is_binar_f(src[i])) {
        while (opers != NULL && (is_prefix_f(opers->ch) ||
                                 (set_priority(src[i]) <= opers->priority) ||
                                 (opers->associative &&
                                  set_priority(src[i]) == opers->priority))) {
          dst[j++] = pop_o(&opers);
          dst[j++] = ' ';
        }
        opers = push_o(src[i++], opers);
      }
      if (src[i] == '(') opers = push_o(src[i++], opers);
      if (src[i] == ')') {
        while (opers != NULL && opers->ch != '(') {
          dst[j++] = pop_o(&opers);
          dst[j++] = ' ';
        }
        if (opers != NULL)
          pop_o(&opers);
        else
          flag = 0;
        i++;
      }
      if (src[i] == ' ') i++;
    }
    while (opers != NULL) dst[j++] = pop_o(&opers), dst[j++] = ' ';
    dst[--j] = '\0';
  } else
    dst = NULL;

  return flag;
}

// ============================= CALCLUATE

int calc_binar_func(char ch, stack_n **nums) {
  int flag = 1;
  double a, b;

  if (*nums != NULL) {
    a = pop_n(nums);
    if (*nums != NULL)
      b = pop_n(nums);
    else
      flag = 0;
  } else
    flag = 0;

  if (flag) {
    if (ch == '+')
      a = b + a;
    else if (ch == '-')
      a = b - a;
    else if (ch == '*')
      a = b * a;
    else if (ch == '/')
      a = b / a;
    else if (ch == '^')
      a = pow(b, a);
    else if (ch == 'm')
      a = fmod(b, a);
    *nums = push_n(a, *nums);
  }
  return flag;
}

int calc_unary_func(char ch, stack_n **nums) {
  int flag = 1;
  double bin_res, a;

  if (*nums != NULL)
    a = pop_n(nums);
  else
    flag = 0;

  if (flag) {
    if (ch == 's')
      bin_res = sin(a);
    else if (ch == 'c')
      bin_res = cos(a);
    else if (ch == 't')
      bin_res = tan(a);
    else if (ch == 'a')
      bin_res = atan(a);
    else if (ch == 'o')
      bin_res = acos(a);
    else if (ch == 'n')
      bin_res = asin(a);
    else if (ch == 'q')
      bin_res = sqrt(a);
    else if (ch == 'g')
      bin_res = log10(a);
    else if (ch == 'l')
      bin_res = log(a);
    else if (ch == '~')
      bin_res = -1 * a;
  }

  if (flag) *nums = push_n(bin_res, *nums);
  return flag;
}

int calc_func(char ch, stack_n **nums) {
  return is_binar_f(ch) ? calc_binar_func(ch, nums) : calc_unary_func(ch, nums);
}

int calculate(char *src, double *result, double valX) {
  int flag = 1;
  stack_n *nums = NULL;

  for (int i = 0; src[i] != '\0'; i++) {
    if (isdigit(src[i]) || src[i] == '.') {
      char num_buf[25] = "";
      int j = 0;
      parse_digits(src, num_buf, &i, &j);
      nums = push_n(atof(num_buf), nums);
    } else if (is_binar_f(src[i]) || is_prefix_f(src[i]))
      flag = calc_func(src[i], &nums);
    else if (src[i] == 'x')
      nums = push_n(valX, nums);
  }
  *result = pop_n(&nums);

  return flag;
}

int SmartCalc(char *inputStr, double *result, double *argX) {
  char RpnStr[512];
  double valueX = 0;
  if (argX != NULL) valueX = *argX;
  int flag = 0;
  flag = reverse_polish(inputStr, RpnStr);
  if (flag) flag = calculate(RpnStr, result, valueX);
  return flag;
}
