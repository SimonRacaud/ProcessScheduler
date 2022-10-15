__Author__: simon.racaud

__Description__: Documentation of the program.

# BUILD

To compile the three schedulers:
```bash
$> make
```

To compile a specific task: 
```bash
$> make <binary-name>
$> make fcfs_scheduler rr_scheduler edf_scheduler
```

Other commands:
```bash
$> make clean       # To remove the objects
$> make fclean      # To remove the objects and binaries
$> make re          # alias for 'make clean all'
```

# RUN

To run a task, execute the corresponding binary file (fcfs_scheduler, rr_scheduler or edf_scheduler):
```bash
$> ./<algo>_scheduler <filepath>
```
The <filepath> parameter is optional. If not given, ./processes.txt will be used.
<filepath> is pointing on the file containing the instructions to run the simulator.

# Examples:

## First-Come First-Served:

Content of processes.txt
```
W 0 4 5
X 2 5 7
Y 3 8 6
Z 8 3 2
```
```bash
$> ./fcfs_scheduler processes.txt && cat results-1.txt
```
The result will be:
```
Time 0: W has entered the system.
Time 0: W is in the running state.
Time 2: X has entered the system.
Time 3: Y has entered the system.
Time 4: W has finished execution.
Time 4: X is in the running state.
Time 8: Z has entered the system.
Time 9: X has finished execution.
Time 9: Y is in the running state.
Time 17: Y has finished execution.
Time 17: Z is in the running state.
Time 20: Z has finished execution.
W 0 4 1
X 2 7 1
Y 6 14 0
Z 9 12 0
```
The processes enter in order: W, X, Y, Z and are executed in the same order.

## Round-robin:

Content of processes.txt
```
W 0 4 5
X 2 5 7
Y 3 8 6
Z 8 3 2
```
```bash
$> ./rr_scheduler processes.txt && cat results-2.txt
```
The result will be:
```
Time 0: W has entered the system.
Time 0: W is in the running state.
Time 2: X has entered the system.
Time 2: X is in the running state.
Time 3: Y has entered the system.
Time 4: Y is in the running state.
Time 6: W is in the running state.
Time 8: W has finished execution.
Time 8: Z has entered the system.
Time 8: Z is in the running state.
Time 10: X is in the running state.
Time 12: Y is in the running state.
Time 14: Z is in the running state.
Time 15: Z has finished execution.
Time 15: X is in the running state.
Time 16: X has finished execution.
Time 16: Y is in the running state.
Time 20: Y has finished execution.
W 0 8 0
Z 0 7 0
X 0 14 0
Y 1 17 0
Z 9 12 0
```
- The processes selected by the scheduler changes each 2 clock ticks.
- Y enters at 3, when X is being executed. So it starts at the next round (4).
- Z enters at 8, the scheduler is looking for a new process at the same time, so Z is selected.
- (...)

## Earliest Deadline First:

Content of processes.txt
```
W 0 4 5
X 2 5 7
Y 3 8 6
Z 8 3 2
```
```bash
$> ./edf_scheduler processes.txt && cat results-3.txt
```
The result will be:
```
Time 0: W has entered the system.
Time 0: W is in the running state.
Time 2: X has entered the system.
Time 3: Y has entered the system.
Time 4: W has finished execution.
Time 4: Y is in the running state.
Time 8: Z has entered the system.
Time 12: Y has finished execution.
Time 12: X is in the running state.
Time 17: X has finished execution.
Time 17: Z is in the running state.
Time 20: Z has finished execution.
W 0 4 1
Y 1 9 0
X 10 15 0
Z 9 12 0
```
To undestand the order of execution, let's use a table.

Remainder about processes.txt:
```
+---------+-------+---------+----------+
| Process | Start | Service | Deadline |
+---------+-------+---------+----------+
| W       |     0 |       4 |        5 |
| X       |     2 |       5 |        7 |
| Y       |     3 |       8 |        6 |
| Z       |     8 |       3 |        2 |
+---------+-------+---------+----------+
```
Computation of the remaining time before the deadline over the time:
```
+-------+----------+----------+----------+----------+----------+
| Time: | Selected | W remain | X remain | Y remain | Z remain |
+-------+----------+----------+----------+----------+----------+
|     0 | W        |     >  5 |          |          |          |
|     1 | W        |     >  4 |          |          |          |
|     2 | W        |     >  3 |        7 |          |          |
|     3 | W        |     >  2 |        6 |        6 |          |
|     4 | Y        |          |        5 |     >  5 |          |
|     5 | Y        |          |        4 |     >  4 |          |
|     6 | Y        |          |        3 |     >  3 |          |
|     7 | Y        |          |        2 |     >  2 |          |
|     8 | Y        |          |        1 |     >  1 |        2 |
|     9 | Y        |          |        0 |     >  0 |        1 |
|    10 | Y        |          |       -1 |     > -1 |        0 |
|    11 | Y        |          |       -2 |     > -2 |       -1 |
|    12 | X        |          |     > -3 |          |       -2 |
|    13 | X        |          |     > -4 |          |       -3 |
|    14 | X        |          |     > -5 |          |       -4 |
|    15 | X        |          |     > -6 |          |       -5 |
|    16 | X        |          |     > -7 |          |       -6 |
|    17 | X        |          |     > -8 |          |       -7 |
|    18 | Z        |          |          |          |    >  -8 |
|    19 | Z        |          |          |          |    >  -9 |
|    20 | Z        |          |          |          |    > -10 |
+-------+-------- -+----------+----------+----------+----------+
```
At 4, the processes Y and X have the same remaining time, but Y is selected because it's the last one to enter the queue.

_____________________________
# Algorithms

## Task 1 - FCFS

The First-Come-First-Served scheduler always select the oldest process of the queue to run first.

## Task 2 - Round-robin

The round-robin scheduler runs the first process of the PCB queue.
After running it, the process's PCB is moved at the end of the queue.
Any new process entering the system will be added at the beginning of the queue.

Important: The next process to run will always be the last process to enter the queue.
E.g: If A is running from 0 to 3. B enter at 1. C enter at 2. Then the next process to run will be C.

## Task 3 - Earliest Deadline First

The process with the shortest time before the deadline will run first.
The shortest time before the deadline is the deadline minus the age of the PCB (now - entry time).

If two processes have the same remaining time before the deadline, the last process to enter the queue will be selected.
