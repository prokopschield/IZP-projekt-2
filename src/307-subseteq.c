//
// Created by Štefan Pekník on 19.11.2021.
//


#include <stdbool.h>
#include <stdio.h>

bool Cmd_subseteq(set_t *set1, set_t *set2) {
    for (int i = 0; i < (int)set2->number_of_elements; ++i) {
        if (!is_element_in_set(set2->elements[i], set1))
            return false;
    }
    return true;
}