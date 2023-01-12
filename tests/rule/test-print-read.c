#include <stdlib.h>
#include <stdio.h>

#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>

#include <rule.h>

#include <rule.inc>

int main(void) {

    //FILE *f = fopen("rules.txt", "w+");
    FILE *f = tmpfile();
    if (f) {

        int facts1[] = {1, 25, 3, 786, 24, 65};
        int cons1[] = {14, 56, 8};
        size_t sizeFacts1 = sizeof facts1 / sizeof(int);
        size_t sizeCons1 = sizeof cons1 / sizeof(int);
        rule_print_block(facts1, 6, cons1, 3, f);

        int facts2[] = {25, 678, 5, 43};
        int cons2[] = {7, 23, 678, 5, 43, 3};
        size_t sizeFacts2 = sizeof facts2 / sizeof(int);
        size_t sizeCons2 = sizeof cons2 / sizeof(int);
        rule_print_block(facts2, 4, cons2, 6, f);

        rewind(f);

        Rule *rule = rule_create();
        rule_read_block(rule, f);
        assert(sizeFacts1 == rule->nb_facts);
        for (size_t i = 0; i < sizeFacts1; i++) {assert(facts1[i] == (rule->facts)[i]);}
        assert(sizeCons1 == rule->nb_cons);
        for (size_t i = 0; i < sizeCons1; i++) {assert(cons1[i] == (rule->cons)[i]);}
        rule_display(rule);

        rule_read_block(rule, f);
        assert(sizeFacts2 == rule->nb_facts);
        for (size_t i = 0; i < sizeFacts2; i++) {assert(facts2[i] == (rule->facts)[i]);}
        assert(sizeCons2 == rule->nb_cons);
        for (size_t i = 0; i < sizeCons2; i++) {assert(cons2[i] == (rule->cons)[i]);}
        rule_display(rule);
        rule_destroy(rule);
    }
    fclose(f);

    return EXIT_SUCCESS;
}