#ifndef _UI_BOX_HPP_
#define _UI_BOX_HPP_

#include <string_view>

namespace ui {

void drawBox(int x, int y, int w, int h);
void drawBox(int x, int y, int w, int h, std::string_view label);

}; // namespace ui

#endif
