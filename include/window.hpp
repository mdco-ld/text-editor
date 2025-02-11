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

    void insertLine(size_t lineIdx);
    void insertLineUnderCursor();
    void insertLineAboveCursor();
    void eraseLine(size_t lineIdx);
    void eraseLineAtCursor();

    void insertCharacter(char c, size_t line, size_t position);
    void insertCharacterAtCursor(char c, bool move = true);
    void eraseCharacter(size_t line, size_t position);
    void eraseCharacterAtCursor(bool move = true);

    [[nodiscard]] Cursor &getCursor();
    [[nodiscard]] Cursor getCursorPosition();

  private:
    void clampCursorPosition();

    Buffer buffer_;
    Cursor cursor_;
    size_t offset_;
    std::optional<std::string> name_;
};

}; // namespace editor

#endif
