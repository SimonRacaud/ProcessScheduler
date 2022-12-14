/**
 * @file arg.c
 * @author simon.racaud
 * createdAt: 12:14:16 PM Thu Sep 29 2022
 * updatedAt: 12:14:16 PM Thu Sep 29 2022
 * Parse the program argument
 */

#include <stdio.h>

#include "simulator.h"

/**
 * @brief Return the filepath of the input process file
 * 
 * @param argc argument counter
 * @param argv argument values
 * @return char const* file path
 */
char const *get_intput_filepath(int argc, char **argv)
{
    if (argc > 2) {
        // Too many arguments
        fprintf(stderr, "%s <optional-file-path>\n", argv[0]);
        return NULL;
    }
    if (argc == 2) {
        return argv[1]; // File path provided
    }
    return DEF_INPUT_FILE; // Use the default path
}