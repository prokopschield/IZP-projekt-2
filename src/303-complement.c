//
// Created by Štefan Pekník on 22.11.2021.
//

#include <stdbool.h>
#include <stdio.h>

set_t* Cmd_complement(set_t* universe, set_t* set) {
    set_t* setc = empty_set();
    for (int i = 0; i < (int)universe->number_of_elements; i++) {
        if (!is_element_in_set(universe->elements[i], set)) {
            add_element_to_set(universe->elements[i], &set);
        }
    }
    return setc;
}