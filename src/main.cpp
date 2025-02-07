#include <buffer.hpp>
#include <input/base.hpp>
#include <logger.hpp>
#include <terminal.hpp>
#include <ui/base.hpp>
#include <ui/box.hpp>
#include <ui/status.hpp>
#include <utils.hpp>
#include <window.hpp>

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
        auto text = utils::readFile("CMakeLists.txt");
        auto window = editor::Window(text);
        ui::base::clear();
        ui::base::present();
        window.draw({1, 1, 90, 30});
        while (true) {
            auto key = input::readKey();
            if (key) {
                if (key == input::Key{'q'}.setCtrl(true)) {
                    break;
                }
                if (key == input::Key{'j'}) {
                    window.goDown();
                }
                if (key == input::Key{'k'}) {
                    window.goUp();
                }
                if (key == input::Key{'h'}) {
                    window.goLeft();
                }
                if (key == input::Key{'l'}) {
                    window.goRight();
                }
            }
            ui::base::clear();
            window.draw({1, 1, 90, 30});
            ui::base::goTo(window.getCursorPosition().x + 1,
                           window.getCursorPosition().y + 1);
            ui::base::present();
        }
    } catch (std::runtime_error &e) {
        Logger::get().printlnAtExit(e.what());
    }
    return 0;
}
