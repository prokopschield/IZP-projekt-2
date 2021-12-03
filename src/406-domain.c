#include <stdbool.h>
#include <stdio.h>

set_t* cmd_domain(rel_t *rel){
    set_t* setdom = empty_set();
    for (size_t i = 0; i < rel->number_of_pairs; i++) {
        if (!is_element_in_set(rel->pairs[i]->left, setdom)){
            add_element_to_set(rel->pairs[i]->left, &setdom);
        }
    }                        
    return setdom;
}
