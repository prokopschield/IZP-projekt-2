//
// Created by jiris on 30/11/2021.
//
#include <stdbool.h>
#include <stdio.h>

bool Cmd_function(rel_t *rel, set_t* universe){
    for (size_t i = 0; i < rel->number_of_pairs; i++) {
        for (size_t j = 0; j < universe->number_of_elements; j++) {
            if (rel->pairs[i]->right != universe->elements[j]) {
                if (is_pair_in_rel(get_pair(rel->pairs[i]->left, universe->elements[j]), rel))
                    return false;
            }
        }
    }
    return true;
}
