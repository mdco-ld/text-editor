#ifndef _INPUT_BASE_HPP_
#define _INPUT_BASE_HPP_

#include <cstdint>
#include <ostream>

namespace input {

struct Key {
    uint32_t value = 0;

    static constexpr uint32_t Ctrl = 1 << 24;
    static constexpr uint32_t Alt = 1 << 25;

    enum class Special {
        None = 0,
        Space = 1u << 8,
        Enter = 2u << 8,
        Tab = 3u << 8,
        Backspace = 4u << 8,
        Insert = 5u << 8,
        Delete = 6u << 8,
        Home = 7u << 8,
        End = 8u << 8,
        Down = 9u << 8,
        Up = 10u << 8,
        Left = 11u << 8,
        Right = 12u << 8,
        Esc = 13u << 8,
    };

    bool getCtrl();
    bool getAlt();
    char getChar();
    Special getSpecialChar();
    Key &setCtrl(bool ctrl);
    Key &setAlt(bool alt);

    Key();
    Key(char c);
    Key(Special special);

    operator bool();
    bool operator==(Key other);
};

Key readKey();

std::ostream &operator<<(std::ostream &out, Key key);

}; // namespace input

#endif
