#include <stdbool.h>
#include <stdio.h>

// goes through universe and checks whether each element in set is in universe, if not, it is added to new set comp_set
set_t* cmd_complement(set_t* universe, set_t* set) {
    set_t *comp_set = empty_set();
    for (size_t i = 0; i < universe->number_of_elements; i++) {
        if (!is_element_in_set(universe->elements[i], set)) {
            add_element_to_set(universe->elements[i], &comp_set);
        }
    }
    return comp_set;
}