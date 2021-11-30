//
// Created by Štefan Pekník on 22.11.2021.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>

bool contains_element(element_t** elements ,element_t* element, size_t num_of_els) {
    for (size_t i = 0; i < num_of_els; i++) {
        if (elements[i] == element) return true;
    }
    return false;
}

bool Cmd_reflexive (rel_t* rel) {
    element_t** elements = malloc(sizeof(element_t*) * rel->number_of_pairs * 2);
    size_t num_of_els = 0;

    for (size_t i = 0; i < rel->number_of_pairs; i++) {
        if (contains_element(elements, rel->pairs[i]->left, num_of_els)) {
            elements[num_of_els] = rel->pairs[i]->left;
            num_of_els++;
        }
        if (contains_element(elements, rel->pairs[i]->right, num_of_els)) {
            elements[num_of_els] = rel->pairs[i]->right;
            num_of_els++;
        }
    }

    size_t counter = 0;
    for (size_t i = 0; i < rel->number_of_pairs; i++) {
        if (rel->pairs[i]->left == rel->pairs[i]->right)
            counter++;
    }

    if (num_of_els == counter)
        return true;

    return false;
}