#include <ui/rect.hpp>

namespace ui {

Rect Rect::subrect(Rect rect) {
    return {
        .x = x + rect.x,
        .y = y + rect.y,
        .w = rect.w,
        .h = rect.h,
    };
}

}; // namespace ui
