
//
//  main.c
//  Extension
//
//  Created by Dave Hayden on 7/30/14.
//  Copyright (c) 2014 Panic, Inc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "pd_api.h"

#ifdef _WINDLL
__declspec(dllexport)
#endif

static int update(void* userdata);

int eventHandler(PlaydateAPI* pd, PDSystemEvent event, uint32_t arg)
{
    (void)arg; // arg is currently only used for event = kEventKeyPressed

    if ( event == kEventInit )
    {
        
        pd->display->setRefreshRate(20);
        pd->system->setUpdateCallback(update, NULL);

    }
    
    return 0;
}

static int update(void* userdata)
{
    return 1;
}

#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 60

struct Paddle {
    // Position
    int x;
    int y;
};

