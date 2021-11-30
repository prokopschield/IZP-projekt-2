//
// Created by jiris on 30/11/2021.
//
#include <stdbool.h>
#include <stdio.h>

bool Cmd_fun(rel_t *rel1){
    if(Cmd_reflx(rel1) == true && Cmd_symm(rel1) == true && Cmd_tran(rel1) == true) {
        bool found;
        for (size_t i = 0; i < rel1->number_of_pairs; i++) {
            found = false;
            for (size_t j = 0; j < rel1->number_of_pairs; j++) {
                if (rel1->pairs[i]->left == rel1->pairs[j]->left && rel1->pairs[i]->right != rel1->pairs[j]->right) {
                    found = true;
                    break;
                }
            }
            if(found) {
                return false;
            }
        }
        return true;
    }
    else{
        return false;
    }
}
