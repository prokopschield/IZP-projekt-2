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
			if (arg_A_val(&a, lines, args, 2)) {
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
			if (arg_A_val(&a, lines, args, 1)) {
				ret.u = true;
				ret.n = (long long int) cmd_card(a.A);
				return ret;
			}
		} else if (!strcmp(cmd_s, "complement")) {
			arg_A_t a = { NULL, 0 };
			if (arg_A_val(&a, lines, args, 1)) {
				line->val_set = cmd_complement(get_universe(lines), a.A);
				return ret;
			}
		} else if (!strcmp(cmd_s, "union")) {
			arg_AB_t a = { NULL, NULL, 0 };
			if (arg_AB_val(&a, lines, args, 2)) {
				line->val_set = cmd_union(a.A, a.B);
				return ret;
			}
		} else if (!strcmp(cmd_s, "intersect")) {
			arg_AB_t a = { NULL, NULL, 0 };
			if (arg_AB_val(&a, lines, args, 2)) {
				line->val_set = cmd_intersect(a.A, a.B);
				return ret;
			}
		} else if (!strcmp(cmd_s, "minus")) {
			arg_AB_t a = { NULL, NULL, 0 };
			if (arg_AB_val(&a, lines, args, 2)) {
				line->val_set = cmd_minus(a.A, a.B);
				return ret;
			}
		} else if (!strcmp(cmd_s, "subseteq")) {
			arg_AB_t a = { NULL, NULL, 0 };
			if (arg_AB_val(&a, lines, args, 3)) {
				if (cmd_subseteq(a.A, a.B)) {
					ret.s = "true";
				} else {
					ret.s = "false";
					ret.N = a.N;
				}
			}
		} else if (!strcmp(cmd_s, "subset")) {
			arg_AB_t a = { NULL, NULL, 0 };
			if (arg_AB_val(&a, lines, args, 3)) {
				if (cmd_subset(a.A, a.B)) {
					ret.s = "true";
				} else {
					ret.s = "false";
					ret.N = a.N;
				}
			}
		} else if (!strcmp(cmd_s, "equals")) {
			arg_AB_t a = { NULL, NULL, 0 };
			if (arg_AB_val(&a, lines, args, 3)) {
				if (cmd_equals(a.A, a.B)) {
					ret.s = "true";
				} else {
					ret.s = "false";
					ret.N = a.N;
				}
			}
		} else if (!strcmp(cmd_s, "reflexive")) {
			arg_R_t a = { NULL, 0 };
			if (arg_R_val(&a, lines, args, 2)) {
				if (cmd_reflexive(get_universe(lines), a.R)) {
					ret.s = "true";
				} else {
					ret.s = "false";
					ret.N = a.N;
				}
			}
		} else if (!strcmp(cmd_s, "symmetric")) {
			arg_R_t a = { NULL, 0 };
			if (arg_R_val(&a, lines, args, 2)) {
				if (cmd_symmetric(a.R)) {
					ret.s = "true";
				} else {
					ret.s = "false";
					ret.N = a.N;
				}
			}
		} else if (!strcmp(cmd_s, "antisymmetric")) {
			arg_R_t a = { NULL, 0 };
			if (arg_R_val(&a, lines, args, 2)) {
				if (cmd_antisymmetric(a.R)) {
					ret.s = "true";
				} else {
					ret.s = "false";
					ret.N = a.N;
				}
			}
		} else if (!strcmp(cmd_s, "transitive")) {
			arg_R_t a = { NULL, 0 };
			if (arg_R_val(&a, lines, args, 2)) {
				if (cmd_transitive(a.R)) {
					ret.s = "true";
				} else {
					ret.s = "false";
					ret.N = a.N;
				}
			}
		} else if (!strcmp(cmd_s, "function")) {
			arg_R_t a = { NULL, 0 };
			if (arg_R_val(&a, lines, args, 2)) {
				if (cmd_function(a.R)) {
					ret.s = "true";
				} else {
					ret.s = "false";
					ret.N = a.N;
				}
			}
		} else if (!strcmp(cmd_s, "domain")) {
			arg_R_t a = { NULL, 0 };
			if (arg_R_val(&a, lines, args, 1)) {
				line->val_set = cmd_domain(a.R);
				return ret;
			}
		} else if (!strcmp(cmd_s, "codomain")) {
			arg_R_t a = { NULL, 0 };
			if (arg_R_val(&a, lines, args, 1)) {
				line->val_set = cmd_codomain(a.R);
				return ret;
			}
		} else if (!strcmp(cmd_s, "injective")) {
			arg_RAB_t a = { NULL, NULL, NULL, 0 };
			if (arg_RAB_val(&a, lines, args, 3)) {
				if (cmd_injective(a.R, a.A, a.B)) {
					ret.s = "true";
				} else {
					ret.s = "false";
					ret.N = a.N;
				}
			}
		} else if (!strcmp(cmd_s, "surjective")) {
			arg_RAB_t a = { NULL, NULL, NULL, 0 };
			if (arg_RAB_val(&a, lines, args, 3)) {
				if (cmd_surjective(a.R, a.A, a.B)) {
					ret.s = "true";
				} else {
					ret.s = "false";
					ret.N = a.N;
				}
			}
		} else if (!strcmp(cmd_s, "bijective")) {
			arg_RAB_t a = { NULL, NULL, NULL, 0 };
			if (arg_RAB_val(&a, lines, args, 3)) {
				if (cmd_bijective(a.R, a.A, a.B)) {
					ret.s = "true";
				} else {
					ret.s = "false";
					ret.N = a.N;
				}
			}
		} else if (!strcmp(cmd_s, "closure_ref")) {
			arg_R_t a = { NULL, 0 };
			if (arg_R_val(&a, lines, args, 1)) {
				line->val_rel = cmd_closure_ref(get_universe(lines), a.R);
				return ret;
			}
		} else if (!strcmp(cmd_s, "closure_sym")) {
			arg_R_t a = { NULL, 0 };
			if (arg_R_val(&a, lines, args, 1)) {
				line->val_rel = cmd_closure_sym(a.R);
				return ret;
			}
		} else if (!strcmp(cmd_s, "closure_trans")) {
			arg_R_t a = { NULL, 0 };
			if (arg_R_val(&a, lines, args, 1)) {
				line->val_rel = cmd_closure_trans(a.R);
				return ret;
			}
		} else if (!strcmp(cmd_s, "select")) {
			if (args->len > 2) {
				throw_error("Too many select() arguments (%ld > 2)", args->len);
			}
			if (args->len > 0) {
				line_t* A = lineload(lines, args->items[0]);
				if (A->val_set && (A->val_set != empty_set())) {
					line->val_set = cmd_select(A->val_set);
				} else if (A->val_rel && (A->val_rel != empty_rel())) {
					set_t* domain = cmd_domain(A->val_rel);
					set_t* codomain = cmd_codomain(A->val_rel);
					if (domain && codomain) { // malloc may have failed
						set_t* u = cmd_union(domain, codomain);
						if (u) { // malloc may have failed
							line->val_set = cmd_select(u);
						}
					}
				} else if (args->len >= 2) {
					// goto line N
					ret.N = args->items[1];
				} else {
					line->val_set = empty_set();
				}
				return ret;
			}
		} else {
			throw_error("Unknown command: \"%s\"", cmd_s);
		}
	}
	return ret;
}
