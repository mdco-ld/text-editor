#ifndef _EDITOR_HPP_
#define _EDITOR_HPP_

#include <map>
#include <memory>
#include <string_view>

#include <window.hpp>

namespace editor {

class Editor {
  public:
    enum class Mode {
        Normal,
        Edit,
        Command,
    };

    Editor();

    void openFile(std::string_view path);

    void draw();

  private:
    std::map<size_t, std::unique_ptr<Window>> windows_;
    std::optional<size_t> activeWindowId_;
    size_t nextWindowId_;
};

}; // namespace editor

#endif
