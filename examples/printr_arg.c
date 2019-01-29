#include <stdio.h>
#include <stdlib.h>

#include "../lib/gt.h"

void f(int* id) {
  int i;

  for (i = 0; i < 10; i++) {
    printf("%d %d\n", *id, i);
    gt_yield();
  }
}

int main() {
  int i;
  gt_init();

  for (i = 0; i < 270; i++) {
    int id;
    id = i;
    gt_go(f, &id);
  }

  gt_ret(1);
}
