//
// Created by Štefan Pekník on 19.11.2021.
//

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void Command_union (set_t *set1, set_t *set2) {
    for (int i = 0; i < (int)set1->number_of_elements; i++) {
        printf("%s ", set1->elements[i]->str.data);
    }

    for (int i = 0; i < (int)set2->number_of_elements; i++) {
        bool print = true;
        for (int j = 0; j < (int)set1->number_of_elements; j++) {
        if (set2->elements[i] == set1->elements[j]) {
                print = false;
                break;
            }
        }
        if (print)
            printf("%s ", set2->elements[i]->str.data);
    }
}