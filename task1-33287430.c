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

/**
 * @brief First-Come-First-Served scheduler
 * 
 * @param list_ptr : PCB linked list
 * @param prev_node : Previous PCB selected to run
 * @param clock : clock counter
 * @return pcb_node_t* : Next PCB to run
 */
static pcb_node_t *fcfs_scheduler(
    pcb_node_t **list_ptr, 
    UNUSED pcb_node_t *prev_node, 
    UNUSED size_t clock)
{
    for (pcb_node_t *it = *list_ptr; it; it = it->next) {
        if (it->next == NULL) {
            return it; // return last node of the list (older PCB)
        }
    }
    return NULL; // in case of an empty PCB list
}

int main(int argc, char **argv)
{
    const int TASK_ID = 1;

    return simulator(argc, argv, &fcfs_scheduler, TASK_ID);
}