//
// Created by Štefan Pekník on 19.11.2021.
//

#include <stdbool.h>
#include <stdio.h>

set_t* Cmd_intersect (set_t *set1, set_t *set2) {
    set_t* seti = set1;
    for (int i = 0; i < (int) set1->number_of_elements; i++) {
        for (int j = 0; j < (int) set2->number_of_elements; j++) {
            if (set1->elements[i] == set2->elements[j]) {
                expand_set(set1->elements[i], seti);
            }
        }
    }
    return seti;
}