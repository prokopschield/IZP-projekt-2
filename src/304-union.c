#include <stdbool.h>
#include <stdio.h>

// creates new set uni_set which contains all elements from set_A,
// goes through all elements in set_B and
// adds every new element (element which is not in set uni_set) to set uni_set
set_t* cmd_union(set_t* set_A, set_t* set_B) {
    set_t *uni_set = set_A;
    for (size_t i = 0; i < set_B->number_of_elements; i++) {
        if (!is_element_in_set(set_B->elements[i], uni_set))
            add_element_to_set(set_B->elements[i], &uni_set);
    }
    return uni_set;
}