#include <ui/base.hpp>

#include <expected>
#include <sstream>
#include <sys/ioctl.h>
#include <unistd.h>

namespace ui {

#define ESC "\x1b"

void Base::clear() { buffer_ += ESC "[2J"; }

void Base::goTo(int x, int y) {
    std::stringstream ss;
    ss << '[' << y << ';' << x << 'H';
    buffer_ += ESC;
    buffer_ += ss.str();
}

void Base::print(std::string_view str) { buffer_ += str; }

void Base::present() {
    write(STDOUT_FILENO, buffer_.data(), buffer_.size());
    buffer_.clear();
}

int Base::getWidth() {
    winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCSWINSZ, &ws) == -1 || ws.ws_col == 0) {
        return -1;
    }
    return ws.ws_col;
}

int Base::getHeight() {
    winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCSWINSZ, &ws) == -1 || ws.ws_row == 0) {
        return -1;
    }
    return ws.ws_row;
}

std::string Base::buffer_;

}; // namespace ui
