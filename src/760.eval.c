#include <stdbool.h>
#include <string.h>

set_t* get_universe(array_t* lines);

extern char* eval(array_t* lines, line_t* line);

typedef struct arg_A_t {
	set_t* A;
	size_t N;
} arg_A_t;

extern bool arg_A_val(arg_A_t* res, array_t* lines, size_t_array_t* args);

char* eval(array_t* lines, line_t* line) {
	if ((line->line_type == line_type_cmd) && line->val_cmd) {
		cmd_t* cmd = line->val_cmd;
		char* cmd_s = (char*) cmd->cmd.data;
		size_t_array_t* args = (size_t_array_t*) cmd->args;
		if (args->len) {
			if (!strcmp(cmd_s, "empty")) {
				arg_A_t a = { NULL, 0 };
				if (arg_A_val(&a, lines, args)) {
					return cmd_empty(a.A) ? "true" : "false";
				}
			}
		}
	}
	return NULL;
}

set_t* get_universe(array_t* lines) {
	line_t* universe_line = lines->items[1];
	if (!universe_line) {
		return empty_set();
	}
	set_t* universe = universe_line->val_set;
	if (!universe) {
		return empty_set();
	}
	const array_t* elements = all_elements();
	if (universe->number_of_elements != elements->len) {
		for (size_t i = 0; i < elements->len; ++i) {
			add_element_to_set(elements->items[i], &universe);
		}
		universe_line->val_set = universe;
	}
	return universe;
}

void invalid_argument(line_t* line) {
	throw_chars("Invalid argument: ");
	line_print(line, stderr);
}

bool arg_A_val(arg_A_t* res, array_t* lines, size_t_array_t* args) {
	if (args->len < 1) {
		throw_error("Insufficient (%ld) arguments for empty()", args->len);
		return false;
	}
	line_t* arg_1 = line_get(lines, args->items[1]);
	if (!arg_1) {
		arg_1 = line_get(lines, 0);
	}
	eval(lines, arg_1);
	res->A = arg_1->val_set ? arg_1->val_set : (set_t*) arg_1->val_rel;
	if (!res->A) {
		return true;
	} else {
		invalid_argument(arg_1);
		return false;
	}
}
