#pragma once

#include <NEMain.h>
#include <nf_lib.h>

extern char activeScreen[10];
extern int screenFrames;
extern NE_Sprite *spr[40];
extern NE_Material *sprMtl[40];
extern NE_Palette *sprPal[40];
extern uint32_t kHeld;
extern uint32_t kUp;
extern uint32_t kDown;
extern int tc;
extern bool pressedA;
extern bool pressedB;
extern bool noTransition;

void draw3D_top(void);
void draw3D_bottom(void);
void setup2D(void);