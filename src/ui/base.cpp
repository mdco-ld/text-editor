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

void hideCursor() {
	g_buffer += ESC "[?25l";
}

void showCursor() {
	g_buffer += ESC "[?25h";
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

int getWidth() {
    winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCSWINSZ, &ws) == -1 || ws.ws_col == 0) {
        return -1;
    }
    return ws.ws_col;
}

int getHeight() {
    winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCSWINSZ, &ws) == -1 || ws.ws_row == 0) {
        return -1;
    }
    return ws.ws_row;
}

} // namespace base

}; // namespace ui
