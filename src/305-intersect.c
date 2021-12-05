#include <stdbool.h>
#include <stdio.h>

// checks whether each element from set1 is in set_B as well, if it is, it is added to new set inter_set
set_t* cmd_intersect(set_t* set_A, set_t* set_B) {
    set_t *inter_set = empty_set();
    for (size_t i = 0; i < set_A->number_of_elements; i++) {
        if (is_element_in_set(set_A->elements[i], set_B)) {
            add_element_to_set(set_A->elements[i], &inter_set);
        }
    }
    return inter_set;
}