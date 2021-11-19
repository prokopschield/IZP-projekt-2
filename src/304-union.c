//
// Created by Štefan Pekník on 19.11.2021.
//

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void Command_union (set_t *set1, set_t *set2) {
    for (int i = 0; i < set1->number_of_elements; i++) {
        printf("%s ", set1->elements[i]);
    }

    bool print;
    for (int i = 0; i < set2->number_of_elements; i++) {
        print = true;
        for (int j = 0; j < set1->number_of_elements; j++) {
            if (strcmp(set2->elements[i], set1->elements[j])) {
                print = false;
                break;
            }
        }
        if (print)
            printf("%s ", set2->elements[i]);
    }
}