#include "rule.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "rule.inc"

//--------CREATE / DESTROY---------
Rule *rule_create() {
    Rule *r = malloc(sizeof(Rule));

    r->facts = calloc(1, sizeof(int));
    r->cons = calloc(1, sizeof(int));

    if (!r->facts || !r->cons) return NULL;

    r->nb_facts = 0;
    r->nb_cons = 0;
    
    return r;
}

void rule_destroy(Rule *r) {
    free(r->facts);
    free(r->cons);
    free(r);
}


//--------RULE READING FROM FILE-------
/**
 *  @return Number of line read
 */
int rule_read_line(int *nb_field, int **arr_field, FILE *stream) {
    *nb_field = 0;
    int i;
    char c;
    bool end_of_line = false;
    while (!end_of_line) {
        c = fgetc(stream);
        if (feof(stream) || (c == '\n' && *nb_field != 0)) end_of_line = true;
        else if (strchr("0123456789", c)) {

            fseek(stream, -sizeof(char), SEEK_CUR);
            fscanf(stream, "%d", &i);

            *nb_field += 1;
            int *tmp_ptr = reallocarray(*arr_field, *nb_field, sizeof(int));
            if (tmp_ptr) {
                *arr_field = tmp_ptr;
                (*arr_field)[(*nb_field)-1] = i;
            } else return 0;
        }
    }
    return 1;
}

Rule *rule_read_block(Rule *r, FILE *stream) {
    rule_read_line(&(r->nb_facts), &(r->facts), stream);
    rule_read_line(&(r->nb_cons), &(r->cons), stream);
    return r;
}


//---------RULE PRINTING ON FILE---------
void rule_print_line(int *arr, size_t size, FILE *stream) {
    for (size_t i = 0; i < size-1; i++) {
        fprintf(stream, "%d ", arr[i]);
    }
    fprintf(stream, "%d\n", arr[size-1]);
}

void rule_print_block(int *facts, size_t factsSize, int *cons, size_t consSize, FILE *stream) {
    rule_print_line(facts, factsSize, stream);
    rule_print_line(cons, consSize, stream);
    fputs("\n", stream);
}


//---------RULE DISPLAYING---------
void rule_display(Rule *r) {
    printf("Faits (%d) :\t\t", r->nb_facts);
    for (int i = 0; i < r->nb_facts; i++) {
        printf("%d ", r->facts[i]);
    }
    printf("\nConséquences (%d) :\t", r->nb_cons);
    for (int j = 0; j < r->nb_cons; j++) {  
        printf("%d ", r->cons[j]);
    }
    printf("\n");
}