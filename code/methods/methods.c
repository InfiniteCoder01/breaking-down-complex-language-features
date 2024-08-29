#include <stdio.h>

struct Player {
  float health;
};

void player_hit(struct Player* player, float damage) {
  player->health -= damage;
}

int main() {
  struct Player player;
  player.health = 100.0;
  player_hit(&player, 20.0);
  printf("Health: %f\n", player.health);
  return 0;
}
