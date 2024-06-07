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

/**
 * @file  sched.h
 * @brief Contains declarations for process scheduler.
 * 
 * @details This header file includes functions and structs related
 * to the kernel process scheduler.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   29.05.2024
 */

#ifndef _NOS_KERNEL_SCHED_H_
#define _NOS_KERNEL_SCHED_H_

#include <nos/types.h>
#include <nos/gdt.h>
#include <nos/pm.h>

#define MAX_PROCESSES 64

struct sched_s {
    pcb_t *processes[MAX_PROCESSES]; ///< Array of processes.
    s32   front;    ///< Index of the front of the queue.
    s32   rear;     ///< Index of the rear of the queue.
};

typedef struct sched_s sched_t;

/** @brief Initialize process scheduler. */ 
void sched_init(void);

/**
 * @brief Add new process to scheduler. 
 * 
 * @param [in] proc - given new process. 
 */
void sched_add(pcb_t *proc);

/**
 * @brief Get scheduler struct.
 * 
 * @return Scheduler struct pointer.
 */
sched_t *get_sched(void);

#endif /* _NOS_KERNEL_SCHED_H_ */