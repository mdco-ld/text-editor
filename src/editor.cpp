#include <editor.hpp>
#include <logger.hpp>
#include <ui/base.hpp>
#include <utils.hpp>

#include <filesystem>
#include <memory>

namespace editor {

Editor::Editor() : nextWindowId_(0), mode_(Mode::Normal), quit_(false) {}

void Editor::openFile(std::string_view filePath) {
    auto window = std::make_unique<Window>(filePath);
    if (!std::filesystem::exists(filePath)) {
        windows_.insert({nextWindowId_, std::move(window)});
        return;
    }
    auto content = utils::readFile(filePath);
    window->setContent(content);
    windows_.insert({nextWindowId_, std::move(window)});
    activeWindowId_ = nextWindowId_;
    nextWindowId_++;
}

void Editor::draw() {
    static size_t w = 90;
    static size_t h = 30;
    ui::base::getWindowSize(w, h);
    if (!activeWindowId_.has_value()) {
        return;
    }
    auto windowId = activeWindowId_.value();
    auto activeWindow = windows_.at(windowId).get();
    activeWindow->draw({1, 1, w, h - 1});
    switch (mode_) {
    case Mode::Normal: {
        auto cursor = activeWindow->getCursorPosition();
        ui::base::goTo(cursor.x + 1, cursor.y + 1);
        break;
    }
    case Mode::Edit: {
        break;
    }
    case Mode::Search: {
        break;
    }
    case Mode::Command: {
        auto data = std::get<CommandModeData>(modeData_);
        ui::base::goTo(1, h);
        ui::base::print("Command: ");
        ui::base::print(data.commandBuffer);
        break;
    }
    }
}

[[nodiscard]] bool Editor::shouldQuit() const noexcept { return quit_; }

void Editor::processInputKey(input::Key key) {
    switch (mode_) {
    case Mode::Normal:
        processKeyNormal(key);
        break;
    case Mode::Edit:
        processKeyEdit(key);
        break;
    case Mode::Search:
        processKeySearch(key);
        break;
    case Mode::Command:
        processKeyCommand(key);
        break;
    }
}

void Editor::processKeyNormal(input::Key key) {
    using input::Key;
    if (key == Key{'m'}.setAlt(true)) {
        mode_ = Mode::Command;
        modeData_ = CommandModeData();
        return;
    }
    if (key == Key{'j'}) {
        if (activeWindowId_.has_value()) {
            size_t windowId = activeWindowId_.value();
            windows_.at(windowId)->goDown();
        }
        return;
    }
    if (key == Key{'k'}) {
        if (activeWindowId_.has_value()) {
            size_t windowId = activeWindowId_.value();
            windows_.at(windowId)->goUp();
        }
        return;
    }
    if (key == Key{'l'}) {
        if (activeWindowId_.has_value()) {
            size_t windowId = activeWindowId_.value();
            windows_.at(windowId)->goRight();
        }
        return;
    }
    if (key == Key{'h'}) {
        if (activeWindowId_.has_value()) {
            size_t windowId = activeWindowId_.value();
            windows_.at(windowId)->goLeft();
        }
        return;
    }
}

void Editor::processKeyEdit(input::Key key) {
    using input::Key;
    if (key == Key::Special::Esc) {
        mode_ = Mode::Normal;
        return;
    }
}

void Editor::processKeySearch([[maybe_unused]] input::Key key) {}

void Editor::processKeyCommand(input::Key key) {
    using input::Key;
    auto data = std::get<CommandModeData>(modeData_);
    if (key == Key::Special::Esc) {
        mode_ = Mode::Normal;
        return;
    }
    if (key == Key::Special::Enter) {
        if (data.commandBuffer == "quit") {
            quit_ = true;
        }
        mode_ = Mode::Normal;
        return;
    }
    if (key == Key::Special::Backspace) {
        if (data.commandBuffer.size() > 0) {
            data.commandBuffer.pop_back();
            modeData_ = std::move(data);
        }
        return;
    }
    if (key.getChar() != 0 && !key.getAlt() && !key.getCtrl()) {
        data.commandBuffer += key.getChar();
        modeData_ = std::move(data);
        return;
    }
}

}; // namespace editor
