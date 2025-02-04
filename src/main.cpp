#include <terminal.hpp>

#include <unistd.h>

int main() {
    Terminal::init();
    char c;
    while (true) {
        read(STDIN_FILENO, &c, 1);
		if (c == 'q') {
			break;
		}
    }
    return 0;
}
