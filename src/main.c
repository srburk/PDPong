
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

#define DISPLAY_SCALE 2

const char* boldFontPath = "/System/Fonts/Roobert-10-Bold.pft";
LCDFont* boldFont = NULL;

int eventHandler(PlaydateAPI* pd, PDSystemEvent event, uint32_t arg)
{
    (void)arg; // arg is currently only used for event = kEventKeyPressed

    if ( event == kEventInit )
    {
        
        const char* err;
        
        boldFont = pd->graphics->loadFont(boldFontPath, &err);
        if ( boldFont == NULL )
            pd->system->error("%s:%i Couldn't load font %s: %s", __FILE__, __LINE__, boldFontPath, err);
        
        setPDPtr(pd);
        pd->display->setRefreshRate(40);
        pd->display->setScale(DISPLAY_SCALE);
        pd->system->setUpdateCallback(update, NULL);
        pd->graphics->setFont(boldFont);
        initGame();

    }
    
    return 0;
}
