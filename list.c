/* Cynthia Joseph (938358) - Assignment 2 COMP20003
Linked list operations - Recycled code from Assignment 1
*/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

#define MAXLINE 513
#define MAXFIELD 129
#define MAXKEYS 20



/* =====================================================================
   listops.c
   ================================================================== */

list_t *make_empty_list(void) {
    list_t *list = (list_t*)malloc(sizeof(*list));
    assert(list!=NULL);
    list->head = list->foot = NULL;
    return list;
}

void free_list(list_t *list) {
    node_t *curr, *prev;
    assert(list!=NULL);
    curr = list->head;
    while (curr) {
        prev = curr;
        curr = curr->next;
        
        free(prev);
        
    }
    free(list);
}

list_t *insert_at_foot(list_t *list, data_t value) {
    node_t *new = (node_t*)malloc(sizeof(*new));
    assert(list!=NULL && new!=NULL);
    new->data = value;
    new->next = NULL;
    if (list->foot==NULL) {
        list->head = list->foot = new;
    } else {
        list->foot->next = new;
        list->foot = new;
    }
    return list;
}

/* =====================================================================
   Program written by Alistair Moffat, as an example for the book
   "Programming, Problem Solving, and Abstraction with C", Pearson
   Custom Books, Sydney, Australia, 2002; revised edition 2012,
   ISBN 9781486010974.

   See http://people.eng.unimelb.edu.au/ammoffat/ppsaa/ for further
   information.

   Prepared December 2012 for the Revised Edition.
   ================================================================== */



/* Map 1 - prints found records from list */
void printlist(char *x, char *y, list_t *list, FILE *out_file) {
    node_t *temp = list->head;
    while(temp != NULL) {
        fprintf(out_file, "%s %s --> Census year: %d || Block ID: %d || Property ID: %d || Base property ID: %d || CLUE small area: %s || Trading Name: %s || Industry (ANZSIC4) code: %d || Industry (ANZSIC4) description: %s || x coordinate: %.5lf || y coordinate: %.5lf || Location: %s) || \n", 
                        x, y, 
                        (temp->data)->censusYear,
                        (temp->data)->blockID, 
                        (temp->data)->propertyID, 
                        (temp->data)->basePropertyID, 
                        (temp->data)->clueSmallArea, 
                        (temp->data)->tradingName, 
                        (temp->data)->industryCode,
                        (temp->data)->industryDescription, 
                        (temp->data)->xCoordinate, 
                        (temp->data)->yCoordinate, 
                        (temp->data)->location);  
        temp = temp->next;
    }
}



/* Map 2 - prints found records from list*/
void printlist_map2(char *x, char *y, char *r, list_t *list, FILE *out_file) {
    node_t *temp = list->head;
    while(temp != NULL) {
        fprintf(out_file, "%s %s %s --> Census year: %d || Block ID: %d || Property ID: %d || Base property ID: %d || CLUE small area: %s || Trading Name: %s || Industry (ANZSIC4) code: %d || Industry (ANZSIC4) description: %s || x coordinate: %.5lf || y coordinate: %.5lf || Location: %s) || \n", 
                        x, y, r,
                        (temp->data)->censusYear,
                        (temp->data)->blockID, 
                        (temp->data)->propertyID, 
                        (temp->data)->basePropertyID, 
                        (temp->data)->clueSmallArea, 
                        (temp->data)->tradingName, 
                        (temp->data)->industryCode,
                        (temp->data)->industryDescription, 
                        (temp->data)->xCoordinate, 
                        (temp->data)->yCoordinate, 
                        (temp->data)->location);  
        temp = temp->next;
    }
}



//Frees struct values in the linked list
void free_list_structs(list_t *list){
    node_t *temp = list->head;
    while (temp!= NULL){
        free(temp->data->tradingName);
        free(temp->data->clueSmallArea);
        free(temp->data->industryDescription);
        free(temp->data->location);
        free(temp->data);
        temp = temp -> next;
    }
    free(temp);
}