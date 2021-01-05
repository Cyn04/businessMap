/* Cynthia Joseph (938358) - Assignment 2 COMP20003
Kd tree operations

Citation/reference used to help build read_file_into_dict function from lines 236-307:
Torok, R (2018) Parsing CSV Files in C source code (Version 1) [Source code]. https://codingboost.com/parsing-csv-files-in-c

Citation/reference used to help build recursion condition from lines 141-143 and 197-199:
Anonymous, (2010). Quickselectesque median algorithm in C (Version 1) [Source Code]. https://rosettacode.org/wiki/K-d_tree

Note that none of the codes from the references were copied, only the idea of the method was used (:
*/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "list.h"
#include "bst.h"

#define MAXLINE 513
#define MAXFIELD 129
#define MAXDIMENSION 2
#define k 2
#define EPSILON 1e-7



//makes a new node, where data is an empty linked list
nodekd new_node(record_t *record){ 
    nodekd temp = malloc(sizeof(*temp));
    assert(temp);
    temp->datakd = make_empty_list();
    temp->datakd = insert_at_foot(temp->datakd, record);
    
    temp->left = temp->right = NULL; 
    return temp;
} 



//inserts the given record into a linked list into the kd tree
nodekd insert_record(nodekd curr_nodekd, record_t *new_p, int depth) { 
    
    if (curr_nodekd == NULL){
       return new_node(new_p);
    }

    record_t *curr_node_data_head = curr_nodekd->datakd->head->data;

    int d = depth % k; 
    
    //Compares new node with current node, inserts appropriately
    if ((fabs(new_p->xCoordinate - curr_node_data_head->xCoordinate)<EPSILON) && (fabs(new_p->yCoordinate - curr_node_data_head->yCoordinate)<EPSILON)){       
         curr_nodekd->datakd = insert_at_foot(curr_nodekd->datakd, new_p);
     }    
    else if (d==0){
        if (new_p->xCoordinate < curr_node_data_head->xCoordinate) 
            curr_nodekd->left = insert_record(curr_nodekd->left, new_p, depth+1); 
        else
            curr_nodekd->right = insert_record(curr_nodekd->right, new_p, depth+1);
    }
    else{
        if (new_p->yCoordinate < curr_node_data_head->yCoordinate) 
            curr_nodekd->left = insert_record(curr_nodekd->left, new_p, depth+1); 
        else
            curr_nodekd->right = insert_record(curr_nodekd->right, new_p, depth+1);    
        
    }
    return curr_nodekd; 
} 



//inserts a node into the tree
void insert_to_tree(tree t, record_t *new_p){
    if (t == NULL){
        printf("Error tree pointer is null\n");
        exit(EXIT_FAILURE);
    }
    t->root = insert_record(t->root, new_p, 0);
}



//makes a new tree
tree new_tree(){
    tree t = malloc(sizeof(*t));
    assert(t);
    t->root = NULL;
    return t;
} 



//frees the tree
void freetree(nodekd n){
    if (n != NULL){
        free_list_structs(n->datakd);
        free_list(n->datakd);
        freetree(n->left);
        freetree(n->right);
        free(n);   
    }
}


/* Map 1 - Finds the closest node coordinate from the key coordinate */
void nearest(nodekd curr_node, inkey1_t key, int flag, nodekd *closest, double *best_distance_squared, int *comparisons){ 
    
    double curr_distance_squared, xy_distance, xy_distance_squared;
    if (!curr_node) return;
    
    *comparisons = *comparisons +1;
    
    //finds the current distance between key coordinate and search coordinate
    curr_distance_squared = dist1(curr_node, key, MAXDIMENSION);
    
    
    //finds the distance between either x or y to key coordinate, and square it
    if (flag == 0){
        xy_distance = curr_node->datakd->head->data->xCoordinate - key.x;
    }
    else{
        xy_distance = curr_node->datakd->head->data->yCoordinate - key.y;
    }
    xy_distance_squared = xy_distance * xy_distance;
 
    
    //if there is no current closest business or the current distance is smaller than best distance, replace best
    if (!*closest || curr_distance_squared < *best_distance_squared) {
        *best_distance_squared = curr_distance_squared;
        *closest = curr_node;
    }
 
    if (sqrt(*best_distance_squared) < EPSILON) return;

    
    if (++flag >= MAXDIMENSION) flag = 0;
 
    //if curr_distance_squared > best_distance_squared, proceed down either side, else proceed down both sides.
    nearest(xy_distance > 0 ? curr_node->left : curr_node->right, key, flag, closest, best_distance_squared, comparisons);
    if (xy_distance_squared >= *best_distance_squared) return;
    nearest(xy_distance > 0 ? curr_node->right : curr_node->left, key, flag, closest, best_distance_squared, comparisons);
}



/* Map 1 - finds the current squared distance between key coordinate and search coordinate */
double dist1(nodekd curr_node, inkey1_t key, int flag){
    double distance, curr_distance_squared = 0;
    while (flag--) {
        if (flag == 0){
            distance = curr_node->datakd->head->data->xCoordinate - key.x;
        }
        else{
            distance = curr_node->datakd->head->data->yCoordinate - key.y;
        }
        curr_distance_squared += distance * distance;
    }
    return curr_distance_squared;
}



/* Map 2 - finds all the nodes within given radius and prints it to outfile */
void within_radius(nodekd curr_node, inkey2_t key, int flag, FILE *out_file, int *comparisons, int *found, char *xcoord, char *ycoord, char *radius){

    double curr_distance_squared, xy_distance, xy_distance_squared;
    
    if (!curr_node) return;
    
    *comparisons = *comparisons +1;
    
    curr_distance_squared = dist_2(curr_node, key, MAXDIMENSION);
    
    
    //prints out if node within radius
    if (curr_distance_squared<=key.r*key.r){
        *found = *found +1;
        printlist_map2(xcoord, ycoord, radius, curr_node->datakd, out_file);
    }
    
    
    //finds the distance between either x or y to key coordinate, and square it
    if (flag == 0){
        xy_distance = curr_node->datakd->head->data->xCoordinate - key.x;
    }
    else{
        xy_distance = curr_node->datakd->head->data->yCoordinate - key.y;
    }
    xy_distance_squared = xy_distance * xy_distance;
 
    if (++flag >= MAXDIMENSION) flag = 0;
    
    
    //if curr_distance_squared > radius squared, proceed down either side, else proceed down both sides.
    within_radius(xy_distance > 0 ? curr_node->left : curr_node->right, key, flag, out_file, comparisons, found, xcoord, ycoord, radius);
    if (xy_distance_squared > key.r*key.r) return;
    within_radius(xy_distance > 0 ? curr_node->right : curr_node->left, key, flag, out_file, comparisons, found, xcoord, ycoord, radius);
}



/* Map 2 - finds the current squared distance between key coordinate and search coordinate */
double dist_2(nodekd curr_node, inkey2_t key, int flag){
    double distance, curr_distance_squared = 0;
    while (flag--) {
        if (flag == 0){
            distance = curr_node->datakd->head->data->xCoordinate - key.x;
        }
        else{
            distance = curr_node->datakd->head->data->yCoordinate - key.y;
        }
        curr_distance_squared += distance * distance;
    }
    return curr_distance_squared;
}




/* Recycled code from Assignmnent 1 */

//Reads given csv file into kd tree
void read_file_into_dict(tree t, FILE *fp){
    record_t *record;
    char line[MAXLINE], field[MAXFIELD];
    int field_length = 0, i = 0, field_num = 0;
    int first_line = 1, in_quote = 0;
    
    //Reads the file line-by-line and seperates the fields
    while (fgets(line, MAXLINE, fp)) {
        if (first_line) {
            first_line = 0;
            continue;
        }
        record = malloc(sizeof(record_t));
        assert(record);
        field_num = 0, i = 0;
        
        while (line[i]){
            field[field_length++] = line[i];
            
            //Skips over one double quote
            if (line[i] == '"' && line[i+1] == '"'){
                i++;
            }
            
            //Switch to indicate the start and end of taking in field characters
            else if (line[i] == '"' && line[i+1] != '"') {
                in_quote = !in_quote;
                field_length--;
            } 
            
            //Inserts completed field into record struct
            else if (!in_quote && (line[i] == ',' || line[i] == '\n')) {
                field[field_length - 1] = 0;
                field_to_struct(field_num, field, record);
                field_num++;
                field_length = 0;
            }
            i++;           
        }
        //inserts last field, then inserts struct into linked list
        char *loc = strtok(field, ")");
        record->location = strdup(loc);        
        assert(record->location);
        insert_to_tree(t, record);
    }
}



//Indicates where each field belongs in the struct
void field_to_struct(int field_num, char *field, record_t *record) {
    if (field_num == 0) {
        record->censusYear = atoi(field);
    }
    else if (field_num == 1){
        record->blockID = atoi(field);
    }
    else if (field_num == 2){
        record->propertyID = atoi(field);
    }
    else if (field_num == 3){
        record->basePropertyID = atoi(field);
    }
    else if (field_num == 4){
        record->clueSmallArea = strdup(field);
        assert(record->clueSmallArea);
    }
    else if (field_num == 5){
        record->tradingName = strdup(field);
        assert(record->tradingName);
    } 
    else if (field_num == 6){
        record->industryCode = atoi(field);
    }
    else if (field_num == 7){
        record->industryDescription = strdup(field);
        assert(record->industryDescription);
    }
    else if (field_num == 8){
        record->xCoordinate = atof(field);
    }
    else if (field_num == 9){
        record->yCoordinate = atof(field);
    }
}