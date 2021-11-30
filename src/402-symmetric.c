//
// Created by jiris on 30/11/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool Cmd_symm(rel_t *rel1) {
    bool found;
    for (size_t i = 0; i < rel1->number_of_pairs; i++) {
        found = false;
        for (size_t j = i; j < rel1->number_of_pairs; j++) {
            if (rel1->pairs[i]->left == rel1->pairs[j]->right && rel1->pairs[i]->right == rel1->pairs[j]->left) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}
