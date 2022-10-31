#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "term.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <sys/select.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#endif

void term_cursor_scroll(int dy) {
	if (dy == 0) {
		return;
	}

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
	fflush(stdout);
#endif
}

void term_sleep(unsigned int ms) {
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

unsigned int term_width(void) {
#ifdef _WIN32
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(output, &info);

	return info.srWindow.Right - info.srWindow.Left + 1;
#else
	struct winsize info;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &info);

	return info.ws_col;
#endif
}

char term_getch(void) {
#ifdef _WIN32
	return _getch();
#else
	struct termios original, new;
	tcgetattr(STDIN_FILENO, &original);
	new = original;

	// Disabilita la modalità canonica (vedi termios(3))
	new.c_lflag &= ~ICANON;
	tcsetattr(STDIN_FILENO, TCSANOW, &new);

	char input = fgetc(stdin);
	tcsetattr(STDIN_FILENO, TCSANOW, &original);	// Ripristina lo stato originale
	return input;
#endif
}
