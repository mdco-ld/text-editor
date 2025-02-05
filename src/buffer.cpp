#include <buffer.hpp>

#include <cassert>

namespace editor {

Buffer::Buffer() {
	lines_.push_back("");
}

Buffer::Buffer(std::string_view content) {
    for (size_t pos = 0, lineStart = 0; pos < content.size(); pos++) {
        if (content[pos] == '\n') {
            lines_.push_back(
                std::string(content.substr(lineStart, pos - lineStart)));
            lineStart = pos + 1;
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
	lines_.insert(lines_.begin() + lineNum, contentLines.begin(), contentLines.end());
}

const std::string_view Buffer::getLine(size_t lineNum) const {
	assert(lineNum < lines_.size());
	return lines_[lineNum];
}

const std::string_view Buffer::getLinePart(size_t lineNum, size_t start, size_t maxLength) const {
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

}; // namespace editor
