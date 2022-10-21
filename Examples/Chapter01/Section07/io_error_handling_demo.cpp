// A simple example that shows how to handle io-errors (without exceptions)
#include <fstream>
#include <iostream>

void create_good_file() {
    std::ofstream good_file{"good_file.data_"};
    good_file << 5 << ' ' << 6.0 << '\n';
}

int main() {
    create_good_file();
    std::ifstream infile;
    std::string filename{"bad_file.data_"};
    bool opened = false;
    while(!opened) {
        infile.open(filename);
        if(infile.good()) {
            opened = true;
        } else {
            std::cout << "The file '" << filename << "' does not exist (or can not be opened),"
                      << "please enter: 'good_file.data_': ";
            std::cin >> filename;
        }
    }

    int i;
    double d;
    infile >> i >> d;

    if(infile.good()) {
        std::cout << "i is " << i << ", d is " << d << '\n';
    }
    else {
        std::cout << "Could not correctly read the content.\n";
    }
    infile.close();

}