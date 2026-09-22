#pragma bank 255

#include <stddef.h>
#include "actor.h"
#include "vm.h"

static upoint16_t followPos[16];
static upoint16_t lastPos;
static UBYTE followStep;

void resetAlien(SCRIPT_CTX * THIS) OLDCALL BANKED {
    UBYTE i;
    THIS;
    followStep = 0;
    lastPos = PLAYER.pos;
    for (i = 0; i != 16; ++i) followPos[i] = PLAYER.pos;
}

void followAlien(SCRIPT_CTX * THIS) OLDCALL BANKED {
    actor_t * alien;
    if (!THIS->hthread) return;
    if (PLAYER.pos.x == lastPos.x &&
        PLAYER.pos.y == lastPos.y) return;

    alien = (actor_t *)((UBYTE *)THIS->hthread - offsetof(actor_t, hscript_update));
    alien->pos = followPos[followStep];
    followPos[followStep] = PLAYER.pos;
    followStep = (followStep + 1) & 15;
    lastPos = PLAYER.pos;
}
