/**
 * @file pcb.h
 * @author simon.racaud 33287430 srac0005@student.monash.edu
 * createdAt: 11:34:24 AM Thu Sep 29 2022
 * updatedAt: 11:34:24 AM Thu Sep 29 2022
 * Process control block
 */

#ifndef H_PCB
#define H_PCB

typedef enum {
    READY,      // The process is ready to run
    RUNNING,    // The process is running
    EXIT        // The process ended
} process_state_t;

typedef struct {
    char process_name[11];

    int entry_time;      // Time process entered system
    int service_time;    // Total time required by process
    int remaining_time;  // Remaining time until completion

    process_state_t state; // Current state of the process
} pcb_t;

#endif