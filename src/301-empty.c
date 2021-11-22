//
// Created by Štefan Pekník on 15.11.2021.
//
#include <stdbool.h>
#include <stdio.h>

bool cmd_empty (set_t *set) {
    if (set->number_of_elements == 0)
        return true;
    return false;
}
