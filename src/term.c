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

void term_cursor_move(int dy, int dx) {
#ifdef _WIN32
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(output, &info);

	info.dwCursorPosition.Y += dy;
	info.dwCursorPosition.X += dx;
	SetConsoleCursorPosition(output, info.dwCursorPosition);
#else
	if (dy != 0) {
		printf("\x1b[%d%c", abs(dy), dy > 0 ? 'B' : 'A');
		fflush(stdout);
	}

	if (dx != 0) {
		printf("\x1b[%d%c", abs(dx), dx > 0 ? 'C' : 'D');
		fflush(stdout);
	}
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

	CONSOLE_SCREEN_BUFFER_INFO info = {0};
	GetConsoleScreenBufferInfo(output, &info);

	return info.srWindow.Right - info.srWindow.Left + 1;
#else
	struct winsize info = {0};
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &info);

	return info.ws_col;
#endif
}

char term_getch(void) {
#ifdef _WIN32
	return _getch();
#else
	struct termios original, new;
	if (tcgetattr(STDIN_FILENO, &original) == 0) {
		new = original;

		// Disabilita la modalità canonica e l'echo dell'input (vedi termios(3))
		new.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &new);

		char byte = fgetc(stdin);
		tcsetattr(STDIN_FILENO, TCSANOW, &original);	// Ripristina lo stato originale
		return byte;
	}

	return fgetc(stdin);
#endif
}
