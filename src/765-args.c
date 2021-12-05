bool arg_A_val(arg_A_t* res, array_t* lines, size_t_array_t* args,  size_t max_args) {
	if (args->len < 1) {
		throw_chars("Insufficient arguments: ");
		return false;
	}
	line_t* arg_1 = lineload(lines, args->items[0]);
	res->A = arg_1->val_set ? arg_1->val_set : (set_t*) arg_1->val_rel;
	if (args->len >= 2) {
		res->N = args->items[1];
	}
	if (args->len > max_args) {
		throw_error("Too many arguments: %ld > %ld", args->len, max_args);
	}
	if (res->A) {
		return true;
	} else {
		invalid_argument(arg_1);
		return false;
	}
}

bool arg_AB_val(arg_AB_t* res, array_t* lines, size_t_array_t* args, size_t max_args) {
	if (args->len < 2) {
		throw_chars("Insufficient arguments: ");
		return false;
	}
	line_t* arg_1 = lineload(lines, args->items[0]);
	if (!(res->A = arg_1->val_set)) {
		invalid_argument(arg_1);
	}
	line_t* arg_2 = lineload(lines, args->items[1]);
	if (!(res->B = arg_2->val_set)) {
		invalid_argument(arg_2);
	}
	if (args->len >= 3) {
		res->N = args->items[2];
	}
	if (args->len > max_args) {
		throw_error("Too many arguments: %ld > %ld", args->len, max_args);
	}
	return (res->A && res->B);
}
