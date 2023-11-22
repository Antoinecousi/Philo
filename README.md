
# Philosophers Project

## Overview

The Philosophers project is an implementation of the classic Dining Philosophers problem in computer science. This project aims to explore and solve the challenges of concurrency, thread management, and resource allocation. It serves as a practical demonstration of avoiding common issues such as deadlock, starvation, and race conditions.

## Features

-   **Concurrency Handling**: Utilizes multiple threads or processes to simulate the philosophers.
-   **Resource Management**: Efficiently manages resources (forks) among philosophers to avoid deadlock.
-   **Philosopher States**: Implements different states for each philosopher - thinking, eating, and sleeping.
-   **Time Management**: Controls the timing for eating, sleeping, and thinking to prevent starvation.
-   **Deadlock Prevention**: Implements algorithms to prevent deadlock and ensure fair resource allocation.

## Installation
```
git clone git@github.com:Antoinecousi/Philo.git
cd Philo
make
``` 
    

## Usage

Run the program with the following command:

`./philo [number of philosophers] [time to die] [time to eat] [time to sleep] [number of times each philosopher must eat (optional)]` 

## Problem Description

The Dining Philosophers problem consists of the following scenario: A certain number of philosophers are sitting around a circular table doing one of three things - eating, thinking, or sleeping. While eating, they are not thinking or sleeping; while sleeping, they are not eating or thinking; and, of course, while thinking, they are not eating or sleeping. The philosophers sit at a circular table with a large bowl of spaghetti in the center. A fork is placed between each pair of adjacent philosophers; each philosopher has one fork to their left and one to their right. As spaghetti is difficult to serve and eat with a single fork, it is assumed that a philosopher must eat with two forks, one from their left and one from their right.
