#include "ui/base.hpp"
#include <format>
#include <string_view>
#include <ui/status.hpp>

#define RIGHT_LIMITER ">"
#define LEFT_LIMITER "<"
#define DIVISOR "|"

void ui::drawStatus(int x, int y, int w, std::string_view status,
                    int cursor_line, int cursor_column) {
    base::goTo(x, y);
    std::string left = std::format("{} {} {}", LEFT_LIMITER, status, DIVISOR);

    base::print(left);

    std::string right = std::format("{} {} : {} {} {}", DIVISOR, cursor_line,
                                    DIVISOR, cursor_column, RIGHT_LIMITER);
    base::goTo(x + w - right.size(), y);
    base::print(right);
}
