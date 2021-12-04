//
// Created by Štefan Pekník on 04.12.2021.
//


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

rel_t* cmd_closure_sym(rel_t* rel) {
    rel_t* sym_rel = empty_rel();
    for (size_t i = 0; i < rel->number_of_pairs; i++) {
        pair_t *pair = get_pair(rel->pairs[i]->right, rel->pairs[i]->left);
        if (pair == NULL) {
            throw_chars("could not allocate memory for pair\n");
            return false;
        }
        if (!is_pair_in_rel(pair, rel))
            add_pair_to_rel(pair, &sym_rel);
    }
    return sym_rel;
}