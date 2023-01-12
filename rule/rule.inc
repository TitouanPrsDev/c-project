#ifndef RULE_I_
#define RULE_I_

struct _Rule {
    int nb_facts;
    int *facts;
    int nb_cons;
    int *cons;
};

#endif