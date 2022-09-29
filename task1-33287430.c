/**
 * @file task1-33287430.c
 * @author simon.racaud 33287430 srac0005@student.monash.edu
 * createdAt: 11:28:02 AM Thu Sep 29 2022
 * updatedAt: 11:28:02 AM Thu Sep 29 2022
 * main function of task 1
 */

#include <stdlib.h>
#include <stdio.h>

#include "assignment2.h"

static const int TASK_ID = 1;

static pcb_node_t *fcfs_scheduler(
    pcb_node_t **list_ptr, 
    UNUSED pcb_node_t *prev_node, 
    UNUSED size_t clock)
{
    for (pcb_node_t *it = *list_ptr; it; it = it->next) {
        if (it->next == NULL) {
            return it; // return last node of the list (older PCB)
        }
    }
    return NULL; // in case of an empty PCB list
}

int main(int argc, char **argv)
{
    char const *filepath = get_intput_filepath(argc, argv);
    size_t size = 0;
    process_input_t *inputs = read_input(filepath, &size);
    int status = EXIT_SUCCESS;
    size_t result_size = 0;

    if (!inputs) {
        return EXIT_FAILURE;
    }
    // Simulator:
    process_result_t *results = simulate(inputs, size, &fcfs_scheduler, &result_size);
    // Write outputs
    status = output_generator(results, size, TASK_ID);
    // Clean before exit
    free(inputs);
    free(results);
    return status;
}