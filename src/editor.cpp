#include <editor.hpp>
#include <logger.hpp>
#include <ui/base.hpp>
#include <utils.hpp>

#include <filesystem>
#include <memory>

namespace editor {

Editor::Editor() : nextWindowId_(0) {}

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
    windows_.at(windowId)->draw({1, 1, w, h - 1});
}

}; // namespace editor
