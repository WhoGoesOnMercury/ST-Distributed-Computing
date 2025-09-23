# Multithreaded Prime Search

This project was made for one of my undergraduate problem sets. It is my first
try at using threads in C (although I already have tried in C++). C is static
and so the whole structure for a program with multiple threads must be carefully
planned to avoid leaks and such.

The config file contains four numbers:
1. Maximum integer value for searching (N)
2. Thread count (t)
3. Print mode
    i.  0 is for immediate printing
    ii. 1 is for printing only after all threads are done
4. Division mode
    i.  0 = divides the maximum integer equally among all threads
    ii. 1 = similar to mode 0 except each number now spawns additional `t` threads,
            each designated a range to test if a num `n` is prime.

Both the printing and division method can affect the runtime of the program. As
always, printing immediately in a running loop will significantly bloat the runtime
of a C program. 

The implementation of the division mode here also affects the runtime. For the
second division mode, it is more optimal for significantly large numbers. 