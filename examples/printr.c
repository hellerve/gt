#include <stdio.h>
#include <stdlib.h>

#include "../lib/gt.h"

void f(void* unused) {
  static int x = 0;
  int i, id;

  id = ++x;
  for (i = 0; i < 10; i++) {
    printf("%d %d\n", id, i);
    gt_yield();
  }
}

int main() {
  int i;
  gt_init();

  for (i = 0; i < 270; i++) gt_go(f, NULL);

  gt_ret(1, NULL);
}
