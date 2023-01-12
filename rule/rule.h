#ifndef RULE_
#define RULE_

#include <stdio.h>

typedef struct _Rule Rule;


extern Rule *rule_create();

extern void rule_destroy(Rule *r);


extern int rule_read_line(int *nb_field, int **arr_field, FILE *stream);

extern Rule *rule_read_block(Rule *r, FILE *stream);


extern void rule_print_line(int *arr, size_t size, FILE *stream);

extern void rule_print_block(int *facts, size_t factsSize, int *cons, size_t consSize, FILE *stream);


extern void rule_display(Rule *r);

#endif