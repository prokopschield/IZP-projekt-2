//
// Created by Štefan Pekník on 04.12.2021.
//

#include <stdbool.h>
#include <stdio.h>

rel_t* cmd_closure_ref(set_t* universe, rel_t* rel) {
    rel_t* ref_rel = empty_rel();
    for (size_t i = 0; i < universe->number_of_elements; i++) {
        pair_t* pair = get_pair(universe->elements[i], universe->elements[i]);
        if (pair == NULL) {
            throw_chars("could not allocate memory for pair\n");
            return NULL;
        }
        if (!is_pair_in_rel(pair, rel))
            add_pair_to_rel(pair, &ref_rel);
    }
    return ref_rel;
}