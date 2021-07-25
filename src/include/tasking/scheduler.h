#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <stddef.h>
#include <stdint.h>

#include <boot/stivale2.h>
#include <registers.h>

typedef struct proc {
  char *name;
  int status;
  size_t thread_count;
  size_t pid;
  size_t *tids;
  struct proc *next;
  struct proc *prev;
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
  struct thread *prev;
} thread_t;

void schedule(uint64_t rsp);

void scheduler_init(uintptr_t addr, struct stivale2_struct_tag_smp *smp_info);

#endif
