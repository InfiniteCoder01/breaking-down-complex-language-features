---
title: "Breaking down complex language features in C"
highlight_theme: "base16-ocean.dark"
---
# {{ metadata.title }}
Modern programming languages have a lot of useful features.
This includes traits, inheritance, operator overloding and many more.
I was making an [intermediate representation](https://github.com/InfiniteCoder01/OrCo) to support all those features,
but it become overwelming, so here I am breaking those down.

We are gonna be using C to implement broken-down versions of patterns.
That is because C doesn't have any of them. And manual memory management
will help us understand what is going on under the hood

# Modules
- **A way to organize code into separate files or namespaces.**
- **Found in: Python, JavaScript, Ruby, TypeScript, etc.**

[Code](https://github.com/InfiniteCoder01/breaking-down-complex-language-features/tree/master/code/modules)

Modules, or namespaces, can be found in most modern languages.
They help separate code into reusable segments. Modules (not namespaces) in dynamic
programming languages can also be lazily-loaded. Yet we will only focus on namespaces here.
Let's look at the following C++ snippet:
```C++
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
```

This grouping of functionality can be represented in C using prefixes:
```C
#include <stdio.h>

void logger_init() {
    puts("Initialized logger!\n");
}

int main() {
    logger_init();
    return 0;
}
```

Note: As a good coding practice, it's better to move grouped functionality into a separate header file!

# Methods
- **Functions defined inside a class or object.**
- **Found in: Java, Python, Ruby, C#, etc.**

[Code](https://github.com/InfiniteCoder01/breaking-down-complex-language-features/tree/master/code/methods)

Starting off simple. Methods are essential feature of most modern programming languages.
And yet, C doesn't have that. Let's look at this simple C++ example:
```C++
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
```
Here we can see a class, that has a field called player_position and a method called update.
But how does this method knows about player_position? Let's modify the hit function:
```C++
void Player::hit(float damage) {
    this->health -= damage; // Note `this->`
}
```

Now we can see the hidden `this` pointer that is used to access fields under the hood.
But where does it come from? Let's look at a language that shows it more explicitly,
for example, Python:
```Python
class Player:
    def hit(self, damage: float):
        self.health -= delta_time
```

AHA! `self` (alternative to C++'s `this`) comes as a special argument!
We can now try to replicate this behavious in C:
```C
#include <stdio.h>
#include <stdint.h>

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
```
