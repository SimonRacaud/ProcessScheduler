/**
 * @file simulator.c
 * @author simon.racaud 33287430 srac0005@student.monash.edu
 * createdAt: 12:42:41 PM Thu Sep 29 2022
 * updatedAt: 12:42:41 PM Thu Sep 29 2022
 * Scheduler simulator
 */

#include "assignment2.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

/**
 * @brief STDOUT process state logger
 * 
 * @param evt : The event which occurred
 * @param proc_name : The node of the process related to the event
 * @param clock : clock counter
 */
static void logger(event_t evt, const char *proc_name, size_t clock)
{
    switch (evt)
    {
    case E_CREATE:
        printf("Time %lu: %s has entered the system.\n", clock, proc_name);
        break;
    case E_START:
        printf("Time %lu: %s is in the running state.\n", clock, proc_name);
        break;
    case E_EXIT:
        printf("Time %lu: %s has finished execution.\n", clock, proc_name);
        break;
    default:
        break;
    }
}

static pcb_node_t *manage_process_entry(
    pcb_node_t *processes, 
    const process_input_t *inputs, 
    size_t inputs_size, 
    size_t clock)
{
    for (size_t i = 0; i < inputs_size; i++) {
        if (clock == (size_t)inputs[i].arrival_time) {
            logger(E_CREATE, inputs[i].process_name, clock);
            // Push node to the front of the list
            processes = node_push(processes, &inputs[i], clock);
        }
    }
    return processes;
}

static pcb_node_t *clean_exited_processes(
    pcb_node_t *processes, 
    pcb_node_t **running_node, 
    UNUSED process_result_t *result, 
    size_t *result_size, 
    size_t clock)
{
    pcb_node_t *next = NULL;
   for (pcb_node_t *it = processes; it; it = next) {
        if (it->data.state == EXIT) {
            logger(E_EXIT, it->data.process_name, clock);
            // TODO : add result
            (*result_size) += 1;
            next = it->next;
            if (*running_node == it) {
                *running_node = NULL;
            }
            processes = node_remove(processes, it);
        } else {
            next = it->next;
        }
   }
   return processes;
}

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
    size_t *size_out)
{
    process_result_t *result = calloc(size_in, sizeof(process_result_t));
    size_t clock = 0;
    pcb_node_t *processes = NULL;
    pcb_node_t *running_node = NULL;

    while (processes || clock == 0) {
        processes = clean_exited_processes(processes, &running_node, result, size_out, clock);
        processes = manage_process_entry(processes, inputs, size_in, clock);
        pcb_node_t *select_node = scheduler(&processes, running_node, clock);

        // If a NEW process is elected to run:
        if (select_node && running_node != select_node) {
            select_node->data.state = RUNNING; // Start new process
            if (running_node)
                running_node->data.state = READY; // Put the previous process in pause
            logger(E_START, select_node->data.process_name, clock);
        }
        if (select_node) {
            select_node->data.remaining_time--; // Decrease remaining time
            if (select_node->data.remaining_time == 0) {
                select_node->data.state = EXIT; // Process end of work
            }
        }
        running_node = select_node;
        clock++;
    }
    // cleanup
    list_destroy(processes);
    return result;
}