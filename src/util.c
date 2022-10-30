#include <stdio.h>
#include <stdlib.h>
#include "util.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/select.h>
#include <sys/time.h>
#endif

void cursor_move_rows(int dy) {
#ifdef _WIN32
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(output, &info);

	info.dwCursorPosition.Y += dy;
	SetConsoleCursorPosition(output, info.dwCursorPosition);
#else
	char direction = 'B';	// Down
	if (dy < 0) {
		direction = 'A';	// Up
	}
	printf("\x1b[%d%c", abs(dy), direction);
#endif
}

void msleep(unsigned int ms) {
#ifdef _WIN32
	Sleep(ms);
#else
	struct timeval time = {
		.tv_sec = ms / 1000,
		.tv_usec = (ms % 1000) * 1000
	};
	select(0, NULL, NULL, NULL, &time);
#endif
}
