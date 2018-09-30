#include "files.hpp"

// #define WINDOWS  // uncomment this line to use it for windows
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

namespace gamelib2 {

// -----------------------------------------------------------------------------
//  getWorkingDirectory
// -----------------------------------------------------------------------------
std::string Files::getWorkingDirectory() {
    char buff[FILENAME_MAX];
    GetCurrentDir(buff, FILENAME_MAX);
    std::string current_working_dir(buff);
    return current_working_dir;
}

} // namespace gamelib2
