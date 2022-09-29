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
#include <stddef.h>
#include "pcb.h"

#define DEF_INPUT_FILE "processes.txt"
#define UNUSED __attribute__((unused))

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

typedef struct pcb_node {
    pcb_t data;
    struct pcb_node *next;
} pcb_node_t;

typedef enum event {
    E_CREATE,
    E_START,
    E_EXIT
} event_t;

/**
 * @brief Scheduler function pointer
 * @param list_ptr : linked list of pcb
 * @param prev_node : node previously selected by the scheduler
 * @param clock : clock counter
 */
typedef pcb_node_t *(* scheduler_t)(pcb_node_t **list_ptr, pcb_node_t *prev_node, size_t clock);

/// PROTOTYPES

process_input_t *read_input(char const *filepath, size_t *size);

process_result_t *simulate(
    process_input_t *inputs, 
    size_t size_in, 
    scheduler_t scheduler, 
    size_t *size_out);

char const *get_intput_filepath(int argc, char **argv);

int output_generator(const process_result_t *array, size_t size, int task);

// List:
pcb_node_t *node_push(pcb_node_t *list, const process_input_t *data, size_t time);
pcb_node_t *node_remove(pcb_node_t *list, pcb_node_t *to_remove);
pcb_node_t *node_move_back(pcb_node_t *list);
void list_destroy(pcb_node_t *list);

#endif