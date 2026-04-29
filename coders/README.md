*This project has been created as part of the 42 curriculum by mteriier.*

## Description

This project, named Codexion, simulates a coding environment where multiple coders collaborate on a software project. Each coder requires two "dongles" (representing compilation resources or USB keys) to perform compilation tasks. The simulation incorporates concepts of thread synchronization, resource management, and scheduling algorithms to handle concurrency issues such as deadlocks and starvation. Coders have attributes like burnout time, compilation time, debugging time, and refactoring time, and must manage their workflow while competing for shared resources. The project demonstrates real-world concurrency challenges in a multi-threaded environment.

## Instructions

### Compilation
To compile the project, ensure you have the necessary dependencies (GCC compiler with pthread support). Run the following command in the project root directory:

```
make
```

This will generate the executable named `codexion`.

### Execution
The program requires 8 arguments to run:

```
./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```

- `number_of_coders`: The number of coder threads to simulate (integer)
- `time_to_burnout`: Time in milliseconds before a coder burns out (long)
- `time_to_compile`: Time in milliseconds for compilation (long)
- `time_to_debug`: Time in milliseconds for debugging (long)
- `time_to_refactor`: Time in milliseconds for refactoring (long)
- `number_of_compiles_required`: Number of compilations each coder must complete (integer)
- `dongle_cooldown`: Cooldown time in milliseconds after dongle use (long)
- `scheduler`: Scheduling algorithm, either "fifo" or "edf" (string)

Example runs are provided in the Makefile:
- `make codex`: Runs with 4 coders, fifo scheduling
- `make codex2`: Runs with 50 coders, edf scheduling

### Additional Targets
- `make debug`: Compile with thread sanitizer for debugging
- `make valgrind`: Run with helgrind for race condition detection
- `make valgrind2`: Run with drd for deadlock detection
- `make norming`: Check code style with norminette

## Resources

- **Pthreads Documentation**: Official POSIX threads library documentation for understanding thread synchronization primitives
- **Dining Philosophers Problem**: Classic concurrency problem that inspired the dongle resource allocation mechanism
- **Earliest Deadline First (EDF) Scheduling**: Real-time scheduling algorithm implemented for prioritizing urgent tasks
- **42 School Resources**: General C programming and Unix system programming guides

AI was used for:
- Debugging assistance for thread synchronization issues
- Assistance on the README

## Blocking Cases Handled

The project addresses several concurrency issues that could lead to blocking:

1. **Deadlock Prevention**: Implemented by ensuring coders always acquire dongles in a consistent order (lower ID first), preventing circular wait conditions.

2. **Starvation Prevention**: The EDF (Earliest Deadline First) scheduler prioritizes coders with the most urgent deadlines, reducing starvation compared to FIFO. However, FIFO scheduling may still experience starvation for low-priority coders.

3. **Race Conditions**: Protected all shared data structures (queues, simulation state, coder states) with appropriate mutexes to prevent concurrent access issues.

4. **Resource Contention**: Dongle queues manage access to limited resources, with cooldown periods preventing immediate re-acquisition.

5. **Simulation Termination**: Proper synchronization ensures all threads complete their work before the simulation ends, avoiding premature termination or hanging processes.

## Thread Synchronization Mechanisms

The project uses several POSIX thread synchronization primitives:

1. **Mutexes (pthread_mutex_t)**:
   - `write_mutex`: Protects console output to prevent interleaved prints
   - `data_mutex`: Protects shared simulation data (simul_end flag, etc.)
   - `mutex_coder`: Protects individual coder state (compile_count, last_compile_start)
   - `mutex` (per dongle): Protects dongle availability status
   - `mutex_q` (per dongle): Protects the dongle access queue
   - `mutex_avail` (per dongle): Protects availability timestamp

2. **Thread Creation and Management**:
   - `pthread_create`: Creates threads for each coder and monitor
   - `pthread_join`: Waits for thread completion in cleanup

3. **Scheduling Algorithms**:
   - FIFO: First-in-first-out queue for fair resource allocation
   - EDF: Priority queue based on earliest deadline for urgent task handling

These mechanisms ensure thread-safe access to shared resources while demonstrating different approaches to concurrency control in a multi-threaded simulation.