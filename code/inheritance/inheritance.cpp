#include <iostream>

class Node {
protected:
    int x, y;

public:
    void setPosition(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

class Button: public Node {
    unsigned int clicks = 0;

public:
    void click() {
        clicks++;
        std::cout << "Button at " << x << ", " << y << " was clicked " << clicks << " times!\n";
    }
};

int main() {
    Button button;
    button.setPosition(15, 10);
    button.click();
    return 0;
}
