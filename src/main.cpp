#include <buffer.hpp>
#include <input/base.hpp>
#include <logger.hpp>
#include <sstream>
#include <terminal.hpp>
#include <ui/base.hpp>
#include <utils.hpp>
#include <ui/box.hpp>

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
        ui::base::clear();
        ui::base::goTo(1, 1);
        ui::base::present();
		std::string text;
        while (true) {
            auto key = input::readKey();
			ui::base::clear();
			ui::base::colorFg({100, 200, 255});
			ui::drawBox(1, 1, 90, 30, "title");
			ui::base::colorFg({255, 255, 255});
			ui::base::goTo(2, 2);
            if (key) {
                if (key == input::Key{'q'}.setCtrl(true)) {
                    break;
                }
				if (key == input::Key::Special::Backspace) {
					if (text.size() > 0) {
						text.pop_back();
					}
				} else if (key == input::Key::Special::Space) {
					text += ' ';
				} else {
					std::stringstream ss;
					ss << key;
					text += ss.str();
				}
            }
			ui::base::print(text);
            ui::base::present();
        }
    } catch (std::runtime_error &e) {
        Logger::get().printlnAtExit(e.what());
    }
    return 0;
}
