#include <stdbool.h>
#include <stdio.h>

// checks if every pair in the rel does not have its symmetric pair in the rel (e.g. (a, b) !-> (b, a)),
// if any pair has its symmetric pair, returns false,
// else returns true
bool cmd_antisymmetric(rel_t* rel) {
	for (size_t i = 0; i < rel->number_of_pairs; i++) {
		if (rel->pairs[i]->left != rel->pairs[i]->right) {
            pair_t* pair = get_pair(rel->pairs[i]->right, rel->pairs[i]->left);
            if (pair == NULL) {
                throw_chars("could not allocate memory for pair\n");
                return false;
            }
			if (is_pair_in_rel(pair, rel))
				return false;
		}
	}
	return true;
}
