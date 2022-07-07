// A simple program demonstrating using io with exceptions.
#include <fstream>
#include <iostream>

void with_exceptions(std::ios& io) {
    io.exceptions(std::ios_base::badbit | std::ios_base::failbit);
}

int main() {
    std::ofstream out_file;
    with_exceptions(out_file);
    out_file.open("f.data");

    double o1 = 5.2, o2 = 6.2;
    out_file << o1 << o2 << std::endl;
    out_file.close();

    std::ifstream in_file;
    with_exceptions(in_file);
    try {
        in_file.open("g.data");
    }
    catch(std::ifstream::failure e) {
        std::cout << "Could not open 'g.data': " << e.what() << '\n';
        in_file.open("f.data");
    }

    int i1, i2;
    char c;
    in_file >> i1 >> c >> i2;
    std::cout << "i1 = " << i1 << ", i2 = " << i2 << "\n";
}