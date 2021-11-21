//
// Created by Štefan Pekník on 19.11.2021.
//


#include <stdbool.h>
#include <stdio.h>

set_t* Cmd_minus (set_t *set1, set_t *set2) {
    set_t* setm = empty_set();
    for (int i = 0; i < (int)set1->number_of_elements; i++) {
        bool add = true;
        for (int j = 0; j < (int)set2->number_of_elements; j++) {
            if (set1->elements[i] == set2->elements[j]) {
                add = false;
                break;
            }
        }
        if (add)
            add_element_to_set(set1->elements[i], &setm);
    }
    return setm;
}