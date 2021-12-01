//
// Created by jiris on 30/11/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool Cmd_symmetric(rel_t *rel) {
    for (size_t i = 0; i < rel->number_of_pairs; i++) {
        if (!is_pair_in_rel(get_pair(rel->pairs[i]->right, rel->pairs[i]->left), rel))
            return false;
    }
    return true;
}
