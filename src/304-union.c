#include <stdbool.h>
#include <stdio.h>

// creates new set uni_set which contains all elements from set1,
// goes through all elements in set2 and
// adds every new element (element which is not in set uni_set) to set uni_set
set_t* cmd_union(set_t* set1, set_t* set2) {
    set_t *uni_set = set1;
    for (size_t i = 0; i < set2->number_of_elements; i++) {
        if (!is_element_in_set(set2->elements[i], uni_set))
            add_element_to_set(set2->elements[i], &uni_set);
    }
    return uni_set;
}