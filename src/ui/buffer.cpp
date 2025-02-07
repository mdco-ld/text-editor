#include <string>
#include <ui/base.hpp>
#include <ui/buffer.hpp>

namespace ui {

void drawBuffer(editor::Buffer &buffer, size_t x, size_t y, size_t startLine,
                size_t maxWidth, size_t maxHeight) {

    for (size_t offset = 0;
         startLine + offset < buffer.getNumLines() && offset < maxHeight;
         offset++) {
        auto line = buffer.getLine(startLine + offset);
        if (line.size() > maxWidth) {
            line = line.substr(0, maxWidth);
        }
        ui::base::goTo(x, y + offset);
        ui::base::print(line);
    }
}

} // namespace ui
