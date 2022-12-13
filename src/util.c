#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "term.h"
#include "util.h"

//! @details Non conoscendo la posizione orizzontale del cursore
//! l'offset va specificato manualmente.
int printf_clean(unsigned int offset, char *format, ...) {
	va_list arguments;
	va_start(arguments, format);
	int written = vprintf(format, arguments);
	va_end(arguments);

	if (written >= 0) {
		unsigned int cursor = written + offset;
		unsigned int columns = term_width() - 1;
		if (cursor <= columns) {
			unsigned int empty_len = columns - cursor;

			char empty[empty_len + 1];
			memset(empty, ' ', empty_len);
			empty[empty_len] = 0;

			printf("%s", empty);
			term_cursor_move(0, -empty_len);
		}
	}

	return written;
}
