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

Key::Key(Key::Special special) : value((uint32_t)special) {}
Key::Key() : value(0u) {}
Key::Key(char c) : value(c) {}

Key::operator bool() { return value != 0; }

bool Key::operator==(Key other) { return value == other.value; }

Key &Key::setCtrl(bool ctrl) {
    if (ctrl) {
        value |= Key::Ctrl;
    } else {
        value &= ~Key::Ctrl;
    }
    return *this;
}

Key &Key::setAlt(bool alt) {
    if (alt) {
        value |= Key::Alt;
    } else {
        value &= ~Key::Alt;
    }
    return *this;
}

bool Key::getCtrl() { return (value & Key::Ctrl) != 0; }

bool Key::getAlt() { return (value & Key::Alt) != 0; }

char Key::getChar() { return value & 0xff; }

Key::Special Key::getSpecialChar() { return (Special)(value & 0xffff00); }

Key readKey() {
    char c;
    std::vector<char> inputs;
    if (!readChar(c, inputs)) {
        return Key{};
    }
    if (c == 9) {
        return Key::Special::Tab;
    }
    if (c == 32) {
        return Key::Special::Space;
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

std::ostream &operator<<(std::ostream &out, Key key) {
    if (!key) {
        return out << "<No-Key>";
    }
    if (key.getCtrl()) {
        out << "Ctrl-";
    }
    if (key.getAlt()) {
        out << "Alt-";
    }
    if (key.getChar() != 0) {
        return out << key.getChar();
    }
    switch (key.getSpecialChar()) {
    case Key::Special::None:
        return out << "NoKey";
    case Key::Special::Space:
        return out << "Space";
    case Key::Special::Enter:
        return out << "Enter";
    case Key::Special::Tab:
        return out << "Tab";
    case Key::Special::Backspace:
        return out << "Backspace";
    case Key::Special::Insert:
        return out << "Insert";
    case Key::Special::Delete:
        return out << "Delete";
    case Key::Special::Home:
        return out << "Home";
    case Key::Special::End:
        return out << "End";
    case Key::Special::Down:
        return out << "Down";
    case Key::Special::Up:
        return out << "Up";
    case Key::Special::Left:
        return out << "Left";
    case Key::Special::Right:
        return out << "Right";
	case Key::Special::Esc:
		return out << "Esc";
    }
    LOG_ERROR("Somehow we reached unreachable code");
    return out;
}

}; // namespace input
