#ifndef _UI_BASE_HPP_
#define _UI_BASE_HPP_

#include <string>

namespace ui {

class Base {
  public:
    static void clear();

    static void goTo(int x, int y);

	static void print(std::string_view str);

	static int getWidth();
	static int getHeight();

    static void present();

  private:
    static std::string buffer_;
};

}; // namespace ui

#endif
