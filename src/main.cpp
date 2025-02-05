#include <buffer.hpp>
#include <utils.hpp>
#include <terminal.hpp>
#include <ui/base.hpp>
#include <logger.hpp>

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
    try {
        Terminal::init();
        ui::Base::clear();
        ui::Base::goTo(1, 1);
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
    } catch (std::runtime_error &e) {
		Logger::get().printlnAtExit(e.what());
    }
    return 0;
}
