//
// Created by jiris on 30/11/2021.
//
#include <stdbool.h>
#include <stdio.h>

bool Cmd_transitive(rel_t* rel) {
	for (size_t i = 0; i < rel->number_of_pairs; i++) {
        for (size_t j = 0; j < rel->number_of_pairs; j++) {
            if (rel->pairs[i]->right == rel->pairs[j]->left) {
                if (!is_pair_in_rel(get_pair(rel->pairs[i]->left, rel->pairs[j]->right), rel))
                    return false;
            }
        }
	}
	return true;
}
