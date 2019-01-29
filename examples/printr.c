#include <stdio.h>

#include "../lib/gt.h"

void f() {
  static int x;
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

  for (i = 0; i < 270; i++) gt_go(f);

  gt_ret(1);
}
