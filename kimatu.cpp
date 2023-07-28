#include <curses.h>
#include <windows.h>
#include <cstdlib>
#include <iostream>
#include "Setting.h"
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24

int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    Ball ball = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1, 1 };
    Paddle paddle = { SCREEN_WIDTH / 2 - PADDLE_WIDTH / 2, SCREEN_HEIGHT - 2 };
    const int num_blocks = 15;
    Block blocks[num_blocks];

    for (int i = 0; i < num_blocks; ++i) {
        blocks[i].x = (i % 5) * (SCREEN_WIDTH / 5);
        blocks[i].y = (i / 5) * 2 + 1;
        blocks[i].alive = true;
    }

    while (1) {
        clear();

        handle_input(paddle);
        draw_ball(ball);
        draw_paddle(paddle);
        draw_blocks(blocks, num_blocks);

        move_ball(ball);

        // Check collisions with blocks
        for (int i = 0; i < num_blocks; ++i) {
            if (blocks[i].alive && ball.y == blocks[i].y && ball.x >= blocks[i].x && ball.x < blocks[i].x + 3) {
                blocks[i].alive = false;
                ball.dy = -ball.dy;
            }
        }

        // Check collision with paddle
        if (ball.y == paddle.y && ball.x >= paddle.x && ball.x < paddle.x + PADDLE_WIDTH) {
            ball.dy = -ball.dy;
        }

        // Check game over
        if (ball.y >= SCREEN_HEIGHT - 1) {
            mvprintw(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 5, "Game Over");
            refresh();
            Sleep(2000); // Sleep関数を使用 (ミリ秒単位)
            break;
        }

        refresh();
        Sleep(100); // Sleep関数を使用 (ミリ秒単位)
    }

    endwin();
    return 0;
}
