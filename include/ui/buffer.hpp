#ifndef _UI_BUFFER_HPP_
#define _UI_BUFFER_HPP_

#include <string>
#include <vector>

namespace ui {

void drawBuffer(std::vector<std::string> &buffer, int init_buff, int x, int y,
                int max_column, int height);

}

#endif
