#include "raylib.h"
#include <math.h>

// @author Hugo Lindfors (リンドフォースヒューゴ)

// types and structures definition
typedef struct Paddle
{
    Vector2 position;
    Vector2 velocity;
    float acceleration;
    float width;
    float height;
    Color color;
} Paddle;

typedef struct Ball
{
    Vector2 position;
    Vector2 velocity;
    float radius;
    Color color;
} Ball;

typedef struct Box
{
    Vector2 position;
    float width;
    float height;
    bool active;
    Color color;
} Box;

// global variables declaration
const int screen_width = 800;
const int screen_height = 450;
bool game_over = false;
bool game_is_paused = false;
bool victory = false;

Paddle paddle = {0};
Ball ball = {0};
Box box[60] = {0};

// program main entry point
int main(void)
{
    InitWindow(screen_width, screen_height, "ATARI BREAKOUT");

    SetTargetFPS(60); // set our game to run at 60 frames-per-second

    paddle.position = (Vector2){screen_width / 2, screen_height / 2 + 200};
    paddle.velocity = (Vector2){10.0f, 0.0f};
    paddle.acceleration = 0;
    paddle.width = 250;
    paddle.height = 10;
    paddle.color = YELLOW;

    ball.position = (Vector2){screen_width / 2, screen_height / 2};
    ball.velocity = (Vector2){0.0f, 5.0f};
    ball.radius = 10.0f;
    ball.color = LIGHTGRAY;

    // box.position = (Vector2){screen_width / 2, screen_height / 2 - 200};
    // box.width = 200;
    // box.height = 20;
    // box.active = true;
    // box.color = YELLOW;

    for (int i = 0; i < 60; i++)
    {
        box[i].position = (Vector2){screen_width / 2, screen_height / 2 - 200};
        box[i].width = 200;
        box[i].height = 20;
        box[i].active = true;
        box[i].color = YELLOW;
    }
    



    // main game loop
    while (!WindowShouldClose()) // detect window close or esc key
    {

        Rectangle paddle_rec = {
            .x = paddle.position.x,
            .y = paddle.position.y,
            .width = paddle.width,
            .height = paddle.height};

        // Rectangle box_rec = {
        //     .x = box.position.x,
        //     .y = box.position.y,
        //     .width = box.width,
        //     .height = box.height};

        Rectangle box_rec[60];

        for (int i = 0; i < 60; i++)
        {
            box_rec[i] = {
                .x = box[i].position.x,
                .y = box[i].position.y,
                .width = box[i].width,
                .height = box[i].height;
            };
        };

        // update

        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
            paddle.position.x += paddle.velocity.x;

        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
            paddle.position.x -= paddle.velocity.x;

        if (CheckCollisionCircleRec(ball.position, ball.radius, paddle_rec))
        {
            ball.velocity.x = -ball.velocity.x;
            ball.velocity.y = -ball.velocity.y;
        }

        // if (CheckCollisionCircleRec(ball.position, ball.radius, box_rec) && box.active)
        // {
        //     ball.velocity.x = -ball.velocity.x;
        //     ball.velocity.y = -ball.velocity.y;
        //     box.active = false;
        // }

        ball.position.x += ball.velocity.x;
        ball.position.y += ball.velocity.y;

        // draw
        BeginDrawing();

        ClearBackground(BLACK);

        // if (box.active)
        //     DrawRectangle(box.position.x, box.position.y, box.width, box.height, box.color);

        DrawRectangle(paddle.position.x, paddle.position.y, paddle.width, paddle.height, paddle.color);

        DrawCircle(ball.position.x, ball.position.y, ball.radius, ball.color);

        EndDrawing();
    };
};