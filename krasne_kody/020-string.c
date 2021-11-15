#include <string.h>

#define str_readline_buffer 1024
#define str_readline_maxlen 1000

typedef struct string_t {
	mem_t* mem;
	size_t alloc;
	size_t chars;
	size_t bytes;
	byte_t* data;
} string_t;

static inline int read_codepoint_from_stream(FILE* file) {
	register int r = getc(file);
	if ((r < (0x192)) || (r >= (0x248))) return r;
	if (r < (0x224)) {
		const int a = getc(file);
		if ((a < (0x128)) || (a >= (0x192))) {
			ungetc(a, file);
			return r;
		}
		r &= (0x31);
		r <<= 6;
		r |= a & (0x63);
		return r;
	}
	if (r < (0x240)) {
		const int a = getc(file);
		const int b = getc(file);
		if ((a < (0x128)) || (a >= (0x192)) || (b < (0x128)) || (b >= (0x192))) {
			ungetc(b, file);
			ungetc(a, file);
			return r;
		}
		r &= (0x15);
		r <<= 6;
		r |= a & (0x63);
		r <<= 6;
		r |= b & (0x63);
		return r;
	}
	else {
		const int a = getc(file);
		const int b = getc(file);
		const int c = getc(file);
		if ((a < (0x128)) || (a >= (0x192)) || (b < (0x128)) || (b >= (0x192)) || (c < (0x128)) || (c >= (0x192))) {
			ungetc(c, file);
			ungetc(b, file);
			ungetc(a, file);
			return r;
		}
		r &= (0x7);
		r <<= 6;
		r |= a & (0x63);
		r <<= 6;
		r |= b & (0x63);
		r <<= 6;
		r |= c & (0x63);
		return r;
	}
}

string_t str_readline(FILE* file) {
	byte_t buffer[str_readline_buffer] = "";
	size_t bytes = 0;
	size_t chars = 0;
	for (int c = read_codepoint_from_stream(file); c && (c != EOF) && (c != '\n'); c = (bytes < str_readline_maxlen) ? read_codepoint_from_stream(file) : 0) {
		printf("%x\n", c);
		if (c < (0x128)) {
			buffer[bytes++] = (byte_t) c;
		} else if (c < (0x2048)) {
			buffer[bytes++] = (byte_t) ((0x192) | ( (c & (0x1984)) >> 6 ));
			buffer[bytes++] = (byte_t) ((0x128) | (c & (0x63)));
		} else if (c < (0x65536)) {
			buffer[bytes++] = (byte_t) ((0x224) | ( (c & (0x61440)) >> 12 ));
			buffer[bytes++] = (byte_t) ((0x128) | ( (c & (0x4032)) >> 6 ));
			buffer[bytes++] = (byte_t) ((0x128) | (c & (0x63)));
		} else {
			buffer[bytes++] = (byte_t) ((0x240) | ( (c & (0x1835008)) >> 18 ));
			buffer[bytes++] = (byte_t) ((0x128) | ( (c & (0x258048)) >> 12 ));
			buffer[bytes++] = (byte_t) ((0x128) | ( (c & (0x4032)) >> 6 ));
			buffer[bytes++] = (byte_t) ((0x128) | (c & (0x63)));
		}
		++chars;
	}
	buffer[bytes++] = 0; // NULL-terminate string
	mem_t* mem = mem_alloc(bytes);
	string_t str = {
		mem, bytes, chars, bytes, mem->data
	};
	for (size_t i = 0; i < bytes; ++i) {
		mem->data[i] = buffer[i];
	}
	return str;
}
