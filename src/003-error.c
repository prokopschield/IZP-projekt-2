#include <stdbool.h>

typedef struct error_t {
	bool any;
	bool malloc;
} error_t;

error_t error = { false, false };

#define throw(e)(e = error.any = true)
