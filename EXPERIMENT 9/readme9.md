Process Creation, fork(), and Child
Synchronization

A step-by-step lecture guide to understanding PIDs, process cloning, return values,
and waiting for child termination.

OPERATING SYSTEMS CONCEPTS IN C

STEP 1 • FUNDAMENTALS

What is a Process and PID?

Every running program in an Operating System is called a
process. The OS assigns each process a unique numerical
identifier: the PID.

#

Like a Student Roll Number

Uniquely identifies execution context within kernel process tables.

()

getpid() & getppid()

Standard POSIX calls to query own PID or parent process PID.

pid_demo.c

#include <stdio.h>

#include <unistd.h>

int main() {

printf("Current PID: %d\n", getpid());

return 0;

}

TERMINAL OUTPUT

$ gcc pid_demo.c -o pid_demo

./pid_demo

Current PID: 4092

STEP 2 • CONCEPTUAL ANALOGY

How fork() Works: The Photocopy Analogy

Instant Exact Clone

Like running a notebook through a photocopy
machine, creating an identical copy of code and
memory.

Called Once, Returns Twice

A single function call produces two separate
execution threads continuing from the exact
same instruction.

Different Return Badges

The only immediate difference between parent
and child is what value fork() places into their
variables.

KEY INSIGHT

Both processes start with identical code
segment, stack, heap, and register states at
time of fork().

KEY INSIGHT

Execution continues concurrently right after
the fork() call, rather than re-starting main().

KEY INSIGHT

Parent gets Child PID (>0) to monitor/wait for
it; Child gets 0 to recognize it is the new
process.

CORE CONCEPT

Why Does Child Receive 0 in Variable `p`?

CHILD PROCESS

p = 0

0 is a Role Badge, NOT the Real PID

The child already has its own unique PID (e.g. 5042). It receives 0
purely as a signal to acknowledge:

"I am the newly spawned child."

Child can always check its PID via getpid() and parent via getppid().

PARENT PROCESS

p = Child_PID (e.g. 5042)

Parent Needs the Child's Handle

A parent process can spawn multiple children.

There is no simple API like getchildpid(), so fork() explicitly gives the
child's exact PID to the parent.

Essential for monitoring, signaling, and calling wait().

Stack

Heap

Registers

Stack Copy

Heap Copy

Registers

ARCHITECTURE

Separate Memory Spaces After fork()

Parent Process Running (Original PID: 4000) • pid_t p = fork();

Parent Memory Space

Own copies of stack, heap, and registers.

Variable p = 4001

Condition (p == 0) is FALSE

Child Memory Space

Independent duplicate of stack, heap, and registers.

Variable p = 0

Condition (p == 0) is TRUE

STEP 3 • PROCESS SYNCHRONIZATION

How to Use wait() in C

Synchronizing parent and child processes to prevent race conditions, reap exit status, and ensure clean lifecycle termination.

WHY wait() IS NEEDED

Race Conditions: OS scheduler order is
nondeterministic without synchronization.

Scrambled Output: Shell prompt returns before
child finishes printing to terminal.

Orphan Processes: Parent exits first, abandoning
child to be adopted by init/systemd (PID 1).

Zombie Processes: Terminated child lingers dead
in kernel table until parent collects status.

wait_pattern.c — Basic Implementation

#include <sys/wait.h> // Defines wait()

#include <unistd.h> // Defines fork()

pid_t p = fork();

if (p == 0) { // 1. CHILD PROCESS

printf("Child working...\n");

exit(0); // 2. Normal exit status 0

} else { // 3. PARENT PROCESS

pid_t child_pid = wait(NULL);

printf("Child %d reaped successfully!\n", child_pid);

KEY IMPLEMENTATION TAKEAWAY: wait(NULL)

Passing NULL tells the kernel to block and reap the child process without
storing detailed exit status information in an integer pointer.

STEP 3 • PROCESS SYNCHRONIZATION

How to Use wait() in C

Synchronizing parent and child processes to prevent race conditions, reap exit status, and ensure clean lifecycle termination.

HOW wait() WORKS

Required Headers: #include <sys/wait.h>

Blocks the Parent: Suspends parent execution until
any child process terminates.

Reaps Process State: Collects child exit status and
deallocates it from kernel process table.

Returns Child PID: Returns PID of terminated child,
or -1 if no un-waited children exist.

wait_pattern.c — Basic Implementation

#include <sys/wait.h> // Defines wait()

#include <unistd.h> // Defines fork()

pid_t p = fork();

if (p == 0) {

printf("Child working...\n");

exit(0);

} else {

pid_t child_pid = wait(NULL);

printf("Child %d reaped successfully!\n", child_pid);

KEY IMPLEMENTATION TAKEAWAY: wait(NULL)

Passing NULL tells the kernel to block and reap the child process without
storing detailed exit status information in an integer pointer.

main.c — Complete C Implementation

IMPLEMENTATION

Complete Classroom Program in C

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/wait.h>

int main() {

pid_t p = fork();

if (p == 0) {

printf("Child Running with PID: %d\n", getpid());

sleep(2); // Simulate work

printf("Child Exiting...\n");

exit(0);

}

else {

printf("Parent Waiting for child to terminate...\n");

pid_t terminated_pid = wait(NULL);

printf("Parent Terminated Child PID: %d\n", terminated_pid);

}

return 0;

}

REFERENCE

System Calls Quick Reference

fork()

HEADER FILE

<unistd.h>

PRIMARY PURPOSE

Clones calling process

RETURN VALUE

0 to child, PID to parent

getpid()

HEADER FILE

<unistd.h>

PRIMARY PURPOSE

Gets own process ID

RETURN VALUE

Current process PID

getppid()

HEADER FILE

<unistd.h>

PRIMARY PURPOSE

Gets parent process ID

RETURN VALUE

Parent process PID

wait()

HEADER FILE

<sys/wait.h>

PRIMARY PURPOSE

Waits for child exit

RETURN VALUE
