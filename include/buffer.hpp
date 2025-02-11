#ifndef _BUFFER_HPP_
#define _BUFFER_HPP_

#include <string>
#include <vector>

#include <ui/rect.hpp>

namespace editor {

class Buffer {
  public:
    Buffer();
    Buffer(std::string_view content);

    void addLine(size_t lineNum);
    void addContent(size_t lineNum, std::string_view content);

    const std::string_view getLine(size_t lineNum) const;
    const std::string_view getLinePart(size_t lineNum, size_t start,
                                       size_t maxLength) const;

    [[nodiscard]] size_t getNumLines() const noexcept;

    void setContent(std::string_view content);

    void draw(size_t startOffset, ui::Rect rect);

    void insertCharacter(char c, size_t line, size_t position);
    void eraseCharacter(size_t line, size_t position);
    void insertLine(size_t lineIdx);
    void eraseLine(size_t lineIdx);

  private:
    // TODO: Refactor to use a splay tree instead of std::vector
    std::vector<std::string> lines_;
};

}; // namespace editor

#endif
