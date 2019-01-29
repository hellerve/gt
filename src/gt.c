#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../lib/gt.h"

#define INITIAL_THREAD_SIZE 16
#define STACK_SIZE 0x400000 // this is kind of arbitrary

static struct gt* gt_table;
static struct gt* gt_cur;
int SIZE;

void gt_init() {
  SIZE = INITIAL_THREAD_SIZE;
  gt_table = malloc(SIZE*sizeof(struct gt));
  gt_cur = gt_table;
  gt_cur->st = RUNNING;
}

void __attribute__((noreturn)) gt_ret(int ret) {
  if (gt_cur != gt_table) {
    gt_cur->st = UNUSED;
    gt_yield();
    assert(!"reachable");
  }
  while (gt_yield());

  free(gt_table);
  exit(ret);
}

bool gt_yield() {
  struct gt* p;
  struct gt_ctx* old, *new;

  p = gt_cur;
  while (p->st != READY) {
    if (++p == gt_table+SIZE) p = gt_table;
    if (p == gt_cur) return false;
  }

  if (gt_cur->st != UNUSED) gt_cur->st = READY;
  p->st = RUNNING;
  old = &gt_cur->ctx;
  new = &p->ctx;
  gt_cur = p;
  gt_switch(old, new);
  return true;
}

void gt_resize() {
  SIZE *= 2;
  gt_table = realloc(gt_table, SIZE*sizeof(struct gt));
}

void gt_stop() { gt_ret(0); }

void gt_go(gt_fn f) {
  char* stack;
  struct gt* p;

  for (p = gt_table;; p++) {
    if (p == gt_table+SIZE) { gt_resize(); break; }
    else if (p->st == UNUSED) break;
  }

  stack = malloc(STACK_SIZE);
  if (!stack) assert(!"out of memory");;

  *(uint64_t*)&stack[STACK_SIZE-8] = (uint64_t)gt_stop;
  *(uint64_t*)&stack[STACK_SIZE-16] = (uint64_t)f;
  p->ctx.rsp = (uint64_t)&stack[STACK_SIZE-16];
  p->st = READY;
}
