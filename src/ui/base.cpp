#include <ui/base.hpp>

#include <sstream>
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

std::string Base::buffer_;

}; // namespace ui
