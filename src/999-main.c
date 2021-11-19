#include <stdio.h>

int main() {



    set_t set1 = { 0, 1, NULL };



//    printf("%s", set1.elements[0]->str.data);

    if(Command_empty(&set1))
        puts("true");
    else
        puts("false");

    Command_card(&set1);

	// Remember to free everything!!!
	mem_free_everything();
}
