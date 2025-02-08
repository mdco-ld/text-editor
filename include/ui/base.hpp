#ifndef _UI_BASE_HPP_
#define _UI_BASE_HPP_

#include <cstdint>
#include <string_view>

namespace ui {

namespace base {

void clear();

void hideCursor();
void showCursor();

void goTo(int x, int y);

void print(std::string_view str);

bool getWindowSize(size_t &width, size_t &height);

void present();

}; // namespace base

namespace color {

struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

}; // namespace color

namespace base {

void colorFg(color::RGB col);
void colorBg(color::RGB col);

}; // namespace base

}; // namespace ui

#endif
