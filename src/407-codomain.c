#include <stdbool.h>
#include <stdio.h>

set_t* cmd_codomain(rel_t *rel){
    set_t* setcodom = empty_set();
    for (size_t i = 0; i < rel->number_of_pairs; i++) {
        if (!is_element_in_set(rel->pairs[i]->right, setcodom)){
            add_element_to_set(rel->pairs[i]->right, &setcodom);
        }
    }                        
    return setcodom;
}
