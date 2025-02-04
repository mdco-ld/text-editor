#include <terminal.hpp>

#include <termios.h>
#include <unistd.h>

static termios g_originalTermios;

Terminal::Terminal() {
	tcgetattr(STDOUT_FILENO, &g_originalTermios);

	termios term = g_originalTermios;
	
	term.c_iflag &= ~(IXON | IXOFF | ICRNL | IMAXBEL | BRKINT | IGNBRK);
	term.c_oflag &= ~(OPOST);
	term.c_cflag |= CS8;
	term.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 1;

	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &term);
}

Terminal::~Terminal() {
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &g_originalTermios);
}

void Terminal::init() {
	static Terminal instance;
}
