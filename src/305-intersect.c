//
// Created by Štefan Pekník on 19.11.2021.
//

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void Command_intersect (set_t *set1, set_t *set2) {
    for (int i = 0; i < (int) set1->number_of_elements; i++) {
        for (int j = 0; j < (int) set2->number_of_elements; j++) {
            if (strcmp((const char *) set1->elements[i]->str.data, (const char *) set2->elements[j]->str.data)) {
                printf("%s ", set1->elements[i]->str.data);
            }
        }
    }
}