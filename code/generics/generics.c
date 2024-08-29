#include <stdio.h>

#define VEC2(T) struct Vec2_ ## T
#define VEC2_DEF(T) VEC2(T) { T x, y; }

VEC2_DEF(float);

int main() {
    VEC2(float) v;
    v.x = 2.1;
    v.y = 4.2;
    printf("%f %f\n", v.x, v.y);
    return 0;
}
