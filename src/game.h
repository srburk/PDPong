//
//  game.h
//  Pong
//
//  Created by Sam Burkhard on 5/3/22.
//

#ifndef game_h
#define game_h

#include <stdio.h>
#include "pd_api.h"

int update(void* userdata);
void setPDPtr(PlaydateAPI* p);

void initGame(void);

#endif /* game_h */
