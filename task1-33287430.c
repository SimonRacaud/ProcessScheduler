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

int main(int argc, char **argv)
{
    char const *filepath = get_intput_filepath(argc, argv);
    size_t size = 0;
    process_input_t *inputs = read_input(filepath, &size);
    int status = EXIT_SUCCESS;

    if (!inputs) {
        return EXIT_FAILURE;
    }
    // Simulator:
    process_result_t *results = NULL; // simulate(inputs, &size);
    // Write outputs
    status = output_generator(results, size, TASK_ID);
    // Clean before exit
    free(inputs);
    return status;
}