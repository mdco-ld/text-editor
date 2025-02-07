#ifndef _UI_BOX_HPP_
#define _UI_BOX_HPP_

#include "ui/rect.hpp"
#include <string_view>

namespace ui {

void drawBox(ui::Rect rect);
void drawBox(ui::Rect rect, std::string_view label);

}; // namespace ui

#endif
