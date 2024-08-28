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

# Methods
- **Functions defined inside a class or object.**
- **Found in: Java, Python, Ruby, C#, etc.**

Starting off simple. Methods are essential feature of all modern programming languages.
And yet, C doesn't have that. Let's look at this simple example:
```C++
class Game {
    Vector2 playerPosition;

public:
    void update(float deltaTime) {
        playerPosition.x += deltaTime;
    }
}

int main() {
    Game game;
    game.update(0.1);
    return 0;
}
```
Here we can see a class, that has a field called player_position and a method called update.
But how does this method knows about player_position? Let's transform the example:
```C++
class Game {
// <...>
    void update(float deltaTime) {
        this->playerPosition.x += deltaTime; // Added `this->`
    }
}
// <...>
```

After this change, we can see that all class members are actually accessed using `this` pointer under the hood.
But where does it come from? Let's imagine it was in python:
```Python
class Game:
    # <...>
    def update(self, delta_time: float):
        self.player_position.x += delta_time
# <...>
```

AHA! `self` (alternative to C++'s `this`) comes as a special argument!
We can now try to replicate this in C:
```C
typedef struct Game {
    Vector2 player_position;
} Game;

void game_update(Game* game, float delta_time) {
    game->player_position.x += delta_time;
}
```

# Modules
- **A way to organize code into separate files or namespaces.**
- **Found in: Python, JavaScript, Ruby, TypeScript.**

**TODO!**
