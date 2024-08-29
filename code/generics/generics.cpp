#include <iostream>

template<typename T>
struct Vec2 {
    T x, y;
};

int main() {
    Vec2<float> v;
    v.x = 2.1;
    v.y = 4.2;
    std::cout << v.x << ' ' << v.y << std::endl;
    return 0;
}
