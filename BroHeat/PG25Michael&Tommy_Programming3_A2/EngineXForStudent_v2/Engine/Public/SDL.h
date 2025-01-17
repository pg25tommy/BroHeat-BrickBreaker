//
// * ENGINE-X
//
// + SDL.h
// includes all of the SDL files
//

#pragma once

//-----------------------------------------------------------------
//-----------------------------------------------------------------

#include "3rdParty/SDL/SDL2-2.0.3/include/SDL.h"
#include "3rdParty/SDL/SDL2_gfx-1.0.1/SDL2_gfxPrimitives.h"
#include "3rdParty/SDL/SDL2_ttf-2.0.12/SDL_ttf.h"


const Uint32 COLLISION_EVENT_TYPE = SDL_RegisterEvents(1);

struct CollisionEventData {
	int collider1ID;
	int collider2ID;
};
