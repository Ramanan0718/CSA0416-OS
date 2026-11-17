# CSA04 Operating Systems Lab — Programs 1 to 40

Each folder `EXPERIMENT N/` contains:

- `program.c` — the C program (compiles with `gcc -pthread program.c`)
- `output.txt` — the actual output captured from running the program
- `screenshot.png` — image of the program code and its output
- `input.txt` — (where the program reads input) the input used for the run

| Exp | Topic | Notes |
|---|---|---|
| 1 | fork, getpid, getppid | Rewritten: the manual's version printed getpid() twice; this one uses fork() so parent and child both show their IDs |
| 2 | File copy with open/read/write | Rewritten with system calls (open, read, write, close) |
| 3 | FCFS CPU scheduling | Rewritten; all processes arrive at time 0 |
| 4 | Smallest-burst-first selection | Selection of shortest job, arrival at time 0 |
| 5 | Non-preemptive priority | Higher number = higher priority (as in the manual's code) |
| 6 | Preemptive priority | Simulated one time unit at a time, Gantt chart shown |
| 7 | Non-preemptive SJF | Uses arrival times |
| 8 | Round Robin | Rewritten (manual used conio.h / getch) |
| 9 | Shared memory IPC | Parent writes, child reads; manual printed memory after detach, fixed |
| 10 | Message queue IPC | Child sends, parent receives |
| 11 | Multithreading | Two threads and join |
| 12 | Dining philosophers | Chopstick mutexes + a semaphore allowing at most N-1 philosophers to eat at once (deadlock avoidance). Runs bounded: 2 meals each |
| 13 | Memory allocation (first/best/worst) | One program, strategy chosen at input |
| 14 | Single-level directory | Menu-driven, in memory (manual used Windows file paths) |
| 15 | Two-level directory | Menu-driven, in memory |
| 16 | Random access file, employee records | fseek/fwrite/fread on fixed-size records |
| 17 | Banker's algorithm | Safety check and request handling; prints safe sequence |
| 18 | Producer-consumer with semaphores | Sleep() from Windows.h replaced with usleep() |
| 19 | Mutex synchronization | Manual's code did not update the counter; now two threads increment under a mutex |
| 20 | Reader-writer with semaphores | Readers' preference |
| 21 | Worst fit | Separate program |
| 22 | Best fit | Separate program |
| 23 | First fit | Separate program |
| 24 | UNIX file system calls | creat, open, write, read, unlink |
| 25 | fcntl, lseek, stat, opendir, readdir | Manual only showed open(); all five calls are used |
| 26 | File management (stdio) | fopen, fprintf, fgets |
| 27 | Simulation of `ls` | Lists a directory with opendir/readdir (hides dotfiles, marks directories with /) |
| 28 | Simulation of `grep` | Reads pattern and file name from input (not argv), prints matching lines with line numbers |
| 29 | Classical producer-consumer (counters) | Menu-driven; the manual's `#pragma omp` line removed |
| 30 | Thread create, join, equal, exit | Manual called join after detach (undefined behaviour); rewritten |
| 31 | FIFO page replacement | 3 frames, reference string 7 0 1 2 0 3 0 4 2 3 0 3 2 → 10 faults |
| 32 | LRU page replacement | Same string → 9 faults |
| 33 | Optimal page replacement | Same string → 7 faults |
| 34 | Sequential file allocation | Simulated in memory; reading record k reads records 1..k first |
| 35 | Indexed file allocation | Index block points to scattered disk blocks |
| 36 | Linked file allocation | First/last block in directory, each block points to the next |
| 37 | FCFS disk scheduling | Queue 98 183 37 122 14 124 65 67, head 53 → 640 total movement |
| 38 | SCAN disk scheduling | Same queue → 331 total movement |
| 39 | C-SCAN disk scheduling | Same queue → 382 total movement (jump back to track 0 counted) |
| 40 | File permissions with chmod | Shows rwx bits for owner/group/others before and after chmod 664 |

Programs were compiled and run on Linux with gcc (`-pthread` where needed). Programs that
wait for user input read it from `input.txt`. Experiments 9 and 10 need empty files
`shmfile` and `msgqfile` in their folder for `ftok()`.
