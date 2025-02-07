#include <ui/base.hpp>

#include <cassert>

#define TOP_LEFT "╭"
#define TOP_RIGHT "╮"
#define BOTTOM_LEFT "╰"
#define BOTTOM_RIGHT "╯"
#define VERTICAL "│"
#define HORIZONTAL "─"

namespace ui {

void drawBox(int x, int y, int w, int h) {
    assert(h >= 2 && w >= 2);
    base::goTo(x, y);
    base::print(TOP_LEFT);
    for (int i = 1; i < w - 1; i++) {
        base::print(HORIZONTAL);
    }
    base::print(TOP_RIGHT);
    base::goTo(x, y + h - 1);
    base::print(BOTTOM_LEFT);
    for (int i = 1; i < w - 1; i++) {
        base::print(HORIZONTAL);
    }
    base::print(BOTTOM_RIGHT);
    for (int i = 1; i < h - 1; i++) {
        base::goTo(x, y + i);
        base::print(VERTICAL);
        base::goTo(x + w - 1, y + i);
        base::print(VERTICAL);
    }
}

void drawBox(int x, int y, int w, int h, std::string_view label) {
    assert(h >= 2 && w >= 2);
    drawBox(x, y, w, h);
    if (w == 2) {
        return;
    }
    if (w - 2 < (int)label.size()) {
        label = label.substr(0, w - 2);
    }
    int padSize = (w - (int)label.size()) / 2;
    base::goTo(x + padSize, y);
    base::print(label);
}

}; // namespace ui
