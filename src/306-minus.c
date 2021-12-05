#include <stdbool.h>
#include <stdio.h>

// checks if each element from set1 is not as well in set2, if not, it is added to new set min_set
set_t* cmd_minus(set_t* set1, set_t* set2) {
    set_t *min_set = empty_set();
    for (size_t i = 0; i < set1->number_of_elements; i++) {
        if (!is_element_in_set(set1->elements[i], set2))
            add_element_to_set(set1->elements[i], &min_set);
    }
    return min_set;
}