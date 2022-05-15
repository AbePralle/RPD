// Launcher.c

#include <stdio.h>
#include <stdlib.h>

#include "pd_api.h"
#include "RogueProgram.h"

static int update( void* playdate_api );

#ifdef _WINDLL
__declspec(dllexport)
#endif
int eventHandler(PlaydateAPI* pd, PDSystemEvent event, uint32_t arg)
{
	(void)arg; // arg is currently only used for event = kEventKeyPressed

	if ( event == kEventInit )
	{
    Rogue_playdate = pd;
    Rogue_launch();

		// Note: If you set an update callback in the kEventInit handler, the system assumes the
    // game is pure C and doesn't run any Lua code in the game
		pd->system->setUpdateCallback(update, pd);
	}

	return 0;
}


#define TEXT_WIDTH 86
#define TEXT_HEIGHT 16

int x = (400-TEXT_WIDTH)/2;
int y = (240-TEXT_HEIGHT)/2;
int dx = 1;
int dy = 2;

static int update( void* playdate_api )
{
  PlaydateRoutine__render__RogueInt64( (RogueInt64)playdate_api );

/*
	PlaydateAPI* pd = userdata;

	pd->graphics->setFont(font);
  RogueString* message = RogueRoutine__hello();
	pd->graphics->drawText(message->data->as_utf8, message->data->count, kASCIIEncoding, x, y);

	x += dx;
	y += dy;

	if ( x < 0 || x > LCD_COLUMNS - TEXT_WIDTH )
		dx = -dx;

	if ( y < 0 || y > LCD_ROWS - TEXT_HEIGHT )
		dy = -dy;
*/

  Rogue_collect_garbage();  // executes GC if new allocation threshold has been reached

	return 1;
}

