/**
 * @file input.c
 * @author simon.racaud
 * createdAt: 11:49:19 AM Thu Sep 29 2022
 * updatedAt: 11:49:19 AM Thu Sep 29 2022
 * Management of the file operations
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "simulator.h"

static const size_t memory_alloc_unit = 10;

/**
 * @brief Parse a file line into a proces_input_t
 * 
 * @param line 
 * @param out : location of write the data
 * @return EXIT_SUCCESS | EXIT_FAILURE
 */
static int parse_line(char *line, process_input_t *out)
{
    char *token = strtok(line, " ");
    size_t i;

    for (i = 0; token != NULL && i < 4; i++) {
        if (i == 0) {
            strcpy(out->process_name, token);
        } else if (i == 1) {
            out->arrival_time = atoi(token);
        } else if (i == 2) {
            out->service_time = atoi(token);
        } else if (i == 3) {
            out->deadline = atoi(token);
        }
        token = strtok(NULL, " ");
    }
    if (i != 4) {
        fprintf(stderr, "Error, invalid entry in input file\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
 * @brief Read the input file and return a list of structure related to 
 *  its content.
 * 
 * @param filepath[in] : path of the input file
 * @param size[out] : size of the array returned
 * @return process_input_t* array of process entries
 *      return NULL in case of error
 */
process_input_t *read_input(char const *filepath, size_t *size)
{
    process_input_t *inputs = malloc(sizeof(process_input_t) * memory_alloc_unit);
    size_t idx = 0;
    char *line = NULL;
    size_t line_size = 0;
    int status;
    FILE *file;

    *size = memory_alloc_unit;
    // Open file
    file = fopen(filepath, "r");
    if (!file) {
        perror(NULL);
        return NULL;
    }
    // Read content line per line
    while (getline(&line, &line_size, file) > 0) {
        // Increase the size of the structure array:
        if (idx == *size - 1) { 
            inputs = realloc(inputs, sizeof(process_input_t) * (*size + memory_alloc_unit));
            *size += memory_alloc_unit;
        }
        // Parse the line:
        status = parse_line(line, &inputs[idx]);
        if (status == EXIT_FAILURE) {
            free(inputs);
            free(line);
            return NULL;
        }
        idx++;
        free(line);
        line = NULL;
        line_size = 0;
    }
    // Cleanup
    free(line);
    fclose(file);
    *size = idx;
    return inputs;
}

/**
 * @brief Write data to output file
 * 
 * @param array[in] : data to write
 * @param size : size of array 
 * @param task : task number (1 to 3)
 * @return int EXIT_SUCCESS | EXIT_FAILURE
 */
int output_generator(const process_result_t *array, size_t size, int task)
{
    char filename[] = "results-X.txt";
    FILE *file;

    if (task > 3 || task < 1) {
        return EXIT_FAILURE;
    }
    filename[8] = task + '0';
    // Open file
    file = fopen(filename, "w");
    if (!file) {
        perror(NULL);
        return EXIT_FAILURE;
    }
    // Write logs, line per line
    for (size_t i = 0; i < size; i++) {
        fprintf(file, "%s %d %d %d\n",
            array[i].process_name, 
            array[i].wait_time, 
            array[i].turnaround_time, 
            (int)array[i].deadline_met);
    }
    // Cleanup
    fclose(file);
    return EXIT_SUCCESS;
}