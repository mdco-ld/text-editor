#include <ui/base.hpp>
#include <ui/rect.hpp>

#include <cassert>

#define TOP_LEFT "╭"
#define TOP_RIGHT "╮"
#define BOTTOM_LEFT "╰"
#define BOTTOM_RIGHT "╯"
#define VERTICAL "│"
#define HORIZONTAL "─"

namespace ui {

void drawBox(ui::Rect rect) {
    assert(rect.h >= 2 && rect.w >= 2);
    base::goTo(rect.x, rect.y);
    base::print(TOP_LEFT);
    for (size_t i = 1; i < rect.w - 1; i++) {
        base::print(HORIZONTAL);
    }
    base::print(TOP_RIGHT);
    base::goTo(rect.x, rect.y + rect.h - 1);
    base::print(BOTTOM_LEFT);
    for (size_t i = 1; i < rect.w - 1; i++) {
        base::print(HORIZONTAL);
    }
    base::print(BOTTOM_RIGHT);
    for (size_t i = 1; i < rect.h - 1; i++) {
        base::goTo(rect.x, rect.y + i);
        base::print(VERTICAL);
        base::goTo(rect.x + rect.w - 1, rect.y + i);
        base::print(VERTICAL);
    }
}

void drawBox(ui::Rect rect, std::string_view label) {
    assert(rect.h >= 2 && rect.w >= 2);
    drawBox(rect);
    if (rect.w == 2) {
        return;
    }
    if (rect.w < label.size() + 2) {
        label = label.substr(0, rect.w - 2);
    }
    size_t padSize = (rect.w - label.size()) / 2;
    base::goTo(rect.x + padSize, rect.y);
    base::print(label);
}

}; // namespace ui
