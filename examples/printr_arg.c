#include <stdio.h>
#include <stdlib.h>

#include "../lib/gt.h"

int* ids;

void f(int* id) {
  int i;

  for (i = 0; i < 10; i++) {
    printf("%d %d\n", *id, i);
    gt_yield();
  }
}

void cleanup() {
  free(ids);
}

int main() {
  int i;
  ids = malloc(sizeof(int)*270);
  gt_init();

  for (i = 0; i < 270; i++) {
    ids[i] = i;
    gt_go(f, &ids[i]);
  }

  gt_ret(1, cleanup);
}
