#include "calc.h"

#include <stdio.h>
#include <stdlib.h>

#include "CException.h"
#include "defines.h"
#include "structs.h"

double calculate(double x, Queue *equation) {
  int id, i = 0;
  double rez;
  Stack *stack = create_stack();
  while (!take_queue(equation, &id, &rez)) {
    consume_calc(stack, id, rez, i, x);
    i++;
  }
  take_stack(stack, &id, &rez);
  kill_stack(stack);
  kill_queue(equation);
  return rez;
}

double (*get_unary(int id))(double) {
  double (*flag)(double n) = NULL;
  if (id == UNARY_MINUS) {
    flag = minus;
  } else if (id == UNARY_PLUS) {
    flag = plus;
  } else if (id == COS) {
    flag = cos;
  } else if (id == SIN) {
    flag = sin;
  } else if (id == TAN) {
    flag = tan;
  } else if (id == CTAN) {
    flag = ctg;
  } else if (id == SQRT) {
    flag = Sqrt;
  } else if (id == LOGN) {
    flag = log;
  } else if (id == ACOS) {
    flag = Acos;
  } else if (id == ASIN) {
    flag = Asin;
  } else if (id == ATAN) {
    flag = atan;
  } else if (id == LOG) {
    flag = log10;
  }
  return flag;
}

double (*get_binary(int id))(double, double) {
  double (*flag)(double a, double b) = NULL;
  if (id == SUM) {
    flag = sum;
  } else if (id == SUB) {
    flag = dif;
  } else if (id == MUL) {
    flag = mult;
  } else if (id == DIV) {
    flag = division;
  } else if (id == POW) {
    flag = pow;
  }
  return flag;
}

double (*get_mod(int id))(double, double) {
  double (*flag)(double a, double b) = NULL;
  if (id == MOD) {
    flag = Mod;
  }
  return flag;
}

double Sqrt(double numb) {
  if (numb < 0.0) Throw(9);
  return sqrt(numb);
}

double Acos(double numb) {
  if (numb < -1.0 || numb > 1.0) Throw(3);
  return acos(numb);
}

double Asin(double numb) {
  if (numb < -1.0 || numb > 1.0) Throw(4);
  return asin(numb);
}

double Mod(double a, double b) {
  if (b == 0.0) Throw(5);
  int i, j;
  i = round(a);
  j = round(b);
  if (i != a && j != b) Throw(8);
  if (i != a) Throw(6);
  if (j != b) Throw(7);
  return i % j;
}

double minus(double numb) { return -numb; }

double plus(double numb) { return numb; }

double sum(double a, double b) { return a + b; }

double dif(double a, double b) { return a - b; }

double mult(double a, double b) { return a * b; }

double division(double a, double b) {
  if (b == 0.0) Throw(1);
  return a / b;
}

double ctg(double numb) {
  if (tan(numb) == 0.0) Throw(2);
  return 1 / tan(numb);
}

void consume_calc(Stack *stack, int id, double rez, int i, double x) {
  if (id == NUM) {
    add_stack(stack, NUM, rez);
  } else if (id == X) {
    add_stack(stack, NUM, x);
  } else if (get_unary(id) != NULL) {
    double (*func)(double num) = get_unary(id);
    take_stack(stack, &id, &rez);
    rez = func(rez);
    add_stack(stack, id, rez);
  } else if (get_mod(id) != NULL) {
    double rez1, rez2;
    double (*func)(double a, double b) = get_mod(id);
    take_stack(stack, &id, &rez1);
    take_stack(stack, &id, &rez2);
    rez1 = func(rez2, rez1);
    add_stack(stack, id, rez1);
  } else if (get_binary(id) != NULL) {
    double rez1, rez2;
    double (*func)(double a, double b) = get_binary(id);
    take_stack(stack, &id, &rez1);
    take_stack(stack, &id, &rez2);
    rez1 = func(rez2, rez1);
    add_stack(stack, id, rez1);
  } else {
    printf("calculating token is fail, i = %i\n", i);
  }
}
