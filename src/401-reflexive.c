//
// Created by Štefan Pekník on 22.11.2021.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool Cmd_reflexive(set_t* universe, rel_t* rel) {
    for (size_t i = 0; i < universe->number_of_elements; i++) {
        if (!is_pair_in_rel(get_pair(universe->elements[i], universe->elements[i]), rel))
            return false;
    }
    return true;
}