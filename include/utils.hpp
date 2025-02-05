#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <string>

namespace utils {

std::string readFile(std::string_view filepath, bool noThrow = false);

};

#endif
