#include <buffer.hpp>
#include <input/base.hpp>
#include <logger.hpp>
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
            auto inputKey = input::readKey();
            if (std::holds_alternative<input::KeyChar>(inputKey)) {
                auto key = std::get<input::KeyChar>(inputKey);
                if (key.ctrl && key.c == 'q') {
                    break;
                }
                if (key.ctrl) {
                    ui::Base::print("Ctrl-");
                }
                if (key.alt) {
                    ui::Base::print("Alt-");
                }
                ui::Base::print(std::to_string(key.c));
                ui::Base::print("\r\n");
            } else if (std::holds_alternative<input::SpecialKey>(inputKey)) {
                auto key = std::get<input::SpecialKey>(inputKey);
                switch (key) {
                    using input::SpecialKey;
                case input::Space:
                    ui::Base::print("Space\r\n");
                    break;
                case input::Tab:
                    ui::Base::print("Tab\r\n");
                    break;
                case input::Enter:
                    ui::Base::print("Enter\r\n");
                    break;
                case input::Backspace:
                    ui::Base::print("Backspace\r\n");
                    break;
                case input::Insert:
                    ui::Base::print("Insert\r\n");
                    break;
                case input::Delete:
                    ui::Base::print("Delete\r\n");
                    break;
                case input::Home:
                    ui::Base::print("Home\r\n");
                    break;
                case input::End:
                    ui::Base::print("End\r\n");
                    break;
                case input::Up:
                    ui::Base::print("Up\r\n");
                    break;
                case input::Down:
                    ui::Base::print("Down\r\n");
                    break;
                case input::Left:
                    ui::Base::print("Left\r\n");
                    break;
                case input::Right:
                    ui::Base::print("Right\r\n");
                    break;
                }
            }
            ui::Base::present();
        }
    } catch (std::runtime_error &e) {
        Logger::get().printlnAtExit(e.what());
    }
    return 0;
}
