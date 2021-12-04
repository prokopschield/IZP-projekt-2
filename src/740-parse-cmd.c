cmd_t* parse_cmd(FILE* input, bool EOL) {
	cmd_t* cmd = (cmd_t*) buffer_alloc(sizeof(cmd_t));
	if (!cmd) {
		throw(error.malloc);
		return NULL;
	}
	cmd->cmd = read_word(input, &EOL);
	cmd->args = arr_alloc(2);
	if (!cmd->cmd.len || !cmd->cmd.data || !cmd->args) {
		throw(error.malloc);
		return cmd;
	}
	while (!EOL) {
		string_t str = read_word(input, &EOL);
		if (!str.len || !str.data) {
			throw(error.malloc);
			return cmd;
		}
		signed long long int n = 0;
		size_t r = sscanf((char*) str.data, "%lld", &n);
		if (!r || (n <= 0)) {
			throw_chars("Invalid command parameter(s).\n");
			throw_error("The following is not a natural number: %s", str.data);
		}
		arr_push(cmd->args, (void*) n);
		str_free(&str);
	}
	return cmd;
}
