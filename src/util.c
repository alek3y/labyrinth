#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "term.h"
#include "util.h"

int printf_clean(char *format, ...) {
	printf("\r");

	va_list arguments;
	va_start(arguments, format);
	int bytes_written = vprintf(format, arguments);
	va_end(arguments);

	unsigned int columns = term_width() - 1;
	if (bytes_written >= 0 && (size_t) bytes_written <= columns) {
		size_t empty_len = columns - bytes_written;

		char empty[empty_len + 1];
		memset(empty, ' ', empty_len);
		empty[empty_len] = 0;

		printf("%s", empty);
		term_cursor_move(0, -empty_len);
	}

	return bytes_written;
}
