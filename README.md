# Pong

This is a basic game recreating the traditional arcade game [Pong](https://en.wikipedia.org/wiki/Pong) to 
demonstrate the use of [Thunder](https://github.com/KJ002/Thunder) in conjunction with [raylib](https://www.raylib.com/).
This game is written in C++ because this is the only languages Thunder supports.

## Building

To compile pong you most complete the following:

1. Install [raylib](https://www.raylib.com/)
2. Submodule [Thunder](https://github.com/KJ002/Thunder) in an initalised git project with the command `git submodule add https://github.com/KJ002/Thunder`
3. Compile code with g++/clang++ with the command `g++ main.cpp Thunder/include/thunder.cpp -o main -lraylib -lGL -lm -ldl -lrt -lX11 -lpthread -O3`
