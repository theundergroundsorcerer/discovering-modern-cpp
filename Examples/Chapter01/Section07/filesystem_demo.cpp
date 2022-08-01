// A small demo demonstrating usage of <filesystem> header
#include <string>
#include <iostream>

#if __has_include(<filesystem>)
#define FVESRION 2
#include <filesystem>
namespace fs = std::filesystem;
#elif __has_include(<experimental/filesytem>)
#define FVERSION 1
#include <experimental/filesystem>
namespace fs = std::experimantal::filesystem::v1;
#endif

int main(int argc, char* argv[]) {
#ifndef FVESRION
    std::cerr << "File system not supported yet by this compiler\n";
#endif
    std::cout << (FVESRION == 2 ? "mature" : "experimental") << " filesystem support.\n";
    std::string path{"."};

    if(argc > 1) {
        path = argv[1];
    }
    for(const auto& p : fs::directory_iterator(path)) {
        if (fs::is_regular_file(p)) {
            std::cout << p << " is a regular file\n";
        } else if (fs::is_directory(p)) {
            std::cout << p << " is a directory.\n";
        } else {
            std::cout << p << " is neither regular file nor directory.\n";
        }
    }
}
