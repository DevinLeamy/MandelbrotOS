#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <stddef.h>
#include <stdint.h>

#include <boot/stivale2.h>
#include <registers.h>

typedef struct proc {
  char *name;
  size_t thread_count;
  int *tids;
} proc_t;

typedef struct thread {
  char *name;
  int state;
  int exit_state;
  int run_once;
  int running;
  size_t tid;
  proc_t *mother_proc;
  registers_t registers;
  struct thread *next;
} thread_t;

void schedule(uint64_t rsp);

void scheduler_init(uintptr_t addr, struct stivale2_struct_tag_smp *smp_info);

#endif
