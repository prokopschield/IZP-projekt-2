#include <stdbool.h>
#include <stdio.h>

// checks whether every element from set_A is in set_B as well
bool cmd_subseteq(set_t* set_A, set_t* set_B) {
    for (size_t i = 0; i < set_A->number_of_elements; i++) {
        if (!is_element_in_set(set_A->elements[i], set_B))
            return false;
    }
    return true;
}