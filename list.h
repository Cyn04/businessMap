/* Cynthia Joseph (938358) - Assignment 2 COMP20003
*/
#define MAXDIMENSION 2

typedef struct{
    int censusYear;
    int blockID; 
    int propertyID;
    int basePropertyID; 
    char *clueSmallArea;
    char *tradingName;
    int industryCode;
    char *industryDescription;
    double xCoordinate;
    double yCoordinate;
    char *location; 
} record_t;



/* =====================================================================
   listops.c
   ================================================================== */
typedef struct node node_t;

typedef record_t *data_t;

struct node {
	data_t data;
	node_t *next;
};

typedef struct {
	node_t *head;
	node_t *foot;
} list_t;

list_t *make_empty_list(void);
void free_list(list_t *list);
list_t *insert_at_foot(list_t *list, data_t value);


/* =====================================================================
   Program written by Alistair Moffat, as an example for the book
   "Programming, Problem Solving, and Abstraction with C", Pearson
   Custom Books, Sydney, Australia, 2002; revised edition 2012,
   ISBN 9781486010974.

   See http://people.eng.unimelb.edu.au/ammoffat/ppsaa/ for further
   information.

   Prepared December 2012 for the Revised Edition.
   ================================================================== */


void printlist(char *x, char *y, list_t *list, FILE *out_file);
void printlist_map2(char *x, char *y, char *r, list_t *list, FILE *out_file);
void free_list_structs(list_t *list);