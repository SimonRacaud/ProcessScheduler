/**
 * @file main_rr.c
 * @author simon.racaud
 * createdAt: 5:29:02 PM Thu Sep 29 2022
 * updatedAt: 5:29:02 PM Thu Sep 29 2022
 * Round-robin scheduler
 */

#include <stdlib.h>
#include <stdio.h>

#include "simulator.h"

static const size_t QUANTUM = 2;

/**
 * @brief Round-robin scheduler
 * 
 * @param list_ptr : linked list of PCB
 * @param prev_node : previous PCB scheduled or NULL
 * @param clock : clock counter
 * @return pcb_node_t* : next PCB to run
 */
static pcb_node_t *rr_scheduler(
    pcb_node_t **list_ptr, 
    pcb_node_t *prev_node, 
    UNUSED size_t clock)
{
    static size_t counter = QUANTUM;

    if (counter == 0 || !prev_node) {
        // Time to switch to another process 
        //  or previous process no longer exists (exited).
        counter = QUANTUM - 1; // Reset counter
        if (prev_node) {
            // Push the previous process to the end of the queue:
            *list_ptr = node_move_back(*list_ptr, prev_node);
        }
        return *list_ptr; // Return the first process of the queue
    } else {
        // Continue running previous process
        counter--;
        return prev_node;
    }
}

int main(int argc, char **argv)
{
    const int TASK_ID = 2;

    return simulator(argc, argv, &rr_scheduler, TASK_ID);
}