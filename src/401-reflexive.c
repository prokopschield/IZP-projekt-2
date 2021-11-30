//
// Created by jiris on 30/11/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool Cmd_reflx (rel_t *rel1) {
    size_t c = 0;

    for (size_t i = 0; i < rel1->number_of_pairs; i++) {
        if(rel1->pairs[i]->left == rel1->pairs[i]->right){
            c++;
        }
    }
    if(c == rel1->number_of_pairs) return true;
    return false;

}



