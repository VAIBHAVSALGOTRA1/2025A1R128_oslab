LINUX LAB • EXPERIMENT 8

Observing Process Memory Maps Using pmap

Inspecting virtual address spaces, resident RAM (RSS), dirty page modifications, and permission modes of
CPU-bound and I/O-bound C processes.

Virtual Address Space • pmap -x 6 Columns • Dirty <= RSS <= Kbytes • Memory Protection • Shared Libraries

PROCEDURE & TARGETS

Process Identification & pmap Execution

Launch & PID Resolution

Running workloads in background and capturing process identifiers.

# Step 1: Run processes in background

$ ./io_bound &

$ ./cpu_bound &

# Step 2: Query active PIDs

$ pgrep -af 'io_bound|cpu_bound'

7714 ./cpu_bound

7715 ./io_bound

# Step 3: Run detailed pmap

$ pmap -x 7714

Real-World Output Structure

Contiguous virtual memory mappings formatted across 6 columns.

Address Kbytes RSS Dirty Mode Mapping

00005ddafa875000 4 4 0 r---- cpu_bound

00005ddafa876000 4 4 0 r-x-- cpu_bound

00005ddafa877000 4 4 4 rw--- cpu_bound

000076ec1b228000 1632 1056 0 r-x-- libc.so.6

00007ffd5e2a1000 132 12 12 rw--- [ stack ]

total kB 2772 1744 96

OUTPUT ANATOMY

Deconstructing the Six Columns of pmap -x

Column

Kernel Definition

Analogy / Intuition

Diagnostic Significance

Address

Virtual start offset (hex)

The house postal number

Private virtual address space boundary.

Kbytes

Virtual size reserved (VSZ)

The size of the plot

Total capacity allocated by OS for this region.

RSS

Resident Set Size in RAM

The house footprint built

Actual physical RAM pages loaded right now.

Dirty

Modified resident memory

The renovated rooms

Pages altered by CPU that differ from disk backing.

Mode

Protection permission bits

Zoning and usage rules

Enforces read, write, and execute restrictions.

Mapping

Backing file or identity

The owner on title deed

Points to executable, libc.so.6, or [stack].

CORE INVARIANT

The Golden Rule: Dirty <= RSS <= Kbytes

Hierarchical Memory Inclusion

Why modified pages are always resident in physical RAM.

# Virtual Inclusion Relationship:

+-----------------------------------------+

| Kbytes (Total Address Reservation) |

| +-----------------------------------+ |

| | RSS (Loaded into Physical RAM) | |

| | +-----------------------------+ | |

| | | Dirty (Modified Pages) | | |

| | +-----------------------------+ | |

| +-----------------------------------+ |

+-----------------------------------------+

# Invariant: Dirty <= RSS <= Kbytes

Permission Mode Protection

Hardware-enforced MMU access flags.

r-x-- (Read + Execute): Executable program code (.text). Cannot be
modified, preventing self-modifying code.

rw--- (Read + Write): Stack and data regions. Cannot be executed; hardware
NX bit prevents exploit execution.

r---- (Read-Only): Read-only constants (.rodata) and ELF headers.
Overwrites trigger Segmentation Fault.

EMPIRICAL ANALYSIS

Memory Footprint: cpu_bound vs. io_bound

Memory
Characteristic

cpu_bound Process

io_bound Process

Underlying Architecture

Total Virtual Space

~2,500 – 2,800 KB

~2,500 – 2,800 KB

Both link identical standard C runtime libraries (glibc).

Code (.text) RSS

4 KB (r-x--)

4 KB (r-x--)

Tiny compiled binaries occupy a single 4096-byte page frame.

Stack Allocation

132 KB reserved (12 KB RSS)

132 KB reserved (12 KB RSS)

Dynamic stack growth; only referenced stack frames consume RAM.

Shared Libraries

libc.so.6, ld-linux.so

libc.so.6, ld-linux.so

Shared code pages are mapped once in physical RAM and shared.

Dynamic Heap

0 KB explicit malloc()

0 KB explicit malloc()

Neither program performs dynamic heap allocations.
