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
        return std::monostate{};
    }
    if (c == 9) {
        return SpecialKey::Tab;
    }
    if (c == 32) {
        return SpecialKey::Space;
    }
    if (c == 13) {
        return SpecialKey::Enter;
    }
    if (c == 127) {
        return SpecialKey::Backspace;
    }
    bool alt = false;
    if (c == 27) {
        alt = true;
        if (!readChar(c, inputs)) {
            LOG_DEBUG("Unrecognized input sequence: {}", stringify(inputs));
            return std::monostate{};
        }
        if (c == 91) {
            if (readChar(c, inputs)) {
                if (c == 50) {
                    if (readChar(c, inputs)) {
                        if (c == 126) {
                            return SpecialKey::Insert;
                        }
                    }
                } else if (c == 51) {
                    if (readChar(c, inputs)) {
                        if (c == 126) {
                            return SpecialKey::Delete;
                        }
                    }
                } else if (c == 65) {
                    return SpecialKey::Up;
                } else if (c == 66) {
                    return SpecialKey::Down;
                } else if (c == 67) {
                    return SpecialKey::Right;
                } else if (c == 68) {
                    return SpecialKey::Left;
                } else if (c == 70) {
                    return SpecialKey::End;
                } else if (c == 72) {
                    return SpecialKey::Home;
                }
                LOG_DEBUG("Unrecognized input sequence: {}", stringify(inputs));
                return std::monostate{};
            }
        }
    }
    if (1 <= c && c <= 26) {
        return KeyChar{.c = (char)(c - 1 + 'a'), .ctrl = 1, .alt = alt};
    }
    return KeyChar{.c = c, .ctrl = 0, .alt = alt};
}

}; // namespace input
