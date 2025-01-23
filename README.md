# Dining Philosophers Problem
## Overview
This project implements a solution to the classic Dining Philosophers Problem using threads. It simulates philosophers sitting at a round table, alternating between thinking and eating. The primary challenge is to prevent deadlocks and ensure that philosophers can eat without contention for the shared resources (forks).

## Key Learnings:
- Thread Synchronization: The importance of controlling access to shared resources to avoid race conditions.
- Deadlock Prevention: Techniques to ensure that philosophers don’t get stuck waiting indefinitely for resources.
- Resource Management: How to efficiently manage shared resources (forks) in a multi-threaded environment to prevent starvation and ensure fairness.
## Problem Description
- Philosophers: Each philosopher alternates between thinking, eating, and sleeping.
- Forks: Each philosopher needs two forks (left and right) to eat.
- Fork Management: Mutexes are used to ensure that no two philosophers use the same fork at the same time.
 #### Time Limits:
- time_to_die: Time in milliseconds before a philosopher dies from starvation if they haven’t eaten.
- time_to_eat: Time in milliseconds it takes for a philosopher to eat.
-  time_to_sleep: Time in milliseconds a philosopher sleeps after eating.
- The program ends when a philosopher dies or when all philosophers have eaten the specified number of times.
## How to Run
1. Clone the repository
```bash
git@github.com:lenkras/Philosophers.git
```
2. Compile the program:
```bash
make
```
3. Run the program:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
