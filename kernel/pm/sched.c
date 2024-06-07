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

#include <string.h>
#include <stdio.h>

#include <nos/kernel.h>
#include <nos/sched.h>
#include <nos/types.h>
#include <nos/gdt.h>
#include <nos/pm.h>

static sched_t scheduler;

void sched_init(void)
{
    bzero(scheduler.processes, sizeof(pcb_t) * MAX_PROCESSES);
    scheduler.front = -1;
    scheduler.rear  = -1;
}

void sched_add(pcb_t *proc)
{
    /* Handle full queue */
    if (scheduler.rear == MAX_PROCESSES - 1)
        puts(" kernel: warning: Scheduler queue is full. Cannot add new processes.");
    else {
        /* Handle empty queue */
        if (scheduler.front == -1)
            scheduler.front++;

        scheduler.rear++;
        scheduler.processes[scheduler.rear] = proc;
        printk(" kernel: sched: added new process '%s'\n", proc->name);
    }   
}

sched_t *get_sched(void)
{
    return &scheduler;
}