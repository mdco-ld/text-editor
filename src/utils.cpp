#include <sstream>
#include <utils.hpp>

#include <format>
#include <fstream>
#include <stdexcept>

namespace utils {

std::string readFile(std::string_view filepath, bool noThrow) {
    std::ifstream in(filepath.data());
    if (!in) {
		if (noThrow) {
			return "";
		}
        throw std::runtime_error(
            std::format("Unable to open file '{}'", filepath));
    }
    std::stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

}; // namespace utils
