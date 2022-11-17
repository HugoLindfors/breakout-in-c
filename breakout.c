#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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
int fail_counter;
int boxes_hit_counter;

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
    ball.velocity = (Vector2){0.0f, 4.0f};
    ball.radius = 10.0f;
    ball.color = LIGHTGRAY;

    // box.position = (Vector2){screen_width / 2, screen_height / 2 - 200};
    // box.width = 200;
    // box.height = 20;
    // box.active = true;
    // box.color = YELLOW;

    int j = 0;
    for (int i = 0; i < 60; i++)
    {
        if (i < 10)
        {
            box[i].position = (Vector2){135 * j, 0};
            box[i].color = RED;
            j++;
            if (j == 10)
                j = 0;
        }

        else if (i < 20)
        {
            box[i].position = (Vector2){135 * j, 35};
            box[i].color = ORANGE;
            j++;
            if (j == 10)
                j = 0;
        }

        else if (i < 30)
        {
            box[i].position = (Vector2){135 * j, 70};
            box[i].color = ORANGE;
            j++;
            if (j == 10)
                j = 0;
        }

        else if (i < 40)
        {
            box[i].position = (Vector2){135 * j, 105};
            box[i].color = YELLOW;
            j++;
            if (j == 10)
                j = 0;
        }

        else if (i < 50)
        {
            box[i].position = (Vector2){135 * j, 140};
            box[i].color = GREEN;
            j++;
            if (j == 10)
                j = 0;
        }

        else
        {
            box[i].position = (Vector2){135 * j, 175};
            box[i].color = BLUE;
            j++;
            if (j == 10)
                j = 0;
        }

        box[i].width = 133;
        box[i].height = 30;
        box[i].active = true;
    }

    // main game loop
    while (!WindowShouldClose()) // detect window close or esc key
    {
        Rectangle angle_spot_left = {
            .x = paddle.position.x - 30,
            .y = paddle.position.y,
            .width = 20,
            .height = paddle.height};

        Rectangle paddle_rec_left = {
            .x = paddle.position.x - 10,
            .y = paddle.position.y,
            .width = paddle.width / 2,
            .height = paddle.height};

        Rectangle angle_spot_mid = {
            .x = paddle.position.x + 115,
            .y = paddle.position.y,
            .width = 40,
            .height = paddle.height};

        Rectangle paddle_rec_right = {
            .x = paddle.position.x + 155,
            .y = paddle.position.y,
            .width = paddle.width / 2,
            .height = paddle.height};

        Rectangle angle_spot_right = {
            .x = paddle.position.x + 280,
            .y = paddle.position.y,
            .width = 20,
            .height = paddle.height};

        // Rectangle box_rec = {
        //     .x = box.position.x,
        //     .y = box.position.y,
        //     .width = box.width,
        //     .height = box.height};

        // update

        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
            paddle.position.x += paddle.velocity.x;

        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
            paddle.position.x -= paddle.velocity.x;

        if (CheckCollisionCircleRec(ball.position, ball.radius, angle_spot_left))
        {
            ball.velocity.x = -3.0f;
            ball.velocity.y = -ball.velocity.y;
        }

        if (CheckCollisionCircleRec(ball.position, ball.radius, paddle_rec_left))
        {
            ball.velocity.x = -1.75f;
            ball.velocity.y = -ball.velocity.y;
        }

        if (CheckCollisionCircleRec(ball.position, ball.radius, angle_spot_mid))
        {
            ball.velocity.x = 0.5f;
            ball.velocity.y = -ball.velocity.y;
        }

        if (CheckCollisionCircleRec(ball.position, ball.radius, paddle_rec_right))
        {
            ball.velocity.x = 1.75f;
            ball.velocity.y = -ball.velocity.y;
        }

        if (CheckCollisionCircleRec(ball.position, ball.radius, angle_spot_right))
        {
            ball.velocity.x = 3.0f;
            ball.velocity.y = -ball.velocity.y;
        }

        if (ball.position.x <= 0 || ball.position.x >= GetScreenWidth())
            ball.velocity.x = -ball.velocity.x;

        if (ball.position.y <= 0)
            ball.velocity.y = -ball.velocity.y;

        else if (ball.position.y >= GetScreenHeight())
        {
            ball.position = (Vector2){screen_width / 2, screen_height / 2};
            fail_counter ++;
        }

        // if (CheckCollisionCircleRec(ball.position, ball.radius, box_rec) && box.active)
        // {
        //     ball.velocity.x = -ball.velocity.x;
        //     ball.velocity.y = -ball.velocity.y;
        //     box.active = false;
        // }

        for (int i = 0; i < 60; i++)
        {
            Rectangle box_rec = {
                .x = box[i].position.x,
                .y = box[i].position.y,
                .width = box[i].width,
                .height = box[i].height};

            if (CheckCollisionCircleRec(ball.position, ball.radius, box_rec) && box[i].active)
            {
                ball.velocity.x = ball.velocity.x;
                ball.velocity.y = -ball.velocity.y;
                box[i].active = false;
                boxes_hit_counter ++;
            };
        };

        if (boxes_hit_counter >= 36)
        {
            victory = true;
        };

        if (fail_counter >= 10)
        {
            game_over = true;
        };

        ball.position.x += ball.velocity.x;
        ball.position.y += ball.velocity.y;

        // draw
        BeginDrawing();
            if (!game_over && !victory)
            {
                ClearBackground(BLACK);

                // if (box.active)
                //     DrawRectangle(box.position.x, box.position.y, box.width, box.height, box.color);

                for (int i = 0; i < 60; i++)
                {
                    if (box[i].active)
                        DrawRectangle(box[i].position.x, box[i].position.y, box[i].width, box[i].height, box[i].color);
                };

                DrawRectangle(paddle_rec_left.x, paddle_rec_left.y, paddle_rec_left.width, paddle_rec_left.height, paddle.color);
                DrawRectangle(paddle_rec_right.x, paddle_rec_right.y, paddle_rec_right.width, paddle_rec_right.height, paddle.color);

                DrawRectangle(angle_spot_left.x, angle_spot_left.y, angle_spot_left.width, angle_spot_left.height, paddle.color);
                DrawRectangle(angle_spot_mid.x, angle_spot_mid.y, angle_spot_mid.width, angle_spot_mid.height, paddle.color);
                DrawRectangle(angle_spot_right.x, angle_spot_right.y, angle_spot_right.width, angle_spot_right.height, paddle.color);

                DrawCircle(ball.position.x, ball.position.y, ball.radius, ball.color);
            }

            else if (game_over)
            {

                ClearBackground(BLACK);
                DrawText("GAME OVER", GetScreenWidth() / 2, GetScreenHeight() / 2, 20, RED);
            }

            else if (victory)
            {

                ClearBackground(BLACK);
                DrawText("VICTORY", GetScreenWidth() / 2, GetScreenHeight() / 2, 20, GREEN);
            }
        EndDrawing();
    };
};

