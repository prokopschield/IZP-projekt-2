//
// Created by jiris on 30/11/2021.
//
#include <stdbool.h>
#include <stdio.h>

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
