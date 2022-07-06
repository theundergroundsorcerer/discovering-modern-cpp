// A simple example demonstrading the usage of file input/output
#include <fstream>
#include <iostream>

void writeSquares() {
    std::ofstream square_file{"squares.txt"};
    for(int i = 0; i < 10; ++i) {
        square_file << i << "^2 = " << i * i << '\n';
    }
}

void readSquares() {
    std::ifstream square_file{"squares.txt"};
    if(!square_file) {
        std::cerr << "Unable to open squares.txt";
        exit(1);
    }

    for(char ch = square_file.get(); ch != EOF; ch = square_file.get() ) {
        std::cout << ch;
    }
}

int main() {
    std::cout << "Writing squares...\n";
    writeSquares();
    std::cout << "Written successfully!\n";

    std::cout << "Reading squares...\n";
    readSquares();
    std::cout << "Done!\n";
}