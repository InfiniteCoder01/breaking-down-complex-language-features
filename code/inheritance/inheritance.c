#include <stdio.h>

struct Node {
    int x, y;
};

void node_set_position(struct Node *node, int x, int y) {
    node->x = x;
    node->y = y;
}

struct Button {
    struct Node node;
    unsigned int clicks;
};

void button_click(struct Button *button) {
    button->clicks++;
    printf("Button at %d, %d was licked %u times!\n", button->node.x, button->node.y, button->clicks);
}

int main() {
    struct Button button;
    button.clicks = 0;
    node_set_position(&button.node, 15, 10); // Note how we can use methods on the inner node
    button_click(&button);
    return 0;
}
