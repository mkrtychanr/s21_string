typedef struct flags flags;

#ifndef SRC_S21_FLAGS_H_
#define SRC_S21_FLAGS_H_

#include "s21_string.h"

struct flags {
  bool minus;
  bool plus;
  bool space;
  bool hashtag;
  bool zero;
  bool precision;
};

void flags_init(flags *f);

bool set_flag(flags *f, char flag);

#endif  // SRC_S21_FLAGS_H_
