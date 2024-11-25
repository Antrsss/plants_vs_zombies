#include <iostream>

extern "C" int exponent(int, int);

int main() {
    int num = exponent(4, 2);
    std::cout << num;
    return 0;
}
