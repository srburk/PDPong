
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

int eventHandler(PlaydateAPI* pd, PDSystemEvent event, uint32_t arg)
{
    (void)arg; // arg is currently only used for event = kEventKeyPressed

    if ( event == kEventInit )
    {
        
        setPDPtr(pd);
        pd->display->setRefreshRate(30);
        pd->system->setUpdateCallback(update, NULL);
        initGame();

    }
    
    return 0;
}
