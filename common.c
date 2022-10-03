/**
 * @file common.c
 * @author simon.racaud 33287430 srac0005@student.monash.edu
 * createdAt: 4:14:50 PM Thu Sep 29 2022
 * updatedAt: 4:14:50 PM Thu Sep 29 2022
 * Common functions between the tasks
 */

#include "assignment2.h"

#include <stdlib.h>

/**
 * @brief Read and parse input configuration
 * 
 * @param argc 
 * @param argv 
 * @param input_size[out] size of the returned array 
 * @return process_input_t*  : configuration of the simulator
 */
static process_input_t *simulator_init(int argc, char **argv, size_t *input_size)
{
    char const *filepath = get_intput_filepath(argc, argv);

    *input_size = 0;
    return read_input(filepath, input_size); // Read and parse input file
}

/**
 * @brief Generate program outputs and cleanup
 * 
 * @param results : records of the simulation
 * @param size : size of results 
 * @param task_id : Id of the task [1-3]
 * @param inputs : configuration of the simulator
 * @return int EXIT_SUCCESS | EXIT_FAILURE
 */
static int simulator_exit(
    process_result_t *results, 
    size_t size, 
    size_t task_id, 
    process_input_t *inputs)
{
    int status = EXIT_SUCCESS;

    // Write outputs
    status = output_generator(results, size, task_id);
    // Cleanup
    free(results);
    free(inputs);
    return status;
}

/**
 * @brief Execute a simulation
 * 
 * @param argc : argument counter
 * @param argv : argument values
 * @param scheduler : scheduler function callback
 * @param task_id : Id of the task [1-3]
 * @return int EXIT_SUCCESS | EXIT_FAILURE
 */
int simulator(int argc, char **argv, scheduler_t scheduler, size_t task_id)
{
    size_t input_size = 0;
    size_t result_size = 0;
    process_input_t *inputs = simulator_init(argc, argv, &input_size);
    process_result_t *results;

    if (!inputs) {
        return EXIT_FAILURE;
    }
    // Simulator:
    results = simulate(inputs, input_size, scheduler, &result_size);
    // Exit:    
    return simulator_exit(results, input_size, task_id, inputs);
}
