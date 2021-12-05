#include <stdbool.h>
#include <stdio.h>

// takes pair and finds other pair by rule: a right element from pair1 equals a left element from pairN;
// and checks whether there is also a pair made of a left element from pair1 and a right element from pairN
bool cmd_transitive(rel_t* rel) {
	for (size_t i = 0; i < rel->number_of_pairs; i++) {
		for (size_t j = 0; j < rel->number_of_pairs; j++) {
			if (rel->pairs[i]->right == rel->pairs[j]->left) {
				pair_t* pair = get_pair(rel->pairs[i]->left, rel->pairs[j]->right);
				if (pair == NULL) {
					throw_chars("could not allocate memory for pair\n");
					return false;
				}
				if (!is_pair_in_rel(pair, rel))
					return false;
			}
		}
	}
	return true;
}
