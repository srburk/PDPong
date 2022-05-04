//
//  game.c
//  Pong
//
//  Created by Sam Burkhard on 5/3/22.
//

#include "game.h"

static PlaydateAPI* pd = NULL;

// Playable Frame
const int FRAME_X = 10;
const int FRAME_Y = 10;
const int FRAME_WIDTH = 400 - 20;
const int FRAME_HEIGHT = 240 - 20;

#define PADDLE_WIDTH 8
#define PADDLE_HEIGHT 48
#define PADDLE_SPEED 4

typedef struct {
    // Position
    int x;
    int y;
    int dy;
} Paddle;

Paddle player;
Paddle opponent;

const int BALL_SPEED = 3;
const int BALL_DIAMETER = 9;

typedef struct {
    // Position
    int x;
    int y;
    int dx;
    int dy;
} Ball;

Ball ball;

void setPDPtr(PlaydateAPI* p) {
    pd = p;
}

void initGame() {
    player.x = FRAME_X;
    player.y = 100;

    opponent.x = 400 - (PADDLE_WIDTH + FRAME_X);
    opponent.y = 100;
    
    ball.x = 200;
    ball.y = 120;
    ball.dx = BALL_SPEED;
    ball.dy = BALL_SPEED;

    pd->system->logToConsole("Initialized Game");
    
}

void updatePaddle(Paddle *paddle) {
    
    pd->graphics->fillRect(paddle->x, paddle->y, PADDLE_WIDTH, PADDLE_HEIGHT, kColorWhite);
    
    PDButtons current;
    pd->system->getButtonState(&current, NULL, NULL);

    if ( (current & kButtonUp) && (paddle->y > FRAME_Y)) {
        paddle->dy = -PADDLE_SPEED;
    } else if ( (current & kButtonDown) && ((paddle->y + PADDLE_HEIGHT) < (FRAME_Y + FRAME_HEIGHT)) ) {
        paddle->dy = PADDLE_SPEED;
    }
    
    paddle->y += paddle->dy;
    paddle->dy = 0;
    
}

void updateBall(Ball *ball) {
    
    pd->graphics->fillEllipse(ball->x, ball->y, BALL_DIAMETER, BALL_DIAMETER, 0, 360, kColorWhite);
    
    if ( (ball->y <= 0) || ( (ball->y + BALL_DIAMETER) >= 240) ) {
        ball->dy = -ball->dy;
    }
    
    if ( (ball->x <= (FRAME_X + PADDLE_WIDTH)) ) {
        
        if (ball->y >= (player.y) && ball->y <= (player.y + PADDLE_HEIGHT)) {
            ball->dx = -ball->dx;
        } else {
            pd->system->logToConsole("Opponent Wins!");
            ball->x = 200;
            ball->y = 120;
        }

    } else if ( (ball->x + BALL_DIAMETER / 2) >= FRAME_X + FRAME_WIDTH) {
        ball->dx = -ball->dx;
    }
    
    ball->x += ball->dx;
    ball->y += ball->dy;
    
}

int update(void* userdata) {
            
    updateBall(&ball);
    updatePaddle(&player);
    
    pd->graphics->fillRect(player.x, player.y, PADDLE_WIDTH, PADDLE_HEIGHT, kColorBlack);
    
    pd->graphics->fillRect(opponent.x, opponent.y, PADDLE_WIDTH, PADDLE_HEIGHT, kColorBlack);
    
    pd->graphics->fillEllipse(ball.x, ball.y, BALL_DIAMETER, BALL_DIAMETER, 0, 360, kColorBlack);
    
    pd->system->drawFPS(0,0);

    return 1;
}
