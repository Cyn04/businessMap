/* Cynthia Joseph (938358) - Assignment 2 COMP20003
*/

typedef struct{
    double x;
    double y;
} inkey1_t;

typedef struct{
    double x;
    double y;
    double r;
} inkey2_t;


typedef struct nd{
    list_t *datakd;
    struct nd *left;
    struct nd *right;
} nodekd_t;

typedef nodekd_t *nodekd;

typedef struct {
    nodekd root;
} tree_t;  


typedef tree_t *tree;

nodekd new_node(record_t *record);
nodekd insert_record(nodekd curr_nodekd, record_t *new_p, int depth);
void insert_to_tree(tree t, record_t *new_p);
tree new_tree();
void freetree(nodekd n);

void read_file_into_dict(tree t, FILE *fp);
void field_to_struct(int field_num, char *field, record_t *record);
void nearest(nodekd curr_node, inkey1_t key, int flag, nodekd *closest, double *best_distance_squared, int *comparisons);
double dist1(nodekd curr_node, inkey1_t key, int dim);
void within_radius(nodekd curr_node, inkey2_t key, int flag, FILE *out_file, int *comparisons, int *found, char *xcoord, char *ycoord, char *radius);
double dist_2(nodekd curr_node, inkey2_t key, int dim);