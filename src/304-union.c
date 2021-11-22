//
// Created by Štefan Pekník on 19.11.2021.
//

#include <stdbool.h>
#include <stdio.h>


set_t* cmd_union (set_t *set1, set_t *set2) {
    set_t* setu = set1;
    for (size_t i = 0; i < set2->number_of_elements; i++) {
        if (!is_element_in_set(set2->elements[i], setu))
            add_element_to_set(set2->elements[i], &setu);
    }
    return setu;
}