bool arg_A_val(arg_A_t* res, array_t* lines, size_t_array_t* args,  size_t max_args) {
	if (args->len < 1) {
		throw_chars("Insufficient arguments: ");
		return false;
	}
	line_t* arg_1 = lineload(lines, args->items[0]);

	// if line is not a set, throw error
	if (!(res->A = arg_1->val_set)) {
		invalid_argument(arg_1);
	}

	if (args->len >= 2) {
		res->N = args->items[1];
	}
	if (args->len > max_args) {
		throw_error("Too many arguments: %ld > %ld", args->len, max_args);
	}
	return (res->A != NULL);
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

bool arg_R_val(arg_R_t* res, array_t* lines, size_t_array_t* args,  size_t max_args) {
	if (args->len < 1) {
		throw_chars("Insufficient arguments: ");
		return false;
	}
	line_t* arg_1 = lineload(lines, args->items[0]);
	if (!(res->R = arg_1->val_rel)) {
		invalid_argument(arg_1);
	}
	if (args->len >= 2) {
		res->N = args->items[1];
	}
	if (args->len > max_args) {
		throw_error("Too many arguments: %ld > %ld", args->len, max_args);
	}
	return (res->R);
}

bool arg_RAB_val(arg_RAB_t* res, array_t* lines, size_t_array_t* args,  size_t max_args) {
	if (args->len < 3) {
		throw_chars("Insufficient arguments: ");
		return false;
	}
	line_t* arg_1 = lineload(lines, args->items[0]);
	if (!(res->R = arg_1->val_rel)) {
		invalid_argument(arg_1);
	}
	line_t* arg_2 = lineload(lines, args->items[1]);
	if (!(res->A = arg_2->val_set)) {
		invalid_argument(arg_2);
	}
	line_t* arg_3 = lineload(lines, args->items[2]);
	if (!(res->B = arg_3->val_set)) {
		invalid_argument(arg_1);
	}
	if (args->len >= 4) {
		res->N = args->items[3];
	}
	if (args->len > max_args) {
		throw_error("Too many arguments: %ld > %ld", args->len, max_args);
	}
	return (res->R && res->A && res->B);
}
