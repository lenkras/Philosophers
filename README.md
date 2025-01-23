# Dining Philosophers Problem
## Overview
This project implements a solution to the classic Dining Philosophers Problem threads. The goal of the program is to simulate the life of a group of philosophers sitting at a round table, where they spend their time thinking and eating. The challenge lies in preventing deadlocks and ensuring that philosophers can eat without contention for resources (forks).
## Problem Description
- Philosophers: Each philosopher alternates between thinking, eating, and sleeping.
- Forks: Each philosopher needs two forks (left and right) to eat.
-  Fork Management: Mutexes are used to ensure that no two philosophers use the same fork at the same time.
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
