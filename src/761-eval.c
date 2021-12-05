#include <stdbool.h>
#include <string.h>

evaled_t eval(array_t* lines, line_t* line) {
	evaled_t ret = { 0, 0, NULL, 0 };
	if ((line->line_type == line_type_cmd) && line->val_cmd) {
		cmd_t* cmd = line->val_cmd;
		char* cmd_s = (char*) cmd->cmd.data;
		size_t_array_t* args = (size_t_array_t*) cmd->args;
		if (!strcmp(cmd_s, "empty")) {
			arg_A_t a = { NULL, 0 };
			if (arg_A_val(&a, lines, args)) {
				if (cmd_empty(a.A)) {
					ret.s = "true";
				} else {
					ret.s = "false";
					ret.N = a.N;
				}
				return ret;
			}
		} else if (!strcmp(cmd_s, "card")) {
			arg_A_t a = { NULL, 0 };
			if (arg_A_val(&a, lines, args)) {
				ret.u = true;
				ret.n = (long long int) cmd_card(a.A);
				return ret;
			}
		} else if (!strcmp(cmd_s, "complement")) {
			arg_A_t a = { NULL, 0 };
			if (arg_A_val(&a, lines, args)) {
				line->val_set = cmd_complement(get_universe(lines), a.A);
				return ret;
			}
		}
	}
	return ret;
}
