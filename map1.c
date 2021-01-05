/* Cynthia Joseph (938358) - Assignment 2 COMP20003
Map 1 - finds the nearest CLUE record for each given location coordinate.
This program reads CLUE records from a csv file, inserts it into a linked list, then inserts it 
into a kd tree. The program accepts key inputs and returns the location of the nearest businessess.
*/

#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "bst.h"
#define MAXINPUT 129


//Prototypes
FILE *open_read_file(char *file_name);
FILE *open_write_file(char *file_name);



int main(int argc, char *argv[]) { 
    
    //Open files
    char *input_filename = argv[1];
    char *output_filename = argv[2];
    FILE *in_file = open_read_file(input_filename);
    FILE *out_file = open_write_file(output_filename);
    
    //Read input file into kd tree dictionary
    tree t = new_tree();
    read_file_into_dict(t, in_file);
    
    //Search dictionary and prints output
    nodekd root = t->root;
    inkey1_t key;
    char xcoord[MAXINPUT];
    char ycoord[MAXINPUT];
    while(scanf("%s %s", xcoord, ycoord)== 2){
        key.x = atof(xcoord);
        key.y = atof(ycoord);
        int visited = 0; 
        nodekd closest = 0; 
        double best_distance; 
        nearest(root, key, 0, &closest, &best_distance, &visited); 
        printf("%s %s --> %d\n", xcoord, ycoord, visited); 
        printlist(xcoord, ycoord, closest->datakd, out_file);
    }

    //Free everything
    freetree(t->root);
    free(t);
    fclose(in_file);
    fclose(out_file);
    return 0; 
} 



//Opens input file
FILE *open_read_file(char *file_name){
    FILE *fp = fopen(file_name, "r");
    if (!fp) {
        printf("Can't open file\n");
        exit(EXIT_FAILURE);
    }
    return fp;
}



//Opens output file
FILE *open_write_file(char *file_name){
    FILE *fp = fopen(file_name, "w");
    if (!fp) {
        printf("Can't open file\n");
        exit(EXIT_FAILURE);
    }
    return fp;
}