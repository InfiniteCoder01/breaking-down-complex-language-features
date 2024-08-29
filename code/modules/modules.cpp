#include <iostream>

namespace logger {
    void init() {
        std::cout << "Initialized logger!" << std::endl;
    }
}

int main() {
    logger::init();
    return 0;
}
