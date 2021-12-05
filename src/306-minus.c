#include <stdbool.h>
#include <stdio.h>

// checks if each element from set_A is not as well in set_B, if not, it is added to new set min_set
set_t* cmd_minus(set_t* set_A, set_t* set_B) {
    set_t *min_set = empty_set();
    for (size_t i = 0; i < set_A->number_of_elements; i++) {
        if (!is_element_in_set(set_A->elements[i], set_B))
            add_element_to_set(set_A->elements[i], &min_set);
    }
    return min_set;
}