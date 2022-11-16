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
    float radius;
    bool active;
    Color color;
} Box;

// global variables declaration
static const int screen_width = 800;
static const int screen_height = 450;
static bool game_over = false;
static bool game_is_paused = false;
static bool victory = false;

static Paddle paddle = { 0 };
static Ball ball = { 0 };
static Box box = { 0 };

// program main entry point
int main(void)
{
    InitWindow(screen_width, screen_height, "ATARI BREAKOUT");

    SetTargetFPS(60); // set our game to run at 60 frames-per-second

    // main game loop
    while (!WindowShouldClose()) // detect window close or esc key
    {
        // update
        int pos_x, pos_y;
        int vel_x, vel_y,
        victory = false;
        game_is_paused = false;



        paddle.position = (Vector2){screen_width / 2, screen_height / 2};
        paddle.velocity = (Vector2){10.0f, 0.0f};
        paddle.acceleration = 0;
        paddle.width = 250;
        paddle.height = 10;
        paddle.color = YELLOW;

        if (IsKeyDown(KEY_RIGHT)) paddle.position.x += paddle.velocity.x;
        if (IsKeyDown(KEY_LEFT)) paddle.position.x -= paddle.velocity.x;

        // draw
        BeginDrawing();

            ClearBackground(BLACK);
            
            DrawRectangle(paddle.position.x, paddle.position.y, paddle.width, paddle.height, paddle.color);

        EndDrawing();
    };
};