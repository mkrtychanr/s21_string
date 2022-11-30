typedef struct specs specs;

#ifndef SRC_S21_SPECS_H_
#define SRC_S21_SPECS_H_

#include "s21_string.h"

struct specs {
  bool d;
  bool f;
  bool s;
  bool g;
  bool G;
  bool e;
  bool E;
  bool x;
  bool X;
  bool c;
  bool u;
  bool i;
  bool o;
  bool p;
  bool n;
};

void specs_init(specs *s);

bool set_spec(specs *s, char spec);

#endif  // SRC_S21_SPECS_H_
