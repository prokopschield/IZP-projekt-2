#include <stdbool.h>
#include <stdio.h>

// takes a left element from a pair
// and checks whether there is not any other pair containing the left element from the pair with different right element
bool cmd_function(set_t* universe, rel_t* rel) {
	for (size_t i = 0; i < rel->number_of_pairs; i++) {
		for (size_t j = 0; j < universe->number_of_elements; j++) {
			if (rel->pairs[i]->right != universe->elements[j]) {
				pair_t* pair = get_pair(rel->pairs[i]->left, universe->elements[j]);
				if (pair == NULL) {
					throw_chars("could not allocate memory for pair\n");
					return false;
				}
				if (is_pair_in_rel(pair, rel))
					return false;
			}
		}
	}
	return true;
}
