#include <stdbool.h>
#include <stdio.h>

bool cmd_symmetric(rel_t* rel) { 
	for (size_t i = 0; i < rel->number_of_pairs; i++) { 
		pair_t* pair = get_pair(rel->pairs[i]->right, rel->pairs[i]->left);
		if (pair == NULL) { 
			throw_chars("could not allocate memory for pair\n");
			return false;
		}
		if (!is_pair_in_rel(pair, rel))
			return false;
	}
	return true;
}
