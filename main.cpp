#include <iostream>

int main(int argc, char** argv) {
    // Item 4

    int x = 0; // manual initialization of an int
    const char * text = "A C-style string"; // manual initialization of a
    // pointer (see also Item 3)
    double d; // “initialization” by reading from
    std::cin >> d;

    std::cout << d << std::endl;

    return 0;
}