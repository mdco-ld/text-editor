#include "buffer.hpp"
#include "utils.hpp"
#include <terminal.hpp>
#include <ui/base.hpp>

#include <iostream>
#include <unistd.h>

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
    ui::Base::clear();
    ui::Base::goTo(1, 1);
	auto text = utils::readFile("/home/miguel/.bashrc", true);
	auto buffer = editor::Buffer(text);
	for (size_t i = 0; i < std::min(buffer.getNumLines(), 15ul); i++) {
		ui::Base::print(buffer.getLine(i));
		ui::Base::print("\r\n");
	}
	ui::Base::present();
    char c;
    while (true) {
        if (read(STDIN_FILENO, &c, 1) > 0) {
            if (c == 'q') {
                break;
            }
            std::string s;
            s += std::to_string(c);
            s += "\r\n";
            ui::Base::print(s);
            ui::Base::present();
        }
    }
    return 0;
}
