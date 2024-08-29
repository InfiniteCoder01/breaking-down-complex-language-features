#include <iostream>

class Player {
public:
    float health = 100.0;
    void hit(float damage);
};

void Player::hit(float damage) {
    health -= damage;
}

int main() {
    Player player;
    player.hit(20.0);
    std::cout << "Health: " << player.health << std::endl;
    return 0;
}
