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

int main(int argc, char **argv)
{
    char const *filepath = get_intput_filepath(argc, argv);
    size_t size = 0;
    process_input_t *inputs = read_input(filepath, &size);

    if (!inputs) {
        return EXIT_FAILURE;
    }
    // Simulator:
    for (size_t i = 0; i < size; i++) {
        printf("Name: %s, Arrival: %d, Service: %d, Deadline: %d\n", 
            inputs[i].process_name, inputs[i].arrival_time, inputs[i].service_time, inputs[i].deadline);
    }
    // Clean before exit
    free(inputs);
    return EXIT_SUCCESS;
}