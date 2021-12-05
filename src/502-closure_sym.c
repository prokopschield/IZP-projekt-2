#include <stdbool.h>
#include <stdio.h>

// checks if every pair in the rel has its symmetric pair in the rel (e.g. (a, b) -> (b, a)),
// if not, the pair is added to the rel
rel_t* cmd_closure_sym(rel_t* rel) {
    for (size_t i = 0; i < rel->number_of_pairs; i++) {
        pair_t *pair = get_pair(rel->pairs[i]->right, rel->pairs[i]->left);
        if (pair == NULL) {
            throw_chars("could not allocate memory for pair\n");
            return NULL;
        }
        if (!is_pair_in_rel(pair, rel))
            add_pair_to_rel(pair, &rel);
    }
    return rel;
}
