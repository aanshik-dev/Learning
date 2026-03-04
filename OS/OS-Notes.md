<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **OPERATING NOTES** 🔥🐦‍🔥

⚡ BY - THE AANSHIK-DEV
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

#### ⚡ READ and WRITE

```c
ssize_t read(int fd, void *buffer, size_t count);
ssize_t write(int fd, const void *buffer, size_t count);
```

- fd → file descriptor
- buffer → memory to read into / write from
- count → number of bytes

| FD  | Meaning |
| --- | ------- |
| 0   | stdin   |
| 1   | stdout  |
| 2   | stderr  |

#### ⚡ OPEN Syscall

```c
// Signature
int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);

int fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0655);
```

| Flags        | Meaning                         |
| ------------ | ------------------------------- |
| `O_CREAT`    | Create file if it doesn’t exist |
| `O_TRUNC`    | Clear file if it exists         |
| `O_APPEND`   | Always write at end             |
| `O_EXCL`     | Fail if file already exists     |
| `O_NONBLOCK` | Non-blocking I/O                |

- Flags are separated by `|` (bitwise OR), to get a combination of flags.
- 0655 is the mode to give the permissions to the file, and used when O_CREAT is used.

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

### 🔥 Process Creation (`fork()` implementation)

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
      -                                    +      - Waiting
      -                                    +      + Runnning
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

<br>

## 🐦‍🔥 PROCESS CREATION

In Unix-like systems, process creation involves two main system calls: `fork()` and `exec()`.

### 🔥 1. The `fork()` System Call

```c
#include <unistd.h>  // fork()
#include <sys/types.h> // contains type (pid_t)
pid_t pid = fork();  // returns 0 of pid_t type
```

Creates a new copy process by duplicating the calling (Parent) process.
⚡ COPIED: Code segment, Data segment, Heap, Stack, Registers, Program counter
⚡ SHARED: Open file descriptors, Environment variables,

- Child <- `0`
- Parent <- `Child's Process ID`
- Failed <- `negative value`

### 🔥 2. The `exec()` Family

```c
#include <unistd.h>  // exec()
```

- Once a child is born via `fork()`, it is a clone. To make it run a different program (like ls or grep), we use `exec()` family.
- This overwrites the current process image with a new one.
- mostly the `execvp` or the `execlp` is used

⚡ RETAINED: Open file descriptors, Environment variables, pid, ppid
⚡ DELETED: Code segment, Data segment, Heap, Stack, Registers, Program counter

| Function   | Meaning                            |
| ---------- | ---------------------------------- |
| `execl()`  | arguments as list                  |
| `execv()`  | arguments as array                 |
| `execlp()` | search in PATH                     |
| `execvp()` | array + PATH                       |
| `execle()` | list + environment                 |
| `execve()` | array + environment (core syscall) |

```c
char *command = "ls";              // Used by KERNEL to find the file
char *args[] = {"ls", "-l", NULL}; // Used by the PROGRAM as argv[]

execl("/bin/ls", "ls", "-l", NULL);  // required full path
execv("/bin/ls", args);  // required full path & args array
execlp(command, "ls", "-l", NULL); // ( path is searched
execvp(command, args);             // and args array is used )
```

> 📝 NOTE : We can pass any program in `ececvp()` like `execvp("./myProc", args)`

### 🔥 3. Process Synchronization: `wait()`

- A parent process often needs to wait for its child to finish before continuing. This prevents "Zombies"
- We use wait() to wait for a child process to finish.

```c
#include <sys/wait.h>
```

### 🔥 Example demonstrating `fork()`, `exec()`, `wait()`

```c
#include <stdio.h>
#include <unistd.h>   // For fork()
#include <sys/wait.h> // For wait()
#include <stdlib.h>   // For exit()

int main() {
    pid_t pid;
    printf("Starting main process (PID: %d)\n", getpid());
    pid = fork(); // The "split" happens here

    if (pid < 0) return 1;  // fork failed
    else if (pid == 0) {
      // -------- CHILD PROCESS -----------
      printf("Child: I am born! (PID: %d)\n", getpid());
      printf("Child: My parent is (PPID: %d)\n", getppid());
      execl("/bin/ls", "ls", "-l", NULL);
      printf("This will run if exec failed\n");
      exit(0); // Tell OS, I finished
    }
    else {
      // -------- PARENT PROCESS -----------
        printf("Parent: Created child with PID %d\n", pid);
        wait(NULL); // Parent waits for child
        printf("Parent: Child finished. Exiting\n");
    }

    return 0;
}
```

<br>

## 🐦‍🔥 INTER-PROCESS COMMUNICATION (IPC)

Processes can not communicate directly. We need a way to transfer data between processes.

### 🔥 Shared Memory

- Two processes share a specific region of RAM. It is extremely fast but dangerous.
- Two processes read and write in the same variables
- Can be done with finite or variable buffer

### 🔥 Message Passing

- Processes send packets of data to each other via the Kernel. It is slower but safer.

#### ⚡ THE PIPE - A MESSAGE PASSING CLASSIC

A Pipe is a one-way communication channel managed by the Kernel. In C, it is treated like a file with two ends.

We use the `pipe()` system call, which gives us an array of two integers (File Descriptors).

- `fd[0]`: Read end.
- `fd[1]`: Write end.

> 📝 NOTE : We create the pipe before forking, because it is inherited by the child process

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    char buffer[20];
    int fd[2]; // Array of 2 integers
    pid_t pid;

    if (pipe(fd) == -1) return 1; // Pipe failed

    pid = fork();  // Child Created after pipe

    if (pid > 0) {
        // --- PARENT (The Sender) ---
        close(fd[0]); // Read end not needed
        char msg[] = "Hello Child!";
        write(fd[1], msg, strlen(msg) + 1); // Send data
        close(fd[1]); // Finished writing
    }
    else {
        // --- CHILD (The Receiver) ---
        close(fd[1]); // Write end not needed
        read(fd[0], buffer, sizeof(buffer)); // Receive data
        printf("Child received: %s\n", buffer);
        close(fd[0]); // Finished reading
    }

    return 0;
}
```

### 🔥 The `dup()` and `dup2()` System Calls

- `dup()` creates a copy of a file descriptor with next abailable number
- `dup2()` allows us to copy a file descriptor to a different number, even already in use
- We can use the `dup2()` to take input & give output data using files istead of using STDIN and STDOUT
- `dup2(old_fd, new_fd);` this duplicates the old_fd to new_fd, auto closes the new_fd, meaning we can access file via new_fd

⚡ Demonstrating PIPE duplication

```bash
> wc -l # counts the lines form input
> wc -l file.txt # counts the lines form file
```

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pipe(fd);
    pid_t pid = fork();

    if (pid == 0) {
        // --- CHILD (Receiver) ---
        //'wc' read from the pipe, not keyboard.
        dup2(fd[0], STDIN_FILENO);
        // fd[0] -> PIPE(READ)
        // STDIN -> PIPE(READ)
        close(fd[0]);  // Closing original pipe
        close(fd[1]);  // Close Write end

        char *args[] = {"wc", "-l", NULL};
        execvp(args[0], args);
    }
    else {
        // --- PARENT (Sender) ---
        // 'ls' write to the pipe, NOT the screen.
        dup2(fd[1], STDOUT_FILENO);
        // fd[1] -> PIPE(WRITE)
        // STDOUT -> PIPE(WRITE)
        close(fd[0]);  // Close Read end
        close(fd[1]);  // Closing original pipe

        char *args[] = {"ls", NULL};
        execvp(args[0], args);
    }
    return 0;
}
```

<br>

## 🐦‍🔥 THREADS

A thread is a lightweight execution unit inside a process that shares memory and resources with other threads of the same process.

⚡ SHARED: Code segment, Data segment, and OS Resources
⚡ PRIVATE: Stack, Registers, Program counter, Thread ID

### 🔥 Why use Threads instead of Fork?

- `Responsiveness` : If one thread is waiting, another thread can keep running.
- `Resource Sharing` : They share the same memory (no pipes).
- `Economy` : Creating a thread is much faster than fork().

### 🔥 Process vs. Thread

| Aspect         | Process                    | Thread                           |
| -------------- | -------------------------- | -------------------------------- |
| Definition     | Independent program        | Execution inside process         |
| Memory         | Separate address space     | Shared address space             |
| Communication  | IPC (pipes, shm, sockets)  | Shared variables                 |
| Creation cost  | High (`fork`)              | Low (`pthread_create`)           |
| Context switch | Expensive                  | Cheaper                          |
| Isolation      | Strong                     | Weak                             |
| Failure impact | One process crash ≠ others | One thread crash = whole process |
| Stack          | One per process            | One per thread                   |
| Scheduling     | Scheduled by OS            | Scheduled by OS                  |

### 🔥 Demonstration: POSIX threads (pthreads)

```c
#include <pthread.h>
```

> 📝 NOTE :
>
> - In C, we use the Pthreads library.
> - When compiling, you must add the -lpthread flag
>   (example - `gcc main.c -lpthread`).

- `pthread_t` : The variable that holds the Thread ID.
- `pthread_create()` : The "Fork" equivalent for threads.
- `pthread_join()` : The "Wait" equivalent for threads.

```c
int pthread_create(
    pthread_t *thread, // Thread ID
    const pthread_attr_t *attr, // Attributes, mostly NULL
    void *(*start_routine)(void *), // The function to run
    void *arg // Arguments
);
```

- `start_routine` should return `void *` and take only one `void *` argument.

```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// This is the function the thread will run
void* my_task(void* arg) {
    char* name = (char*)arg;
    for(int i = 0; i < 3; i++) {
        printf("%s is working...\n", name);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Create two threads running the same task
    pthread_create(&thread1, NULL, my_task, "Thread A");
    pthread_create(&thread2, NULL, my_task, "Thread B");

    // Wait for them to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("All threads finished!\n");
    return 0;
}
```

<br>

## 🐦‍🔥 SIGNALS: THE ASYNCHRONOUS NOTIFIER

A signal is an asynchronous notification sent to a process to notify it of an event (interrupt, error, timeout, termination, etc.).

- Signals are asynchronous, can arrive at any time
- When Signals arrive, process stop execution and runs Signal handler

### 🔥 Types of Signals

⚡1. TERMINATION & CONTROL SIGNALS

| Signal    | Name      | Meaning                       |
| --------- | --------- | ----------------------------- |
| `SIGINT`  | Interrupt | Ctrl + C                      |
| `SIGTERM` | Terminate | Polite kill                   |
| `SIGKILL` | Kill      | Force kill (cannot be caught) |
| `SIGQUIT` | Quit      | Ctrl + \ (core dump)          |
| `SIGHUP`  | Hangup    | Terminal closed               |

⚡ 2. TIMING AND CHILD SIGNAL

| Signal    | Name  | Meaning              |
| --------- | ----- | -------------------- |
| `SIGALRM` | Alarm | Timer expired        |
| `SIGCHLD` | Child | Child process exited |

⚡ 3. ERROR SIGNALS

| Signal    | Name                     | Meaning               |
| --------- | ------------------------ | --------------------- |
| `SIGSEGV` | Segmentation fault       | Invalid memory access |
| `SIGFPE`  | Floating-point exception | Divide by zero        |
| `SIGILL`  | Illegal instruction      | Bad CPU instruction   |
| `SIGABRT` | Abort                    | `abort()` called      |

⚡ 4. JOB CONTROL SIGNALS
| Signal | Name | Meaning |
| --------- | ------------- | ---------------------- |
| `SIGSTOP` | Stop | Pause |
| `SIGTSTP` | Terminal stop | Ctrl + Z |
| `SIGCONT` | Continue | Resume stopped process |

### 🔥 Demonstration (SIGKILL)

```c
#include <signal.h>
```

```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void alarm_handler(int sig) {  // Signal handler
  write(1, "Killing itself\n", 15);
  kill(getpid(), SIGKILL);
}

int main() {
  printf("My PID is: %d\n", getpid());
  signal(SIGALRM, alarm_handler); // Signal handler
  alarm(5);  // 5 seconds timer
  pause(); // Freeze the process

  return 0;
}
```

<br>

## 🐦‍🔥 JUMP: Breaking the Flow

In C, execution happens from top to bottom. However, we can use `setjmp(env)` and `longjmp(env, 1)` to break the flow of the program.

- `setjump()` saves the state of the program and return 0 firstly
- `longjump()` is called to jumps back to the saved state
- This time `setjump()` returns the value passed in `longjump()`

```c
#include <setjmp.h>
```

```c
#include <setjmp.h>
#include <stdio.h>

jmp_buf env;

int main() {
    int x = setjmp(env);

    if (x == 0) {
        printf("First time\n");
        longjmp(env, 1);
    } else {
        printf("After jump\n");
    }
}
```

### 🔥 Thread Scheduling

- PCS : Process Contention Scope or process local scheduling

- SCS - System Contention Scope or system global scheduling

</div>
</div>
