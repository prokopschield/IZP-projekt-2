#include <stdbool.h>
#include <stdio.h>

// checks if every element in the universe has its own refeflexive pair (e.g. element a : pair (a, a)) included in the rel
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
