//
//  game.c
//  Pong
//
//  Created by Sam Burkhard on 5/3/22.
//

#include "game.h"

#define DISPLAY_SCALE 2
#define WINNING_SCORE

static PlaydateAPI* pd = NULL;

// Playable Frame
const int FRAME_X = 5;
const int FRAME_Y = 5;
const int FRAME_WIDTH = (400 - 20) / DISPLAY_SCALE;
const int FRAME_HEIGHT = (240 - 20) / DISPLAY_SCALE;

typedef enum {
    active = 0,
    starting = 1,
    end = 2
} GameState;

GameState gameState = starting;

#define PADDLE_WIDTH 4
#define PADDLE_HEIGHT 20
#define PADDLE_SPEED 2

typedef struct {
    // Position
    int x;
    int y;
    int dy;
    int score;
} Paddle;

Paddle player;
Paddle opponent;

const int BALL_SPEED = 2;
const int BALL_DIAMETER = 4;

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

void initGame(void) {
        
    player.x = FRAME_X;
    player.y = 50;
    player.score = 0;

    opponent.x = 200 - (PADDLE_WIDTH + FRAME_X);
    opponent.y = 50;
    opponent.score = 0;
    
    ball.x = 100;
    ball.y = 60;
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
        paddle->dy = -(PADDLE_SPEED - 1);
    } else if ( (ball.dy > 0) && (paddle->y + PADDLE_HEIGHT) <= (FRAME_Y + FRAME_HEIGHT) && (ball.y > (paddle->y + PADDLE_HEIGHT - 5))) {
        paddle->dy = PADDLE_SPEED - 1;
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
    
    if ( (ball->y <= 0) || ( (ball->y + BALL_DIAMETER) >= 120) ) {
        ball->dy = -ball->dy;
    }
    
    if ( (ball->x <= (FRAME_X + PADDLE_WIDTH)) ) {
        
        if (ball->y >= (player.y) && ball->y <= (player.y + PADDLE_HEIGHT)) {
            ball->dx = -ball->dx;
        } else {
            gameState = starting;
            opponent.score += 1;
            checkScores();
            ball->x = 100;
            ball->y = 60;
        }

    } else if ( (ball->x + BALL_DIAMETER) >= 200 - (PADDLE_WIDTH + FRAME_X)) {
        
        if (ball->y >= (opponent.y) && ball->y <= (opponent.y + PADDLE_HEIGHT)) {
            ball->dx = -ball->dx;
        } else {
            gameState = starting;
            player.score += 1;
            checkScores();
            ball->x = 100;
            ball->y = 60;
        }
        
    }
    
    ball->x += ball->dx;
    ball->y += ball->dy;
    
}

static void drawScores() {
        
    char *string = NULL;
    pd->system->formatString(&string, "%i", player.score);
    pd->graphics->drawText(string, 2, kUTF8Encoding, 92, 10);
    
    pd->graphics->fillRect(103, 13, 1, 7, kColorBlack);
    
    pd->system->formatString(&string, "%i", opponent.score);
    pd->graphics->drawText(string, 2, kUTF8Encoding, 108, 10);
    
}

void checkScores( void ) {
    
    pd->graphics->clear(kColorWhite);
            
    if (player.score >= 10) {
        
        pd->graphics->drawText("You Win!", 8, kUTF8Encoding, 70, 50);
        pd->graphics->fillRect(0, 40, 200, 40, kColorXOR);
        
        gameState = end;
        
    } else if (opponent.score >= 10) {
        
        pd->graphics->drawText("You Lose...", 11, kUTF8Encoding, 70, 50);
        pd->graphics->fillRect(0, 40, 200, 40, kColorXOR);
        
        gameState = end;

    }
    
}

int update(void* userdata) {
    
    checkButtons(&player);
    
    if (gameState == active || gameState == starting) {
        
        pd->graphics->clear(kColorWhite);
        
        if (gameState == starting) {
            
            player.x = FRAME_X;
            player.y = 50;
            
            opponent.x = 200 - (PADDLE_WIDTH + FRAME_X);
            opponent.y = 50;
            
            ball.x = 100;
            ball.y = 60;
            
            ball.dy = -ball.dy;
            ball.dx = -ball.dx;
            
            pd->graphics->drawText("Press Ⓐ to start", 21, kUTF8Encoding, 50, 100);
            
            PDButtons current;
            pd->system->getButtonState(&current, NULL, NULL);

            
            if ( (current & kButtonA)) {
                
                pd->graphics->clear(kColorWhite);
                gameState = active;
            }
            
        } else {
            opponentAI(&opponent);
            
            updateBall(&ball);
            updatePaddle(&player);
            updatePaddle(&opponent);
        }
        
        pd->graphics->fillRect(player.x, player.y, PADDLE_WIDTH, PADDLE_HEIGHT, kColorBlack);
        
        pd->graphics->fillRect(opponent.x, opponent.y, PADDLE_WIDTH, PADDLE_HEIGHT, kColorBlack);
        
        pd->graphics->fillEllipse(ball.x, ball.y, BALL_DIAMETER, BALL_DIAMETER, 0, 360, kColorBlack);
        
        drawScores();
        
    } else {
        checkScores();
        pd->graphics->drawText("Press Ⓐ to continue", 21, kUTF8Encoding, 45, 100);
        
        PDButtons current;
        pd->system->getButtonState(&current, NULL, NULL);

        if ( (current & kButtonA)) {
            
            // Reset Game
            player.score = 0;
            opponent.score = 0;
            gameState = starting;
            pd->graphics->clear(kColorWhite);
        }
    }
    
    return 1;
}
