cmd_t* parse_cmd(array_t* error, FILE* input, bool EOL) {
	cmd_t* cmd = (cmd_t*) buffer_alloc(sizeof(cmd_t));
	cmd->cmd = read_word(input, &EOL);
	cmd->args = arr_alloc(2);
	while (!EOL) {
		string_t str = read_word(input, &EOL);
		signed long long int n = 0;
		size_t r = sscanf((char*) str.data, "%lld", &n);
		if (r != str.len) {
			arr_push(error, "Invalid command parameter(s).");
			const char format[] = "The following is not a natural number: %s";
			char* err = (char*) buffer_alloc(str.len + sizeof(format));
			sprintf(err, format, (char*) str.data);
			arr_push(error, err);
		}
		arr_push(cmd->args, (void*) n);
		str_free(&str);
	}
	return cmd;
}
