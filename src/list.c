/**
 * @file list.c
 * @author simon.racaud
 * createdAt: 2:24:27 PM Thu Sep 29 2022
 * updatedAt: 2:24:27 PM Thu Sep 29 2022
 * Linked list of pcb
 */

#include "simulator.h"

#include <string.h>
#include <stdlib.h>

static pcb_node_t *node_create(const process_input_t *data, size_t time)
{
    pcb_node_t *node = malloc(sizeof(pcb_node_t));

    if (!node)
        return NULL;
    strcpy(node->data.process_name, data->process_name);
    node->data.entry_time = time;
    node->data.remaining_time = data->service_time;
    node->data.service_time = data->service_time;
    node->data.state = READY;
    node->data.start_time = -1;
    *(int *)&node->data.deadline = data->deadline;
    node->next = NULL;
    return node;
}

/**
 * @brief Add a new node at the beginning of the list
 * 
 * @param list previous list
 * @param data description of the new pcb
 * @param time current clock time
 * @return pcb_node_t* pointer on the new node
 */
pcb_node_t *node_push(pcb_node_t *list, const process_input_t *data, size_t time)
{
    pcb_node_t *new = node_create(data, time);

    new->next = list;
    return new;
}

/**
 * @brief Remove a node of the linked list
 * 
 * @param list 
 * @param to_remove 
 * @return pcb_node_t *
 */
pcb_node_t *node_remove(pcb_node_t *list, pcb_node_t *to_remove)
{
    pcb_node_t *prev = NULL;
    for (pcb_node_t *it = list; it; it = it->next) {
        if (it == to_remove) {
            if (prev) {
                prev->next = it->next;
                free(it);
                return list;
            }
            pcb_node_t *new_head = it->next;
            free(it);
            return new_head; // Removing the first node
        }
        prev = it;
    }
    return list; // node not found
}

/**
 * @brief Move first node of the list at the back
 * 
 * @param list 
 * @param node: node to move at the end of list
 * @return pcb_node_t* 
 */
pcb_node_t *node_move_back(pcb_node_t *list, pcb_node_t *node)
{
    pcb_node_t *prev = NULL;
    pcb_node_t *node_prev = NULL;
    pcb_node_t *new_head = (node) ? node->next : NULL;

    if (!list || !node)
        return NULL;
    if (node->next == NULL)
        return list; // The node is already at the end of the list.
    for (pcb_node_t *it = list; it; it = it->next) {
        if (it == node) {
            node_prev = prev; // Save node parent.
        } else if (it->next == NULL) {
            it->next = node;
            if (node_prev) {
                // The node to move have a previous node:
                node_prev->next = node->next;
            }
            node->next = NULL;
            break;
        }
        prev = it;
    }
    return (node_prev) 
        ? node_prev  // The node to move had a parent.
        : (new_head) 
            ? new_head // The node to move had a children.
            : node; // The list size is 1
}

/**
 * @brief Free list memory
 * 
 * @param list 
 */
void list_destroy(pcb_node_t *list)
{
    pcb_node_t *next = NULL;
    for (pcb_node_t *it = list; it; it = next) {
        next = it->next;
        free(it);
    }
}