/* MIT License
 *
 * Copyright (c) 2024 Alexander (@alkuzin)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. */

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <nos/kernel.h>
#include <nos/nosstd.h>
#include <sys/types.h>
#include <nos/gdt.h>
#include <nos/pm.h>

static pid_t next_pid = 1;

pcb_t *pm_create_proc(const char *name, i32 priority)
{
    pcb_t *proc;

    proc = kmalloc(sizeof(pcb_t));

    /* initializing PCB fields */
    strncpy(proc->name, name, PROC_NAME_MAX_SIZE);
    proc->priority   = priority;
    proc->state      = TASK_STATE_READY;
    proc->parent_pid = next_pid - 1;
    proc->pid        = pm_getupid();
    proc->base       = (u32)kmalloc(PROC_MEMORY_SIZE);

    if (!proc->base)
        panic("%s\n", "memory allocation error");

    proc->size       = PROC_MEMORY_SIZE;
    proc->counter    = 0;
    proc->signal     = 0;
    // TODO: set proc->tss
    
    return proc;
}

pid_t pm_getupid(void)
{
    return next_pid++;
}

// The operating system allocates a new process control block (PCB) 
// for the child process.
// The memory space of the parent process is duplicated for the 
// child process using a technique called copy-on-write (COW). 
// This means that the physical memory is not immediately copied, 
// but shared between the parent and child processes. Only when 
// one of the processes tries to modify the memory, a separate copy 
// is created.
// File descriptors, signal handlers, and other process attributes 
// are also duplicated for the child process.
// The child process is assigned a new PID (process ID).
// Both the parent and child processes continue execution from the fork() 
// system call, but with different return values. The parent receives the 
// PID of the child process, while the child receives a return value of 0.

// pid_t fork(void)
// {
//     pcb_t *proc;

//     proc = kmalloc(sizeof(pcb_t));
// }