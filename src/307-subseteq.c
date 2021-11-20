//
// Created by Štefan Pekník on 19.11.2021.
//


#include <stdbool.h>
#include <stdio.h>

bool Cmd_subseteq(set_t *set1, set_t *set2) {
    int count = 0;
    for (int i = 0; i < (int) set1->number_of_elements; i++) {
        int equals = false;
        for (int j = 0; j < (int) set2->number_of_elements; j++) {
            if (set1->elements[i] == set2->elements[j]) {
                equals = true;
            }
        }
        if (equals) {
            count++;
        }
        else {
            return false;
        }
    }
    if (set1->number_of_elements == set2->number_of_elements) {
        return false;
    }

    return true;
}