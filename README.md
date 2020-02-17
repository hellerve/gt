# gt

A simple greenthreads implementation for massive lightweight threads. It’s
adapted from [this tutorial](https://c9x.me/articles/gthreads/intro.html), with
the—kind of important—additions that the list of scheduled threads grows
dynamically instead of failing to schedule if the maximum thread number is
reached, and that you can pass one argument to the functions (through the use
of structs you can add as many arguments as you like).

I’d like to use this as a testbed to play around with schedulers if I find the
time.

## Example

```c
#include <stdio.h>

#include "gt.h"

void f(void* unused) {
  static int x;
  int i, id;

  id = ++x; // thread ID
  for (i = 0; i < 10; i++) {
    printf("%d %d\n", id, i);
    gt_yield();
  }
}

int main() {
  int i;
  gt_init();

  // no argument; pass an argument instead of NULL here
  for (i = 0; i < 270; i++) gt_go(f, NULL);

  // the second argument is an optional cleanup function
  gt_ret(1, NULL);
}
```

<hr/>

Have fun!
