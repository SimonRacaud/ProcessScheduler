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

/**
 * @brief Description of a process read from the input file.
 */
typedef struct {
    char process_name[11];

    int arrival_time; // Time when the process is ready to start its execution
    int service_time; // Total time required by the process
    int deadline;     // Deadline of turnaround time the process have to met
} process_input_t;

/**
 * @brief Report about the simulation of a process.
 */
typedef struct {
    char process_name[11];
    int wait_time;          // Time before starting execution
    int turnaround_time;    // Waiting time + Running time of process
    bool deadline_met;      // If the deadline have been met
} process_result_t;

/**
 * @brief PCB linked list node
 */
typedef struct pcb_node {
    pcb_t data;
    struct pcb_node *next;
} pcb_node_t;

/**
 * @brief Process simulation event
 */
typedef enum event {
    E_CREATE, // PCB created
    E_START,  // Process started for the first time
    E_EXIT    // Process exited
} event_t;

/**
 * @brief Scheduler function pointer
 * @param list_ptr : linked list of pcb
 * @param prev_node : node previously selected by the scheduler or NULL
 * @param clock : clock counter
 */
typedef pcb_node_t *(* scheduler_t)(pcb_node_t **list_ptr, pcb_node_t *prev_node, size_t clock);

/// PROTOTYPES

// Common:

/**
 * @brief Execute a simulation
 * 
 * @param argc : argument counter
 * @param argv : argument values
 * @param scheduler : scheduler function callback
 * @param task_id : Id of the task [1-3]
 * @return int EXIT_SUCCESS | EXIT_FAILURE
 */
int simulator(int argc, char **argv, scheduler_t scheduler, size_t task_id);

// Internal functions:

/**
 * @brief Process scheduling simulator
 * 
 * @param inputs[in] : description of the processes to run
 * @param size_in[in] : size of inputs 
 * @param scheduler[in] : callback on the selected scheduler
 * @param size_out[out] : size of the array returned
 * @return process_result_t* : description of the processes execution
 */
process_result_t *simulate(
    process_input_t *inputs, 
    size_t size_in, 
    scheduler_t scheduler, 
    size_t *size_out);

/**
 * @brief Read the input file and return a list of structure related to the
 *      its content.
 * 
 * @param filepath[in] : path of the input file
 * @param size[out] : size of the array returned
 * @return process_input_t* array of process entries
 *      return NULL in case of error
 */
process_input_t *read_input(char const *filepath, size_t *size);

/**
 * @brief Return the filepath of the input process file
 * 
 * @param argc argument counter
 * @param argv argument values
 * @return char const* file path
 */
char const *get_intput_filepath(int argc, char **argv);

/**
 * @brief Write data to output file
 * 
 * @param array[in] : data to write
 * @param size : size of array 
 * @param task : task number (1 to 3)
 * @return int EXIT_SUCCESS | EXIT_FAILURE
 */
int output_generator(const process_result_t *array, size_t size, int task);

// List:
/**
 * @brief Add a new node at the beginning of the list
 * 
 * @param list previous list
 * @param data description of the new pcb
 * @param time current clock time
 * @return pcb_node_t* pointer on the new node
 */
pcb_node_t *node_push(pcb_node_t *list, const process_input_t *data, size_t time);
/**
 * @brief Remove a node of the linked list
 * 
 * @param list 
 * @param to_remove 
 * @return pcb_node_t *
 */
pcb_node_t *node_remove(pcb_node_t *list, pcb_node_t *to_remove);
/**
 * @brief Move first node of the list at the back
 * 
 * @param list 
 * @param node: node to move at the end of list
 * @return pcb_node_t* 
 */
pcb_node_t *node_move_back(pcb_node_t *list, pcb_node_t *node);
/**
 * @brief Free list memory
 * 
 * @param list 
 */
void list_destroy(pcb_node_t *list);

#endif