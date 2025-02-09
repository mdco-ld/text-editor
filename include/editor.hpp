#ifndef _EDITOR_HPP_
#define _EDITOR_HPP_

#include <map>
#include <memory>
#include <string_view>

#include <input/key.hpp>
#include <window.hpp>

namespace editor {

class Editor {
  public:
    enum class Mode {
        Normal,
        Edit,
        Command,
        Search,
    };

    Editor();

    void openFile(std::string_view path);

    void draw();

    void processInputKey(input::Key key);

    [[nodiscard]] bool shouldQuit() const noexcept;

  private:
    void processKeyNormal(input::Key key);
    void processKeyEdit(input::Key key);
    void processKeyCommand(input::Key key);
    void processKeySearch(input::Key key);

    std::map<size_t, std::unique_ptr<Window>> windows_;
    std::optional<size_t> activeWindowId_;
    size_t nextWindowId_;
    Mode mode_;
    bool quit_;
};

}; // namespace editor

#endif
