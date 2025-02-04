#include <terminal.hpp>
#include <ui/base.hpp>

#include <unistd.h>

#include <iostream>

int main() {
	if (!isatty(STDOUT_FILENO)) {
		std::cerr << "output is not a terminal" << std::endl;
		return 0;
	}
	if (!isatty(STDIN_FILENO)) {
		std::cerr << "input is not a terminal" << std::endl;
		return 0;
	}
    Terminal::init();
    char c;
	ui::Base::clear();
	ui::Base::goTo(1, 1);
	ui::Base::present();
    while (true) {
        read(STDIN_FILENO, &c, 1);
		if (c == 'q') {
			break;
		}
    }
    return 0;
}
