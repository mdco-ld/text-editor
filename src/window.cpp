#include <ui/base.hpp>
#include <ui/box.hpp>
#include <window.hpp>

namespace editor {

Window::Window() : buffer_(), cursor_(0, 0), offset_(0) {}

Window::Window(std::string_view content)
    : buffer_(content), cursor_(0, 0), offset_(0) {}

void Window::goDown() {
    size_t numLines = buffer_.getNumLines();
    if (cursor_.y + 1 < numLines) {
        cursor_.y++;
    }
}

void Window::goUp() {
    cursor_.y = std::min(cursor_.y, buffer_.getNumLines());
    if (cursor_.y > 0) {
        cursor_.y--;
    }
    offset_ = std::min(offset_, cursor_.y);
}

void Window::goRight() {
    if (cursor_.x < buffer_.getLine(cursor_.y).size()) {
        cursor_.x++;
    }
}

void Window::goLeft() {
    cursor_.x = std::min(cursor_.x, buffer_.getLine(cursor_.y).size());
    if (cursor_.x > 0) {
        cursor_.x--;
    }
}

void Window::goBeginLine() { cursor_.x = 0; }

void Window::goBegin() { cursor_.y = 0; }

void Window::goEndLine() { cursor_.x = -1; }

void Window::goEnd() { cursor_.y = buffer_.getNumLines() - 1; }

void Window::draw(ui::Rect rect) {
    ui::base::colorFg({100, 200, 255});
    ui::drawBox(rect, "Window");
    ui::base::colorFg({255, 255, 255});
    ui::Rect bufferRect = rect.subrect({1, 1, rect.w - 2, rect.h - 2});
    if (cursor_.y - offset_ >= bufferRect.h) {
        offset_ = cursor_.y - bufferRect.h + 1;
    }
    buffer_.draw(offset_, bufferRect);
}

[[nodiscard]] Cursor &Window::getCursor() { return cursor_; }

[[nodiscard]] Cursor Window::getCursorPosition() {
    return {cursor_.x + 1, cursor_.y - offset_ + 1};
}

}; // namespace editor
