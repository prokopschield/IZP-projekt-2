//
// Created by Štefan Pekník on 22.11.2021.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool cmd_reflexive(set_t* universe, rel_t* rel) {
    for (size_t i = 0; i < universe->number_of_elements; i++) {
        pair_t* pair = get_pair(universe->elements[i], universe->elements[i]);
        if (pair == NULL) {
            throw_chars("could not allocate memory for pair\n");
            return false;
        }
        if (!is_pair_in_rel(pair, rel))
            return false;
    }
    return true;
}