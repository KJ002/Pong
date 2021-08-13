#include <cstdio>
#include <raylib.h>
#include "Thunder/include/thunder.hpp"

#include <iostream>

#define PADDLESPEED 6
#define BALLSPEED 15
#define BUF_SIZE 10

#define log(n) std::cout << n << std::endl

class Body{
public:
  PhysicsBodyRec PhysicsBody;
  Rectangle RenderBody;

  Body(PhysicsEnvironment &env, Vec2 position, Vec2 size) :
    PhysicsBody(&env, position, size, (Vec2){0, 0}, 5, 0, 0)
  {
    updatePosition();
  }

  void updatePosition(){
    this->RenderBody =
      {
      (float)this->PhysicsBody.position.x - (float)(this->PhysicsBody.size.x / 2),
      (float)this->PhysicsBody.position.y - (float)(this->PhysicsBody.size.y / 2),
      (float)this->PhysicsBody.size.x,
      (float)this->PhysicsBody.size.y
      };
  }

};

int main(){
  InitWindow(400, 200, "Pong");

  PhysicsEnvironment env(0.f, 0.f);

  Body ball(env, (Vec2){200, 100}, (Vec2){10, 10});

  Body paddle1(env, (Vec2){10, 100}, (Vec2){8, 40});
  Body paddle2(env, (Vec2){390, 100}, (Vec2){8, 40});
  int paddle1Score = 0;
  int paddle2Score = 0;
  char paddle1ScoreStr[BUF_SIZE];
  char paddle2ScoreStr[BUF_SIZE];
  int paddle1ScoreSize;
  int paddle2ScoreSize;

  ball.PhysicsBody.velocity.x = BALLSPEED;

  SetTargetFPS(60);

  bool reset;

  while (!WindowShouldClose()){
    env.update();
    env.checkCollisions();
    ball.updatePosition();
    paddle1.updatePosition();
    paddle2.updatePosition();

    paddle1.PhysicsBody.velocity.y = 0;
    paddle2.PhysicsBody.velocity.y = 0;

    sprintf(paddle1ScoreStr, "%d", paddle1Score);
    sprintf(paddle2ScoreStr, "%d", paddle2Score);
    paddle1ScoreSize = MeasureText(paddle1ScoreStr, 20);
    paddle2ScoreSize = MeasureText(paddle2ScoreStr, 20);

    reset = false;

    if (IsKeyDown(KEY_W) &&
        paddle1.PhysicsBody.position.y > 40)
      paddle1.PhysicsBody.velocity.y = -PADDLESPEED;

    if (IsKeyDown(KEY_S) &&
        paddle1.PhysicsBody.position.y < 160)
      paddle1.PhysicsBody.velocity.y = PADDLESPEED;

    if (IsKeyDown(KEY_I) &&
        paddle2.PhysicsBody.position.y > 40)
      paddle2.PhysicsBody.velocity.y = -PADDLESPEED;

    if (IsKeyDown(KEY_K) &&
        paddle2.PhysicsBody.position.y < 160)
      paddle2.PhysicsBody.velocity.y = PADDLESPEED;

    if (ball.PhysicsBody.position.y < 5)
      ball.PhysicsBody.velocity.y = BALLSPEED;

    if (ball.PhysicsBody.position.y > 195)
      ball.PhysicsBody.velocity.y = -BALLSPEED;

    if (ball.PhysicsBody.position.x < 5){
      paddle2Score++;
      reset = true;
    }

    if (ball.PhysicsBody.position.x > 395){
      paddle1Score++;
      reset = true;
    }

    if (reset){
      ball.PhysicsBody.position = (Vec2){200, 100};
      ball.PhysicsBody.velocity = (Vec2){BALLSPEED, 0};
    }

    if (ball.PhysicsBody.isColliding){
      ball.PhysicsBody.velocity.x = (ball.PhysicsBody.position.x > 100)
        ? -BALLSPEED
        : BALLSPEED;

      float collVel = ball.PhysicsBody.collidingObjects[0]->velocity.y;

      (collVel)
        ? ball.PhysicsBody.velocity.y = (collVel > 0) ? BALLSPEED : -BALLSPEED
        : ball.PhysicsBody.velocity.y = 0;
    }

    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangleRec(ball.RenderBody, RAYWHITE);
    DrawRectangleRec(paddle1.RenderBody, RAYWHITE);
    DrawRectangleRec(paddle2.RenderBody, RAYWHITE);
    DrawText(paddle1ScoreStr, 180-(paddle1ScoreSize/2), 50, 20, RAYWHITE);
    DrawText(paddle2ScoreStr, 220-(paddle2ScoreSize/2), 50, 20, RAYWHITE);

    for (int i : range(0, 20))
      DrawRectangle(198, i*10, 5, 5, RAYWHITE);

    EndDrawing();
  }

  CloseWindow();

  return 0;

}
