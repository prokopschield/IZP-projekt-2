//
// Created by Štefan Pekník on 19.11.2021.
//

#include <stdbool.h>
#include <stdio.h>

bool cmd_subset(set_t* set_A, set_t* set_B) {
    if (set_A == set_B)
        return false;
    else if (cmd_subseteq(set_A, set_B))
        return true;
    else
        return false;
}