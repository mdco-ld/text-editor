#include <string>
#include <ui/base.hpp>
#include <ui/buffer.hpp>

namespace ui {

void drawBuffer(std::vector<std::string> &buffer, int init_buff, int x, int y,
                int max_column, int height) {

    for (int i = 0;
         i < height && i + init_buff < static_cast<int>(buffer.size()); i++) {

        base::goTo(x, y + i);
        std::basic_string buf = "";
        for (int j = 0; j < max_column &&
                        j < static_cast<int>(buffer[i + init_buff].size());
             j++) {
            buf += buffer[i + init_buff][j];
        }
        base::print(buf);
    }
}

} // namespace ui
