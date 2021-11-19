//
// Created by Štefan Pekník on 15.11.2021.
//
#include <stdbool.h>
#include <stdio.h>

void Cmd_empty (set_t *set) {
    if (set->number_of_elements == 0)
        printf("true\n");
    else
        printf("false\n");
}
