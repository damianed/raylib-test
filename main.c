//#include <stdio.h>
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
    int size;
    int mass;
} Ball;

#define GRAVITY 9.8

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Bouncing physics");
    int current_monitor = GetCurrentMonitor();
    int refresh_rate =  GetMonitorRefreshRate(current_monitor);
    SetTargetFPS(refresh_rate);

    Vector2 pos = {
        .x  = (float) WINDOW_WIDTH/2,
        .y  = (float) WINDOW_HEIGHT/2,
    };
    Ball ball = {
        .pos  = pos,
        .size = 20,
        .mass = 5,
    };

    Vector2 ball_speed = {0, 0};

    while(!WindowShouldClose()) {
        BeginDrawing();
        {
            float dt = GetFrameTime();
            ClearBackground(RAYWHITE);
            float force = ball.mass * GRAVITY * dt;
            ball_speed.y += force;
            ball.pos.y += ball_speed.y;
            if (ball.pos.y > (WINDOW_HEIGHT - ball.size)) {
                ball_speed.y *= -0.90; // invert speed (multiply by -1) but take some for loss of energy
                ball.pos.y = (WINDOW_HEIGHT - ball.size);
            }
            DrawCircleV(*((Vector2 *) &ball), ball.size, BLUE);
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
