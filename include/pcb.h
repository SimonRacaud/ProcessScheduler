/**
 * @file pcb.h
 * @author simon.racaud
 * createdAt: 11:34:24 AM Thu Sep 29 2022
 * updatedAt: 11:34:24 AM Thu Sep 29 2022
 * Process control block
 */

#ifndef H_PCB
#define H_PCB

/**
 * @brief Process states
 */
typedef enum {
    READY,      // The process is ready to run
    RUNNING,    // The process is running
    EXIT        // The process ended
} process_state_t;

/**
 * @brief Process control block
 */
typedef struct {
    char process_name[11];

    int entry_time;      // Time process enter system
    int service_time;    // Total time required by process
    int remaining_time;  // Remaining time until completion

    int start_time;      // Time when process first entered RUNNING state
    const int deadline;  // Deadline of the process

    process_state_t state; // Current state of the process
} pcb_t;

#endif