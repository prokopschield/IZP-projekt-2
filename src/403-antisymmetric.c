//
// Created by jiris on 30/11/2021.
//

#include <stdbool.h>
#include <stdio.h>

bool Cmd_antisymmetric(rel_t *rel){
    for (size_t i = 0; i < rel->number_of_pairs; i++) {
        if (!(rel->pairs[i]->left == rel->pairs[i]->right)) {
            if (is_pair_in_rel(get_pair(rel->pairs[i]->right, rel->pairs[i]->left), rel))
                return false;
        }
    }
    return true;
}