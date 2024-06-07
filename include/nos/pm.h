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
 * @file  pm.h
 * @brief Contains declarations for process management.
 * 
 * @details This header file includes functions and structs related
 * to the kernel process management.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   29.05.2024
 */

#ifndef _NOS_KERNEL_PM_H_
#define _NOS_KERNEL_PM_H_

#include <nos/types.h>
#include <nos/gdt.h>

#define PROC_NAME_MAX_SIZE 64
#define PROC_MEMORY_SIZE   1024 /* 1 KB */

/**
 * @brief Task priority enumeration.
 * 
 * 0 - high priority;
 * 1 - medium priority; 
 * 2 - low priority.
 */
enum task_priority_e {
    HIGH_PRIORITY,
    MEDIUM_PRIORITY,
    LOW_PRIORITY
};

/**
 * @brief Task state enumeration.
 * 
 * 0 - task is running;
 * 1 - task is ready;
 * 2 - task is blocked;
 * 3 - task is terminated. 
 */
enum task_state_e {
    TASK_STATE_RUNNING,
    TASK_STATE_READY,
    TASK_STATE_BLOCKED,
    TASK_STATE_TERMINATED
};

typedef enum task_state_e task_state_t;
/**
 * @brief Process Control Block (PCB) - used by the operating system to 
 * manage and track information about a process.
 * 
 * The PCB contains essential information about a process, allowing the 
 * operating system to manage and control its execution.
 */
struct pcb_s {
    pid_t pid;          ///< A unique identifier assigned to each process in the system.
    s32   priority;     ///< Indicates the priority level of the process.
    pid_t parent_pid;   ///< PID of the parent process that created the curren Task priorityt process.
    s32   signal;       ///< Signal flag that associated with a process.
    s32   counter;      ///< Address of the next instruction to be executed by the process.
    task_state_t state; ///< Indicates the current state of the process.
    tss_entry_t  tss;   ///< Task State Segment (TSS) entry.
    char name[PROC_NAME_MAX_SIZE];
    u32 base; ///< Base address of allocated memory.
    u32 size; ///< Size of allocated memory.
}__attribute__((packed)); ///< prevent the compiler from optimizing

typedef struct pcb_s pcb_t;

/**
 * @brief Create new process.
 * 
 * @param [in] name - given new process name.
 * @param [in] priority - given new process priority.
 * @return pointer to the new PCB.
 */
pcb_t *pm_create_proc(const char *name, s32 priority);

/**
 * @brief Get unique process identificator. 
 * 
 * @return unique PID in case of success.
 * @return -1 in case of errors.
 */
pid_t pm_getupid(void);

/**
 * @brief Clone the calling process, creating an exact copy.
 * 
 * @return PID of the child process to parent process.
 * @return 0 - to the new process.
 * @return -1 - in case of errors.
 */
pid_t fork(void);

#endif /* _NOS_KERNEL_PM_H_ */