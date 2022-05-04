
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

#include "game.h"

#ifdef _WINDLL
__declspec(dllexport)
#endif

const char* fontpath = "/System/Fonts/Asheville-Sans-24-Light.pft";
LCDFont* font = NULL;

int eventHandler(PlaydateAPI* pd, PDSystemEvent event, uint32_t arg)
{
    (void)arg; // arg is currently only used for event = kEventKeyPressed

    if ( event == kEventInit )
    {
        
        const char* err;
        font = pd->graphics->loadFont(fontpath, &err);

        if ( font == NULL )
            pd->system->error("%s:%i Couldn't load font %s: %s", __FILE__, __LINE__, fontpath, err);
        
        setPDPtr(pd);
        pd->display->setRefreshRate(40);
        pd->system->setUpdateCallback(update, NULL);
        initGame();

    }
    
    return 0;
}
