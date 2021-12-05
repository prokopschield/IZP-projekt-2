#include <stdbool.h>
#include <stdio.h>

// checks whether each element from set1 is in set2 as well, if it is, it is added to new set inter_set
set_t* cmd_intersect(set_t* set1, set_t* set2) {
    set_t *inter_set = empty_set();
    for (size_t i = 0; i < set1->number_of_elements; i++) {
        if (is_element_in_set(set1->elements[i], set2)) {
            add_element_to_set(set1->elements[i], &inter_set);
        }
    }
    return inter_set;
}