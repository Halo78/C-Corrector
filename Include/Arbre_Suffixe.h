
#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
  char value;
  struct _node *sons, *brothers;
} *tree_t;

