//
// Created by jiris on 30/11/2021.
//
#include <stdbool.h>
#include <stdio.h>

bool Cmd_transitive(rel_t* rel1) {
	for (size_t i = 0; i < rel1->number_of_pairs; i++) {
		if (!is_pair_in_rel(get_pair(rel1->pairs[i]->left, rel1->pairs[i]->left), rel1))
			return false;
		if (!is_pair_in_rel(get_pair(rel1->pairs[i]->right, rel1->pairs[i]->right), rel1))
			return false;
	}
	return true;
}
