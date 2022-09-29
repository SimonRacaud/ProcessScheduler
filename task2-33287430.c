/**
 * @file task1-33287430.c
 * @author simon.racaud 33287430 srac0005@student.monash.edu
 * createdAt: 11:28:02 AM Thu Sep 29 2022
 * updatedAt: 11:28:02 AM Thu Sep 29 2022
 * main function of task 2
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
        counter = QUANTUM; // Reset counter
        if (counter == 0) {
            // Push the current process to end of the queue:
            *list_ptr = node_move_back(*list_ptr);
        }
    } else {
        counter--;
    }
    return *list_ptr; // The head of the queue
}

int main(int argc, char **argv)
{
    const int TASK_ID = 2;

    return simulator(argc, argv, &rr_scheduler, TASK_ID);
}