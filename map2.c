/* Cynthia Joseph (938358) - Assignment 2 COMP20003
Map 2 - finds all the CLUE records for each given location coordinate within a specified radius.
This program reads CLUE records from a csv file, inserts it into a linked list, then inserts it 
into a kd tree. The program accepts key inputs and returns the location of businesses within
the given radius of the key inputs.
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
    inkey2_t key;
    char xcoord[MAXINPUT];
    char ycoord[MAXINPUT];
    char radius[MAXINPUT];
    while(scanf("%s %s %s",xcoord, ycoord, radius)== 3){
        key.x = atof(xcoord);
        key.y = atof(ycoord);
        key.r = atof(radius);
        int visited = 0;
        int found = 0;
        int flag = 0;
        within_radius(root, key, flag, out_file, &visited, &found, xcoord, ycoord, radius); 
        printf("%s %s %s --> %d\n", xcoord, ycoord, radius, visited);
        if (found == 0){
            fprintf(out_file, "%s %s %s --> NOTFOUND\n", xcoord, ycoord, radius);
        }
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