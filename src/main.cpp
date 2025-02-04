#include <terminal.hpp>
#include <ui/base.hpp>

#include <unistd.h>

int main() {
    Terminal::init();
    char c;
	ui::Base::clear();
	ui::Base::goTo(1, 1);
	ui::Base::present();
    while (true) {
        read(STDIN_FILENO, &c, 1);
		if (c == 'q') {
			break;
		}
    }
    return 0;
}
