#include <stdbool.h>
#include <stdio.h>

// takes pair and finds other pair by rule: a right element from pair1 equals a left element from pairN;
// and checks whether there is also a pair made of a left element from pair1 and a right element from pairN,
// if not, the pair is added to the rel
// and the process goes again to check, whether the newly added pairs have its transitive pairs
rel_t* cmd_closure_trans(rel_t* rel) {
    int c = 0;
    do {
        c = 0;
        for (size_t i = 0; i < rel->number_of_pairs; i++) {
            for (size_t j = 0; j < rel->number_of_pairs; j++) {
                if (rel->pairs[i]->right == rel->pairs[j]->left) {
                    pair_t* pair = get_pair(rel->pairs[i]->left, rel->pairs[j]->right);
                    if (pair == NULL) {
                        throw_chars("could not allocate memory for pair\n");
                        return NULL;
                    }
                    if (!is_pair_in_rel(pair, rel)) {
                        add_pair_to_rel(pair, &rel);
                        c++;
                    }
                }
            }
        }
    } while (c != 0);
    return rel;
}
