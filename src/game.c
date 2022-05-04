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
#define PADDLE_HEIGHT 40
#define PADDLE_SPEED 3

typedef struct {
    // Position
    int x;
    int y;
    int dy;
    int score;
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
    opponent.score = 0;

    opponent.x = 400 - (PADDLE_WIDTH + FRAME_X);
    opponent.y = 100;
    opponent.score = 0;
    
    ball.x = 200;
    ball.y = 120;
    ball.dx = BALL_SPEED;
    ball.dy = BALL_SPEED;

    pd->system->logToConsole("Initialized Game");
    
}

void updatePaddle(Paddle *paddle) {
    
    pd->graphics->fillRect(paddle->x, paddle->y, PADDLE_WIDTH, PADDLE_HEIGHT, kColorWhite);
    
    paddle->y += paddle->dy;
    paddle->dy = 0;
    
}

void opponentAI(Paddle *paddle) {
    
    if ( (ball.dy < 0) && (paddle->y >= FRAME_Y) && (ball.y < paddle->y + 5) ) {
        paddle->dy = -PADDLE_SPEED;
    } else if ( (ball.dy > 0) && (paddle->y + PADDLE_HEIGHT) <= (FRAME_Y + FRAME_HEIGHT) && (ball.y > (paddle->y + PADDLE_HEIGHT - 5))) {
        paddle->dy = PADDLE_SPEED;
    }
    
}

void checkButtons(Paddle *paddle) {
    
    PDButtons current;
    pd->system->getButtonState(&current, NULL, NULL);

    if ( (current & kButtonUp) && (paddle->y > FRAME_Y)) {
        paddle->dy = -PADDLE_SPEED;
    } else if ( (current & kButtonDown) && ((paddle->y + PADDLE_HEIGHT) < (FRAME_Y + FRAME_HEIGHT)) ) {
        paddle->dy = PADDLE_SPEED;
    }
    
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
            opponent.score += 1;
            checkScores();
            ball->x = 200;
            ball->y = 120;
        }

    } else if ( (ball->x + BALL_DIAMETER) >= 400 - (PADDLE_WIDTH + FRAME_X)) {
        
        if (ball->y >= (opponent.y) && ball->y <= (opponent.y + PADDLE_HEIGHT)) {
            ball->dx = -ball->dx;
        } else {
            player.score += 1;
            checkScores();
            ball->x = 200;
            ball->y = 120;
        }
        
    }
    
    ball->x += ball->dx;
    ball->y += ball->dy;
    
}

static void drawScores() {
        
    char *string = NULL;
    pd->system->formatString(&string, "%i", player.score);
    pd->graphics->drawText(string, 2, kUTF8Encoding, 100, 50);
    
    pd->system->formatString(&string, "%i", opponent.score);
    pd->graphics->drawText(string, 2, kUTF8Encoding, 300, 50);
}

void checkScores( void ) {
    
    pd->graphics->clear(kColorWhite);

}

int update(void* userdata) {
    
    checkButtons(&player);
    opponentAI(&opponent);
    
    updateBall(&ball);
    updatePaddle(&player);
    updatePaddle(&opponent);
    
    pd->graphics->fillRect(player.x, player.y, PADDLE_WIDTH, PADDLE_HEIGHT, kColorBlack);
    
    pd->graphics->fillRect(opponent.x, opponent.y, PADDLE_WIDTH, PADDLE_HEIGHT, kColorBlack);
    
    pd->graphics->fillEllipse(ball.x, ball.y, BALL_DIAMETER, BALL_DIAMETER, 0, 360, kColorBlack);
    
    drawScores();
    
    pd->system->drawFPS(0,0);

    return 1;
}
