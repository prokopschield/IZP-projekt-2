//
// Created by Štefan Pekník on 22.11.2021.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>

bool Cmd_reflexive (rel_t* rel) {
    for (size_t i = 0; i < rel->number_of_pairs; i++) {
        if (!is_pair_in_rel(get_pair(rel->pairs[i]->left, rel->pairs[i]->left), rel))
            return false;
        if (!is_pair_in_rel(get_pair(rel->pairs[i]->right, rel->pairs[i]->right), rel))
            return false;
    }
    return true;
}