/**
 * @file assignment2.h
 * @author simon.racaud 33287430 srac0005@student.monash.edu
 * createdAt: 11:31:34 AM Thu Sep 29 2022
 * updatedAt: 11:31:34 AM Thu Sep 29 2022
 * Main header of the programs
 */

#ifndef H_ASS2
#define H_ASS2

#define DEF_INPUT_FILE "processes.txt"

#include "pcb.h"

typedef struct {
    char process_name[11];

    int arrival_time; // Time when the process is ready to start its execution
    int service_time; // Total time required by the process
    int deadline;     // Deadline of turnaround time the process have to met
} process_input_t;


process_input_t *read_input(char const *filepath, size_t *size);

char const *get_intput_filepath(int argc, char **argv);

#endif