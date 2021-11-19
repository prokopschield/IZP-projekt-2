//
// Created by Štefan Pekník on 19.11.2021.
//

#include <stdbool.h>
#include <stdio.h>

bool Cmd_equals (set_t *set1, set_t *set2) {
    if (Cmd_subset (set1, set2) && Cmd_subset (set2, set1))
        return true;
    else
        return false;
}