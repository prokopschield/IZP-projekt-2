set_t* get_universe(array_t* lines);

void invalid_argument(line_t* line);

line_t* lineload(array_t* lines, size_t n);

typedef struct evaled_t {
	size_t N; // goto line
	long long int n;
	char* s;
	bool u; // use flag
} evaled_t;

extern evaled_t eval(array_t* lines, line_t* line);

typedef struct arg_A_t {
	set_t* A;
	size_t N;
} arg_A_t;

extern bool arg_A_val(arg_A_t* res, array_t* lines, size_t_array_t* args, size_t max_args);

typedef struct arg_AB_t {
	set_t* A;
	set_t* B;
	size_t N;
} arg_AB_t;

extern bool arg_AB_val(arg_AB_t* res, array_t* lines, size_t_array_t* args, size_t max_args);

typedef struct arg_R_t {
	rel_t* R;
	size_t N;
} arg_R_t;

extern bool arg_R_val(arg_R_t* res, array_t* lines, size_t_array_t* args, size_t max_args);

typedef struct arg_RAB_t {
	rel_t* R;
	set_t* A;
	set_t* B;
	size_t N;
} arg_RAB_t;

extern bool arg_RAB_val(arg_RAB_t* res, array_t* lines, size_t_array_t* args, size_t max_args);
