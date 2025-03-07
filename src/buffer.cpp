#include <buffer.hpp>
#include <logger.hpp>
#include <ui/base.hpp>
#include <ui/rect.hpp>

#include <cassert>

namespace editor {

Buffer::Buffer() { lines_.push_back(""); }

Buffer::Buffer(std::string_view content) { setContent(content); }

void Buffer::setContent(std::string_view content) {
    lines_.clear();
    std::string currentLine;
    for (size_t pos = 0; pos < content.size(); pos++) {
        if (content[pos] == '\n') {
            lines_.emplace_back(std::move(currentLine));
        } else {
            if (content[pos] == '\t') {
                currentLine += std::string(4, ' ');
            } else {
                currentLine += content[pos];
            }
        }
    }
}

void Buffer::addLine(size_t lineNum) {
    assert(lineNum <= lines_.size());
    lines_.insert(lines_.begin() + lineNum, "");
}

void Buffer::addContent(size_t lineNum, std::string_view content) {
    assert(lineNum <= lines_.size());
    std::vector<std::string> contentLines;
    for (size_t position = 0, lineStart = 0; position < content.size();
         position++) {
        if (content[position] == '\n') {
            contentLines.push_back(
                std::string(content.substr(lineStart, position - lineStart)));
            lineStart = position + 1;
        }
    }
    lines_.insert(lines_.begin() + lineNum, contentLines.begin(),
                  contentLines.end());
}

const std::string_view Buffer::getLine(size_t lineNum) const {
    assert(lineNum < lines_.size());
    return lines_[lineNum];
}

const std::string_view Buffer::getLinePart(size_t lineNum, size_t start,
                                           size_t maxLength) const {
    auto line = getLine(lineNum);
    if (start >= line.size()) {
        return "";
    }
    maxLength = std::min(maxLength, line.size() - start);
    return line.substr(start, maxLength);
}

[[nodiscard]] size_t Buffer::getNumLines() const noexcept {
    return lines_.size();
}

void Buffer::draw(size_t startOffset, ui::Rect rect) {
    for (size_t offset = 0;
         startOffset + offset < lines_.size() && offset < rect.h; offset++) {
        auto line = getLine(startOffset + offset);
        if (line.size() > rect.w) {
            line = line.substr(0, rect.w);
        }
        ui::base::goTo(rect.x, rect.y + offset);
        ui::base::print(line);
    }
}

void Buffer::insertCharacter(char c, size_t line, size_t position) {
    lines_[line].insert(lines_[line].begin() + position, c);
}

void Buffer::eraseCharacter(size_t line, size_t position) {
    lines_[line].erase(lines_[line].begin() + position);
}

void Buffer::insertLine(size_t lineIdx) {
    lines_.insert(lines_.begin() + lineIdx, std::string());
}

void Buffer::eraseLine(size_t lineIdx) {
    lines_.erase(lines_.begin() + lineIdx);
}

}; // namespace editor
