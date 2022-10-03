/**
 * @file task2-33287430.c
 * @author simon.racaud 33287430 srac0005@student.monash.edu
 * createdAt: 5:29:02 PM Thu Sep 29 2022
 * updatedAt: 5:29:02 PM Thu Sep 29 2022
 * Round-robin scheduler
 */

#include <stdlib.h>
#include <stdio.h>

#include "assignment2.h"

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