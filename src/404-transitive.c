//
// Created by jiris on 30/11/2021.
//
#include <stdbool.h>
#include <stdio.h>

bool find_pair(rel_t* rel1, element_t* left, element_t* right) {
    for (size_t i = 0; i < rel1->number_of_pairs; i++) {
        if (rel1->pairs[i]->left == left && rel1->pairs[i]->right == right)
            return true;
    }
    return false;
}

bool Cmd_tran(rel_t *rel1){
    bool found;

    for (size_t i = 0; i < rel1->number_of_pairs; i++) {
        found = false;
        for (size_t j = 0; j < rel1->number_of_pairs; j++) {
            if (rel1->pairs[i]->right == rel1->pairs[j]->left && find_pair(rel1, rel1->pairs[i]->left, rel1->pairs[j]->right)) {
                found = true;
                break;
            }
        }
        if (!found)
            return false;
    }
    return true;
}
