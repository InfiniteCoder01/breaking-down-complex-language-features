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
- **Found in: Python, JavaScript, Ruby, TypeScript.**

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
- **Found in: Java, Python, Ruby, C#.**

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

void player_hit(struct Player *player, float damage) {
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

# Generics
- **Allow classes and functions to operate on any data type.**
- **Found in: Java, C#, C++ (templates).**

[Code](https://github.com/InfiniteCoder01/breaking-down-complex-language-features/tree/master/code/generics)

Generics (or templates) are a way to make container types and reuse same code for multiple types.
Consider this C++ example:
```C++
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
```

Under the hood compiler just creates the same struct for all types it's used with.
We can't replicate all the syntactic sugar, but we can utilize macros to make this in C:
```C
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
```

Be aware: any typedef-ed type will resolve to a different name!

Note: `A ## B` in a macro converts to AB. It's a token pasting operator, you can read more about it [here](https://learn.microsoft.com/en-us/cpp/preprocessor/token-pasting-operator-hash-hash?view=msvc-170)

Another note: Zig also uses a similar approach to emulate generics

# Inheritance
- **Allows a class to inherit properties and methods from another class.**
- **Found in: Java, C++, Python, C#.**

[Code](https://github.com/InfiniteCoder01/breaking-down-complex-language-features/tree/master/code/inheritance)

Inheritance is a useful feature in multiple OOP-oriented programming languages.
It allows reusing functionality from parent's class by multiple children

Look at the following C++ example:
```C++
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
```

To recreate this in C, we can utilize a different concept - composition
(yes, they are normally looked at opposites, but one can be implemented with another).
This also plays nicely with C++'s ability to inherit multiple parents
Here is the implementation:
```C
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
```
