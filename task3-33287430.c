/**
 * @file task3-33287430.c
 * @author simon.racaud 33287430 srac0005@student.monash.edu
 * createdAt: 5:29:24 PM Thu Sep 29 2022
 * updatedAt: 5:29:24 PM Thu Sep 29 2022
 * Deadline based scheduler
 */

#include <stdlib.h>
#include <stdio.h>

#include "assignment2.h"

/**
 * @brief Compute the remaining time the process have before its deadline
 * 
 * @param node : PCB node
 * @param clock : clock counter
 * @return int : remaining time in second
 */
static int get_remaining_time(pcb_node_t *node, size_t clock)
{
    return node->data.deadline - ((int)clock - node->data.entry_time);
}

/**
 * @brief Earliest Deadline First scheduler
 * 
 * @param list_ptr : linked list of PCB
 * @param prev_node : previous PCB scheduled or NULL
 * @param clock : clock counter
 * @return pcb_node_t* : next PCB to run
 */
static pcb_node_t *deadline_based_scheduler(
    pcb_node_t **list_ptr, 
    UNUSED pcb_node_t *prev_node, 
    size_t clock)
{
    pcb_node_t *selected = *list_ptr;
    int remaining_select;

    if (!selected)
        return NULL; // Empty PCB list
    if (!selected->next)
        return selected; // Only one node in the list
    // remaining time before the deadline of the first process:
    remaining_select = get_remaining_time(selected, clock);
    for (pcb_node_t *it = (*list_ptr)->next; it; it = it->next) {
        // remaining time before the deadline of the current process:
        int remaining = get_remaining_time(it, clock);

        if (remaining < remaining_select) {
            // the current process has a lower remaining time
            selected = it;
            remaining_select = remaining;
        }
    }
    return selected;
}

int main(int argc, char **argv)
{
    const int TASK_ID = 3;

    return simulator(argc, argv, &deadline_based_scheduler, TASK_ID);
}