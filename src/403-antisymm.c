//
// Created by jiris on 30/11/2021.
//

#include <stdbool.h>
#include <stdio.h>

bool Cmd_antisymm(rel_t *rel1){

    bool x;
    for (size_t i = 0; i < rel1->number_of_pairs; i++) {
        x = false;
        if (rel1->pairs[i]->left == rel1->pairs[i]->right) {
            x = true;
        }
        else {
            for (size_t j = i; j < rel1->number_of_pairs; j++) {
                if ((rel1->pairs[i]->left == rel1->pairs[j]->right && rel1->pairs[i]->right == rel1->pairs[j]->left)) {
                    x = false;
                    break;
                }
            }
        }
        if (!x) {
            return false;
        }
    }
    return true;
}