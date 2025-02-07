#ifndef _UI_STATUS_HPP_
#define _UI_STATUS_HPP_
#include <string_view>
#include <ui/base.hpp>

namespace ui {
void drawStatus(int x, int y, int w, std::string_view status, int cursor_line,
                int cursor_column);

}

#endif // !_UI_STATUS_H
