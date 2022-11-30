#include "s21_specs.h"

void specs_init(specs *s) {
  s->d = false;
  s->f = false;
  s->s = false;
  s->g = false;
  s->G = false;
  s->e = false;
  s->E = false;
  s->x = false;
  s->X = false;
  s->c = false;
  s->u = false;
  s->i = false;
  s->o = false;
  s->p = false;
  s->n = false;
}

bool set_spec(specs *s, char spec) {
  bool result = true;
  switch (spec) {
    case 'd':
      s->d = true;
      break;
    case 'f':
      s->f = true;
      break;
    case 's':
      s->s = true;
      break;
    case 'g':
      s->g = true;
      break;
    case 'G':
      s->G = true;
      break;
    case 'e':
      s->e = true;
      break;
    case 'E':
      s->E = true;
      break;
    case 'x':
      s->x = true;
      break;
    case 'X':
      s->X = true;
      break;
    case 'c':
      s->c = true;
      break;
    case 'u':
      s->u = true;
      break;
    case 'i':
      s->i = true;
      break;
    case 'o':
      s->o = true;
      break;
    case 'p':
      s->p = true;
      break;
    case 'n':
      s->n = true;
      break;
    default:
      result = false;
      break;
  }
  return result;
}
