<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **OPERATING NOTES** 🔥🐦‍🔥

<br>

## 🐦‍🔥 WHAT IS AN OPERATING SYSTEM ?

An Operating System (OS) is system software that manages computer hardware and software resources and provides common services for computer programs. It acts as an intermediary between users and the computer hardware.

<br>

## 🐦‍🔥 GETTING STARTED [/>](https://www.tutorialspoint.com/operating_system/index.htm)

### 🔥 Prerequisites

- Basic computer architecture knowledge
- Understanding of hardware components
- Programming fundamentals
- Data structures and algorithms

### 🔥 OS Evolution Timeline

- 1940s-1950s: No OS (Bare Machine)
- 1950s-1960s: Batch Processing Systems
- 1960s-1970s: Multiprogramming Systems
- 1970s-1980s: Time-Sharing Systems
- 1980s-1990s: Personal Computer OS
- 1990s-2000s: Network & Distributed OS
- 2000s-Present: Mobile & Cloud OS

### 🔥 Types of Operating System

- Batch Operating System
- Time-Sharing/Multitasking OS
- Distributed OS
- Network OS
- Real-Time OS
- Mobile OS
- Embedded OS

<br>

## 🐦‍🔥 Kernel Vs Operating System

| **Kernel**                           | **Operating System**                   |
| ------------------------------------ | -------------------------------------- |
| Core part of the system              | Complete software package              |
| Manages hardware resources           | Provides a usable environment          |
| Direct access                        | Access via kernel                      |
| No direct interaction                | Yes (GUI / CLI)                        |
| Runs in **kernel mode**              | Mostly **user mode**                   |
| CPU, memory, process, device control | Kernel + shell + utilities + libraries |
| Can run alone but useless to users   | Needs kernel for running               |

<br>

## 🐦‍🔥 SYSTEM CALL IN C

### 🔥 Duel mode Operation

To protect the computer from crashing or malicious software, the CPU operates in two modes:

- `User Mode`: Where applications run, have restricted access to hardware.
- `Kernel Mode`: Where the OS resides, has full, unrestricted access to the hardware.

⚡We need this because: Imagine if a buggy Python script could accidentally "delete" your RAM or shut down your cooling fan. By forcing programs to stay in User Mode, the OS stays in control.

### 🔥 System Call

A System Call is the programmatic way a program requests a service from the Kernel. It is the bridge between User Mode and Kernel Mode.

- System calls provide an interface between a process and the operating system.
- For example: `fork()`, `getpid()`, `write()`, `read()` are wrapper functions (APIs) that use system calls internally.

_A system call is the programmatic gateway and security boundary that allows a user-level application to request protected services from the operating system kernel._

```c
// Using libc wrapper
#include <unistd.h>
write(1, "Hello", 5);  // makes system call to print on stdout

// Direct system call in Linux x86
#include <sys/syscall.h>
syscall(SYS_write, 1, "Hello", 5);
```

### 🔥 Sys call rules

- System calls are identified by numbers
- Parameters are passed in registers
- Return value is in EAX register
- Must preserve registers according to calling convention
- Error codes are returned as negative values

<br>

## 🐦‍🔥 PROCESS MANAGEMENT

- A process is a program in execution.
- Each process has its own address space, program counter, and system resources.
- The OS manages processes through Process Control Blocks (PCB).

### 🔥 Process Control Block

When we run a C program, the OS doesn't just "run" it. It keeps a detailed "diary" of everything that process is doing. This diary is called the Process Control Block (PCB). It is a data Structure (a massive struct in C)

⚡ Information associated with each Process

- `Process ID (PID)`: A unique integer (like your Roll Number).
- `Process state`: Is it running? Waiting? Sleeping?
- `Program counter`: The address of the next C instruction to execute.
- `CPU registers`: A "snapshot" of the math being done when process paused.
- `CPU scheduling information`
- `Memory-management information`
- `Accounting information`
- `I/O status information`

```C
// Process Control Block (PCB) structure
typedef struct pcb {
    int pid;                // Process ID
    int state;              // Process state
    void* stack_pointer;    // Stack pointer
    void* base_pointer;     // Base pointer
    uint32_t* page_dir;     // Page directory
    struct pcb* next;       // Next PCB in queue
    int priority;           // Process priority
    int time_slice;         // Remaining time slice
    // Registers context
    uint32_t eax, ebx, ecx, edx;
    uint32_t esi, edi, ebp;
    uint32_t eip, eflags;
    // Memory information
    uint32_t heap_start;
    uint32_t heap_end;
} pcb_t;
```

### 🔥 Process Life Cycle

- `NEW` : "Process is being created",
- `READY` : "Process is waiting for CPU",
- `RUNNING` : "Instructions are being executed",
- `WAITING` : "Process is waiting for some event",
- `TERMINATED` : "Process has finished execution"

```txt
               +-------interrupt-------+
      admit    ↓                       ↑     exit
[ NEW ] -→ [ READY ] --schedule-→ [ RUNNING ] -→ [ TERMINATED ]
               ↑                       ↓
               +------[ WAITING ]------+
             😃I/O                  I/O 🙏
```

### 🔥 Context Switching

The mechanism that allows the OS to switch the CPU from one process to another. It is the "magic" that makes multitasking possible.

```txt
   Process 0                           Process 1
      +                                    -
      +                                    -
      +------→ Save state to PCB 0         -
      -               |                    -
      -      Reload state from PCB 1------→+
      -                                    +
      -                                    +
      -        Save state to PCB 1 ←-------+
      -               |                    -
      +←-----Reload state from PCB 0       -
      +                                    -
      +                                    -
```

⚡ `Zombie Process` : A zombie process is a process that has finished execution but still has an entry in the process table.
⚡ `Orphan Process` : An orphan process is a process whose parent process has terminated, but the child is still running.

### 🔥 Process Scheduling

The CPU Scheduler is the part of the OS that decides which process in the READY state gets to use the CPU (RUNNING state) and for how long.

⚡ Key terms

- `Arrival Time (AT)`: Time at which the process enters the ready queue.
- `Burst Time (BT)`: Time required by the process for CPU execution.
- `Turnaround Time (TAT)`: Completion Time - Arrival Time.
- `Waiting Time (WT)`: Turnaround Time - Burst Time.

⚡ Scheduling Criteria

- `CPU Utilization` : Keep the CPU as busy as possible.
- `Throughput` : Number of processes completed per unit of time.
- `Turnaround Time` : Time from submission to completion.
- `Waiting Time` : Total time spent in the READY queue.

⚡ Types of Scheduling

- `NON-PREEMPTIVE` : Once a process starts, it holds the CPU until it finishes or requests I/O (e.g., FCFS).
- `PREEMPTIVE` : The OS can interrupt a running process to give the CPU to another one (e.g., Round Robin).

### 🔥 Process Creation (`fork()` implementation concept)

```C
// Simplified fork-like function
pid_t os_fork() {
    pcb_t* parent = current_process;
    pcb_t* child = kmalloc(sizeof(pcb_t));

    // Copy parent PCB
    memcpy(child, parent, sizeof(pcb_t));

    // Assign new PID
    child->pid = next_pid++;

    // Create new address space
    child->page_dir = clone_page_directory(parent->page_dir);

    // Allocate new kernel stack
    child->kernel_stack = allocate_stack();

    // Set up return value
    child->eax = 0;  // Child returns 0

    // Add to process table
    add_to_ready_queue(child);

    return child->pid;  // Parent returns child's PID
}
```

</div>
</div>
