#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <string_view>

#include <buffer.hpp>
#include <ui/rect.hpp>

namespace editor {

struct Cursor {
    size_t x;
    size_t y;
};

class Window {
  public:
    Window();
    Window(std::string_view text);

    void draw(ui::Rect rect);

    void goDown();
    void goUp();
    void goLeft();
    void goRight();
    void goEnd();
    void goBegin();
    void goEndLine();
    void goBeginLine();

    [[nodiscard]] Cursor &getCursor();
    [[nodiscard]] Cursor getCursorPosition();

  private:
    Buffer buffer_;
    Cursor cursor_;
    size_t offset_;
};

}; // namespace editor

#endif
