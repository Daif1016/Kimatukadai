#include <curses.h>
#include "Setting.h"

#define BALL_SYMBOL 'o'

void draw_ball(const Ball& ball) {
    mvaddch(ball.y, ball.x, BALL_SYMBOL);
}

void move_ball(Ball& ball) {
    ball.x += ball.dx;
    ball.y += ball.dy;

    if (ball.x <= 0 || ball.x >= SCREEN_WIDTH - 1) {
        ball.dx = -ball.dx;
    }

    if (ball.y <= 0 || ball.y >= SCREEN_HEIGHT - 1) {
        ball.dy = -ball.dy;
    }
}
#define BLOCK_SYMBOL 'X'

void draw_blocks(const Block blocks[], int num_blocks) {
    for (int i = 0; i < num_blocks; ++i) {
        if (blocks[i].alive) {
            mvaddch(blocks[i].y, blocks[i].x, BLOCK_SYMBOL);
        }
    }
}
#define PADDLE_SYMBOL '#'

void draw_paddle(const Paddle& paddle) {
    for (int i = 0; i < PADDLE_WIDTH; ++i) {
        mvaddch(paddle.y, paddle.x + i, PADDLE_SYMBOL);
    }
}

void handle_input(Paddle& paddle) {
    int ch = getch();
    switch (ch) {
    case KEY_LEFT:
        if (paddle.x > 0) {
            paddle.x--;
        }
        break;
    case KEY_RIGHT:
        if (paddle.x < SCREEN_WIDTH - PADDLE_WIDTH) {
            paddle.x++;
        }
        break;
    case 'q':
        endwin();
        
        break;
    }
}

