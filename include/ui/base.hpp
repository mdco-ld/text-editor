#ifndef _UI_BASE_HPP_
#define _UI_BASE_HPP_

#include <string_view>

namespace ui {

namespace base {

void clear();

void goTo(int x, int y);

void print(std::string_view str);

int getWidth();
int getHeight();

void present();

}; // namespace base

}; // namespace ui

#endif
