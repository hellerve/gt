# gt

A simple greenthreads implementation for massive lightweight threads. It’s
adapted from [this tutorial](https://c9x.me/articles/gthreads/intro.html), with
the—kind of important—addition that the list of scheduled threads grows
dynamically instead of failing to schedule if the maximum thread number is
reached.

I’d like to use this as a testbed to play around with schedulers if I find the
time, and add functionality to hand a function parameters.

## Example

```c
#include <stdio.h>

#include "gt.h"

void f() {
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

  for (i = 0; i < 270; i++) gt_go(f);

  gt_ret(1);
}
```

## TODO

There is a memory error that you can examine by running `-fsanitize=address`.
The example program seems to run fine either way, but there is something wicked
in the weeds.

<hr/>

Have fun!
