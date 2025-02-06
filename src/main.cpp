#include <buffer.hpp>
#include <input/base.hpp>
#include <logger.hpp>
#include <sstream>
#include <terminal.hpp>
#include <ui/base.hpp>
#include <utils.hpp>

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
        while (true) {
            auto key = input::readKey();
            if (key) {
                if (key == input::Key{'q'}.setCtrl(true)) {
                    break;
                }
                std::stringstream ss;
                ss << key << "\r\n";
                ui::Base::print(ss.str());
            }
            ui::Base::present();
        }
    } catch (std::runtime_error &e) {
        Logger::get().printlnAtExit(e.what());
    }
    return 0;
}
