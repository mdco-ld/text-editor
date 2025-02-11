#ifndef _EDITOR_HPP_
#define _EDITOR_HPP_

#include <input/key.hpp>
#include <map>
#include <memory>
#include <string_view>
#include <variant>
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
    struct CommandModeData {
        std::string commandBuffer;
    };

    using ModeData = std::variant<CommandModeData>;

    void processKeyNormal(input::Key key);
    void processKeyEdit(input::Key key);
    void processKeyCommand(input::Key key);
    void processKeySearch(input::Key key);
    void executeCommand(std::string_view command);

    Window *getActiveWindow();

    std::map<size_t, std::unique_ptr<Window>> windows_;
    std::optional<size_t> activeWindowId_;
    size_t nextWindowId_;
    Mode mode_;
    ModeData modeData_;
    bool quit_;
};

}; // namespace editor

#endif
