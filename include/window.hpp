#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <optional>
#include <string>
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
    Window(std::string_view name);

    void draw(ui::Rect rect);

    void goDown();
    void goUp();
    void goLeft();
    void goRight();
    void goEnd();
    void goBegin();
    void goEndLine();
    void goBeginLine();

    void setContent(std::string_view content);

    [[nodiscard]] Cursor &getCursor();
    [[nodiscard]] Cursor getCursorPosition();

  private:
    void clampCursor();

    Buffer buffer_;
    Cursor cursor_;
    size_t offset_;
    std::optional<std::string> name_;
};

}; // namespace editor

#endif
