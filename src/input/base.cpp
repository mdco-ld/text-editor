#include <input/base.hpp>
#include <logger.hpp>

#include <sstream>
#include <unistd.h>
#include <vector>

namespace input {

bool readChar(char &c, std::vector<char> &inputs) {
    if (read(STDIN_FILENO, &c, 1) <= 0) {
        return false;
    }
    inputs.push_back(c);
    return true;
}

std::string stringify(std::vector<char> &v) {
    std::stringstream ss;
    ss << "{";
    for (size_t i = 0; i < v.size(); i++) {
        if (i > 0) {
            ss << ", ";
        }
        ss << (int)v[i];
    }
    ss << "}";
    return ss.str();
}

Key readKey() {
    char c;
    std::vector<char> inputs;
    if (!readChar(c, inputs)) {
        return Key{};
    }
    if (c == 9) {
        return Key::Special::Tab;
    }
    if (c == 13) {
        return Key::Special::Enter;
    }
    if (c == 127) {
        return Key::Special::Backspace;
    }
    bool alt = false;
    if (c == 27) {
        alt = true;
        if (!readChar(c, inputs)) {
            return Key::Special::Esc;
        }
        if (c == 91) {
            if (readChar(c, inputs)) {
                if (c == 50) {
                    if (readChar(c, inputs)) {
                        if (c == 126) {
                            return Key::Special::Insert;
                        }
                    }
                } else if (c == 51) {
                    if (readChar(c, inputs)) {
                        if (c == 126) {
                            return Key::Special::Delete;
                        }
                    }
                } else if (c == 65) {
                    return Key::Special::Up;
                } else if (c == 66) {
                    return Key::Special::Down;
                } else if (c == 67) {
                    return Key::Special::Right;
                } else if (c == 68) {
                    return Key::Special::Left;
                } else if (c == 70) {
                    return Key::Special::End;
                } else if (c == 72) {
                    return Key::Special::Home;
                }
                LOG_DEBUG("Unrecognized input sequence: {}", stringify(inputs));
                return Key{};
            }
        }
    }
    if (1 <= c && c <= 26) {
        c += 'a' - 1;
        return Key{c}.setCtrl(true).setAlt(alt);
    }
    return Key{c}.setAlt(alt);
}

}; // namespace input
