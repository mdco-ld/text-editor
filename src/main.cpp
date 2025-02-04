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
        if (read(STDIN_FILENO, &c, 1) > 0) {
			if (c == 'q') {
				break;
			}
			std::string s;
			s += c;
			s += "\r\n";
			ui::Base::print(s);
			ui::Base::present();
		}
    }
    return 0;
}
