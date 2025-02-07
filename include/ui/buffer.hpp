#ifndef _UI_BUFFER_HPP_
#define _UI_BUFFER_HPP_

#include <buffer.hpp>

namespace ui {

void drawBuffer(editor::Buffer &buffer, size_t x, size_t y, size_t startLine,
                size_t maxWidth, size_t maxHeight);

}

#endif
