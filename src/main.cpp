#include <buffer.hpp>
#include <input/base.hpp>
#include <logger.hpp>
#include <terminal.hpp>
#include <ui/base.hpp>
#include <ui/box.hpp>
#include <ui/buffer.hpp>
#include <ui/status.hpp>
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
        ui::base::clear();
        ui::base::goTo(1, 1);
        ui::base::present();
        auto text = utils::readFile("CMakeLists.txt");
        auto buffer = editor::Buffer(text);
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
            }
            ui::drawBuffer(buffer, 2, 2, 0, 88, 28);
            ui::base::goTo(2, 2);
            ui::base::present();
        }
    } catch (std::runtime_error &e) {
        Logger::get().printlnAtExit(e.what());
    }
    return 0;
}
