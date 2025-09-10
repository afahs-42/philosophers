# 🍽️ Philosophers (Dining Philosophers Problem)

A multithreaded simulation of the classic dining philosophers problem using C and POSIX threads (pthreads).

## 📋 Table of Contents
- [About](#about)
- [The Problem](#the-problem)
- [Installation](#installation)
- [Usage](#usage)
- [Parameters](#parameters)
- [Examples](#examples)
- [Key Concepts](#key-concepts)
- [Implementation Highlights](#implementation-highlights)
- [Project Structure](#project-structure)

## 🎯 About

This project implements a solution to the famous **Dining Philosophers Problem**, a classic synchronization problem in computer science that illustrates the challenges of resource allocation and deadlock prevention in concurrent programming.

The simulation creates a scenario where philosophers sit around a circular table, alternating between eating, sleeping, and thinking. Each philosopher needs two forks to eat, but there are only as many forks as philosophers, creating potential conflicts and synchronization challenges.

## 🤔 The Problem

**The Setup:**
- N philosophers sit around a circular table
- There are N forks placed between them (one between each pair of adjacent philosophers)
- Each philosopher needs exactly 2 forks to eat
- Philosophers alternate between three states: **eating**, **sleeping**, and **thinking**

**The Challenge:**
- **Starvation**: Ensure no philosopher starves to death
- **Deadlock**: Prevent situations where all philosophers wait indefinitely
- **Race Conditions**: Handle concurrent access to shared resources (forks)
- **Fair Resource Allocation**: Give each philosopher equal opportunity to eat

## 🚀 Installation

```bash
# Clone the repository
git clone [your-repo-url]
cd philosophers

# Compile the project
make

# Clean object files (optional)
make clean

# Full clean including executable
make fclean

# Recompile everything
make re

# Check code style with norminette (if available)
make norm
```

## 💻 Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters

| Parameter | Description | Range | Required |
|-----------|-------------|-------|----------|
| `number_of_philosophers` | Number of philosophers and forks | 1-200 | Yes |
| `time_to_die` | Time (ms) before a philosopher dies from starvation | > 0 | Yes |
| `time_to_eat` | Time (ms) a philosopher spends eating | > 0 | Yes |
| `time_to_sleep` | Time (ms) a philosopher spends sleeping | > 0 | Yes |
| `number_of_times_each_philosopher_must_eat` | Simulation stops when all philosophers have eaten this many times | > 0 | No |

## 📖 Examples

### Basic Usage
```bash
# 5 philosophers, die in 800ms, eat for 200ms, sleep for 200ms
./philo 5 800 200 200

# Same as above, but stop after each philosopher eats 3 times
./philo 5 800 200 200 3

# Single philosopher (special case)
./philo 1 400 200 200
```

### Expected Output Format
```
[timestamp] [philosopher_id] [action]
```

Example output:
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
400 1 has taken a fork
...
```

### Possible Actions
- `has taken a fork` - Philosopher picks up a fork
- `is eating` - Philosopher is eating (has both forks)
- `is sleeping` - Philosopher is sleeping
- `is thinking` - Philosopher is thinking
- `died` - Philosopher died from starvation

## 🔑 Key Concepts

### Synchronization Mechanisms Used
- **Mutexes**: Protect shared resources (forks, status printing, death flag)
- **Thread-safe operations**: All shared data access is protected
- **Atomic operations**: Critical sections are properly managed

### Deadlock Prevention Strategy
- **Ordered resource allocation**: Forks are always acquired in a consistent order (lower-numbered fork first)
- **Asymmetric timing**: Even-numbered philosophers start with a slight delay
- **Resource limitation**: Only allow N-1 philosophers to attempt eating simultaneously (for odd numbers)

### Key Data Structures
- **Philosopher structure**: Contains ID, meal count, timing, and fork assignments
- **Global data structure**: Shared parameters and synchronization primitives
- **Fork mutexes**: One mutex per fork to control access

## ⭐ Implementation Highlights

### Thread Safety
- All shared data access is protected by appropriate mutexes
- Death detection is atomic and thread-safe
- Status printing is synchronized to prevent garbled output

### Performance Optimizations
- Precise timing using custom `precise_usleep()` function
- Efficient busy-waiting for short delays
- Minimal mutex contention through careful lock ordering

### Edge Case Handling
- **Single philosopher**: Special handling since they can't eat (only one fork)
- **Odd number of philosophers**: Additional synchronization to prevent starvation
- **High philosopher counts**: Tested up to 200 philosophers

### Memory Management
- Proper cleanup of all allocated resources
- Mutex destruction in correct order
- No memory leaks under normal and error conditions

## 📁 Project Structure

```
philo/
├── inc/
│   └── philo.h              # Header file with structures and function prototypes
├── src/
│   ├── main.c               # Entry point and program flow control
│   ├── parsing.c            # Command line argument parsing and validation
│   ├── init.c               # Data structure and mutex initialization
│   ├── simulation.c         # Core philosopher behavior and threading logic
│   ├── monitor.c            # Death detection and completion monitoring
│   ├── utils.c              # Utility functions (timing, printing, etc.)
│   └── cleanup.c            # Memory and resource cleanup
├── Makefile                 # Build configuration
└── README.md               # This file
```

## 🛠️ Technical Details

### Threading Model
- One thread per philosopher
- One monitor thread for death/completion detection
- Main thread manages creation and joining of all threads

### Mutex Strategy
- Fork mutexes: One per fork (N mutexes for N philosophers)
- Print mutex: Ensures atomic output
- Dead mutex: Protects death and completion flags
- Meal mutex: Protects meal counting and last meal time

### Timing Precision
- Millisecond precision using `gettimeofday()`
- Custom sleep function for precise timing
- Hybrid approach: `usleep()` for long waits, busy-wait for precision

---

**Note**: This implementation successfully handles all edge cases and provides a deadlock-free, starvation-free solution to the dining philosophers problem while maintaining optimal performance and resource usage.