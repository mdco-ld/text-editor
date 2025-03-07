#include <logger.hpp>
#include <ui/base.hpp>

#include <sstream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

#define ESC "\x1b"

namespace ui {

namespace base {

// TODO: Make this thread-safe
static std::string g_buffer;

void clear() { g_buffer += ESC "[2J"; }

void hideCursor() { g_buffer += ESC "[?25l"; }

void showCursor() { g_buffer += ESC "[?25h"; }

void colorFg(color::RGB col) {
    std::stringstream ss;
    ss << "[38;2;" << (int)col.r << ';' << (int)col.g << ';' << (int)col.b
       << 'm';
    g_buffer += ESC;
    g_buffer += ss.str();
}

void colorBg(color::RGB col) {
    std::stringstream ss;
    ss << "[48;2;" << (int)col.r << ';' << (int)col.g << ';' << (int)col.b
       << 'm';
    g_buffer += ESC;
    g_buffer += ss.str();
}

void goTo(int x, int y) {
    std::stringstream ss;
    ss << '[' << y << ';' << x << 'H';
    g_buffer += ESC;
    g_buffer += ss.str();
}

void print(std::string_view str) { g_buffer += str; }

void present() {
    write(STDOUT_FILENO, g_buffer.data(), g_buffer.size());
    g_buffer.clear();
}

bool getWindowSize(size_t &width, size_t &height) {
    winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_row == 0) {
        return false;
    }
    width = ws.ws_col;
    height = ws.ws_row;
    return true;
}

} // namespace base

}; // namespace ui
