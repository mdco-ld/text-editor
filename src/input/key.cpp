#include <input/key.hpp>
#include <logger.hpp>

namespace input {

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
