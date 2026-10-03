#include <stdio.h>
#include "raylib.h"

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH  800

typedef struct {
    int x;
    int y;
    int speed;
} Movement;

typedef struct {
    Movement movement;
    Color color;
    int x;
    int y;
    int size; //radius
} Player;


Color getRandomColor() {
    int color_index = GetRandomValue(0, 4);
    Color color;
    switch (color_index) {
        case 0: {
               color = RED;
        } break;
        case 1: {
               color = BLUE;
        } break;
        case 3: {
               color = YELLOW;
        } break;
        case 4: {
               color = GREEN;
        } break;
    }

    return color;
}

typedef struct {
    Vector2 pos;
    int radius;
    int mass;
    Color color;
} Ball;

#define GRAVITY 9.8
#define DRAG    0

Ball createBall(Vector2 pos, Color color) {
    Ball ball = {
        .pos  = pos,
        .radius = 20,
        .mass = 5,
        .color = color
    };

    return ball;
}

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Bouncing physics");
    int current_monitor = GetCurrentMonitor();
    int refresh_rate =  GetMonitorRefreshRate(current_monitor);
    SetTargetFPS(refresh_rate);

    //Vector2 pos = {
    //    .x  = (float) WINDOW_WIDTH/2,
    //    .y  = (float) WINDOW_HEIGHT/2,
    //};
#define MAX_BALLS 50
    Ball active_balls[MAX_BALLS] = {0};
    int ball_count = 0;

    Vector2 ball_speeds[MAX_BALLS] = {0};
    Color colors[] = {BLUE, GREEN, ORANGE};
    int color_index = 0;

    Ball freezed_ball = {0};

    int ball_index = 0;
    while(!WindowShouldClose()) {
        BeginDrawing();
        {
            float dt = GetFrameTime();
            ClearBackground(RAYWHITE);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 mouse_pos = GetMousePosition();
                freezed_ball = createBall(mouse_pos, colors[color_index++ % 3]);
            }

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                ball_index = ball_index % MAX_BALLS;
                Vector2 force_start = freezed_ball.pos;
                Vector2 force_end = GetMousePosition();

                float force_factor = 0.3;
                Vector2 ending_force;
                ending_force.y = (force_start.y - force_end.y) * force_factor;
                ending_force.x = (force_start.x - force_end.x) * force_factor;

                active_balls[ball_index] = freezed_ball;
                freezed_ball.radius = 0;
                ball_speeds[ball_index].y = ending_force.y;
                ball_speeds[ball_index].x = ending_force.x;
                if (ball_count < MAX_BALLS) {
                    ball_count++;
                }
                ball_index++;
            }

            if (freezed_ball.radius > 0) {
                DrawCircleV(freezed_ball.pos, freezed_ball.radius, freezed_ball.color);
            }

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                Vector2 mouse_pos = GetMousePosition();
                Vector2 start_pos = freezed_ball.pos;
                //Vector2 size;
                //size.y = mouse_pos.y - freezed_ball.pos.y;
                //size.y = size.y < 0 ? -1 * size.y : size.y;
                //size.x = mouse_pos.x - freezed_ball.pos.x;
                //size.x = size.x < 0 ? -1 * size.x : size.x;
                //printf("size.y: %f size.x %f\n", size.y, size.x);
                //if (size.y > 0 || size.x > 0) {
                //}
                DrawLineEx(start_pos, mouse_pos, 5, RED);
            }

            if (ball_count != 0) {
                for (int i = 0; i < ball_count; i++) {
                    Ball *ball = active_balls + i;
                    Vector2 *ball_speed = ball_speeds + i;

                    float force = ball->mass * GRAVITY * dt;
                    ball_speed->y += force;
                    ball->pos.y += ball_speed->y;

                    if (ball_speed->x < 0) {
                        ball_speed->x += DRAG;
                    } else if(ball_speed->x > 0) {
                        ball_speed->x -= DRAG;
                    }
                    ball->pos.x += ball_speed->x;

                    if (ball->pos.y > (WINDOW_HEIGHT - ball->radius)) {
                        ball_speed->y *= -0.9; // invert speed (multiply by -1) but take some for loss of energy
                        ball->pos.y = (WINDOW_HEIGHT - ball->radius);
                    }

                    if (ball->pos.x > (WINDOW_WIDTH - ball->radius)) {
                        ball_speed->x *= -0.9;
                        ball->pos.x = (WINDOW_WIDTH - ball->radius);
                    } else if (ball->pos.x < ball->radius) {
                        ball_speed->x *= -0.9;
                        ball->pos.x = ball->radius;
                    }

                    DrawCircleV(ball->pos, ball->radius, ball->color);
                }
            }
        } EndDrawing();
    }
}

//int main() {
//    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Raylib Game");  // Initialize window and OpenGL context
//    int current_monitor = GetCurrentMonitor();
//    int refresh_rate =  GetMonitorRefreshRate(current_monitor);
//    SetTargetFPS(refresh_rate);
//
//#define BALL_COUNT 50
//    Player balls[BALL_COUNT] = {0};
//    for (int i = 0; i < BALL_COUNT; i++) {
//        int size = 20;
//        int x = GetRandomValue(size, WINDOW_WIDTH - size);
//        int y = GetRandomValue(size, WINDOW_HEIGHT - size);
//        int x_movement = GetRandomValue(-1, 1);
//        Color color = getRandomColor();
//        balls[i] = (Player) {
//            {.x=x_movement, .y=1, .speed=10},
//            color,
//            x,
//            y,
//            size,
//        };
//    }
//
//    int max_speed = 15;
//
//    double time_since_last_random = 0;
//    while(!WindowShouldClose()) {
//        BeginDrawing();
//        {
//            ClearBackground(RAYWHITE);
//
//            int apply_random = GetTime() - time_since_last_random > 2;
//            if (apply_random) {
//                time_since_last_random = GetTime();
//            }
//            for (int i = 0; i < BALL_COUNT; i++) {
//                Player *player = balls + i;
//                int bottom_threshold = (WINDOW_HEIGHT - player->size);
//                int top_treshold = player->size;
//                int left_threshold = player->size;
//                int right_treshold = WINDOW_WIDTH - player->size;
//                if (apply_random) {
//                    int newy = GetRandomValue(-1, 1);
//                    if (newy != 0) {
//                        player->movement.y = newy;
//                    }
//                    int newx = GetRandomValue(-1, 1);
//                    if (newx != 0) {
//                        player->movement.x = newx;
//                    }
//                }
//                //TODO: use delta time
//                player->y += (player->movement.y * player->movement.speed);
//                player->x += (player->movement.x * player->movement.speed);
//
//                if (player->x >= right_treshold || player->x <= left_threshold){
//                    if (player->x >= right_treshold)  {
//                        player->x = right_treshold - (player->x - right_treshold);
//                    }  else {
//                        player->x = left_threshold + (left_threshold - player->x);
//                    }
//                    player->movement.x *= -1;
//                    if (player->movement.speed < max_speed) {
//                        player->movement.speed += 1;
//                    }
//                }
//
//                if (player->y >= bottom_threshold || player->y <= top_treshold){
//                    if (player->y >= bottom_threshold)  {
//                        player->y = bottom_threshold - (player->y - bottom_threshold);
//                    }  else {
//                        player->y = top_treshold + (top_treshold - player->y);
//                    }
//                    player->movement.y *= -1;
//                    if (player->movement.speed < max_speed) {
//                        player->movement.speed += 1;
//                    }
//                }
//
//                DrawCircle(player->x, player->y, player->size, player->color);
//            }
//
//        } EndDrawing();
//    }
//
//    CloseWindow();
//    return 0;
//}
