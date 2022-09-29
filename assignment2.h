/**
 * @file assignment2.h
 * @author simon.racaud 33287430 srac0005@student.monash.edu
 * createdAt: 11:31:34 AM Thu Sep 29 2022
 * updatedAt: 11:31:34 AM Thu Sep 29 2022
 * Main header of the programs
 */

#ifndef H_ASS2
#define H_ASS2

#include <stdbool.h>

#define DEF_INPUT_FILE "processes.txt"

#include "pcb.h"

// STRUCTURES

typedef struct {
    char process_name[11];

    int arrival_time; // Time when the process is ready to start its execution
    int service_time; // Total time required by the process
    int deadline;     // Deadline of turnaround time the process have to met
} process_input_t;

typedef struct {
    char process_name[11];
    int wait_time;          // Time before starting execution
    int turnaround_time;    // Waiting time + Running time of process
    bool deadline_met;      // If the deadline have been met
} process_result_t;

/// PROTOTYPES

process_input_t *read_input(char const *filepath, size_t *size);

char const *get_intput_filepath(int argc, char **argv);

int output_generator(const process_result_t *array, size_t size, int task);

#endif