//
// Created by Štefan Pekník on 04.12.2021.
//


#include <stdbool.h>
#include <stdio.h>

rel_t* cmd_closure_trans(rel_t* rel) {
    rel_t* trans_rel = empty_rel();
    int c = 0;
    do {
        c = 0;
        for (size_t i = 0; i < rel->number_of_pairs; i++) {
            for (size_t j = 0; j < rel->number_of_pairs; j++) {
                if (rel->pairs[i]->right == rel->pairs[j]->left) {
                    pair_t* pair = get_pair(rel->pairs[i]->left, rel->pairs[j]->right);
                    if (pair == NULL) {
                        throw_chars("could not allocate memory for pair\n");
                        return NULL;
                    }
                    if (!is_pair_in_rel(pair, rel)) {
                        add_pair_to_rel(pair, &trans_rel);
                        c++;
                    }
                }
            }
        }
    } while (c != 0);
    return trans_rel;
}