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
Paddle* player_ptr;
Paddle opponent;

void setPDPtr(PlaydateAPI* p) {
    pd = p;
}

void initGame() {
    player.x = FRAME_X;
    player.y = 30;
    player_ptr = &player;
    
    opponent.x = 400 - (PADDLE_WIDTH + FRAME_X);
    opponent.y = 100;
    
    pd->system->logToConsole("Initialized Game");
    
}

void updatePaddle(Paddle *paddle) {
    
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

int update(void* userdata) {
    
    pd->graphics->fillRect(FRAME_X, FRAME_Y, FRAME_WIDTH, FRAME_HEIGHT, kColorWhite);
        
    updatePaddle(player_ptr);
    
    pd->graphics->fillRect(player.x, player.y, PADDLE_WIDTH, PADDLE_HEIGHT, kColorBlack);
    
    pd->graphics->fillRect(opponent.x, opponent.y, PADDLE_WIDTH, PADDLE_HEIGHT, kColorBlack);
    
    // DEVELOP
    pd->system->drawFPS(0, 0);

    return 1;
}
