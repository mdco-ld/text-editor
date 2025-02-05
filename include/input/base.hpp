#ifndef _INPUT_BASE_HPP_
#define _INPUT_BASE_HPP_

#include <variant>

namespace input {

struct KeyChar {
    char c;
    unsigned char ctrl : 1, alt : 1;
};

enum SpecialKey {
    Space,
    Enter,
    Tab,
    Backspace,
	Insert,
	Delete,
	Home,
	End,
	Down,
	Up,
	Left,
	Right,
};

using Key = std::variant<KeyChar, SpecialKey, std::monostate>;

Key readKey();

}; // namespace input

#endif
