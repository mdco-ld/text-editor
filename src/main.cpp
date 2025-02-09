#include <buffer.hpp>
#include <editor.hpp>
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
        ui::base::clear();
        ui::base::present();
        editor::Editor editor;
        while (true) {
            auto key = input::readKey();
            editor.processInputKey(key);
            ui::base::clear();
            editor.draw();
            ui::base::present();
            if (editor.shouldQuit()) {
                break;
            }
        }
    } catch (std::runtime_error &e) {
        Logger::get().printlnAtExit(e.what());
    }
    return 0;
}
