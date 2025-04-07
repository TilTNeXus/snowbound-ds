#include <string.h>

#include <filesystem.h>
#include <nds.h>
#include <NEMain.h>
#include <nf_lib.h>

#include "dialoguesystem.h"
#include "mainmenu.h"
#include "prologue.h"
#include "screens.h"
#include "sound.h"

void controlPrologue(void) {
	if (5 < screenFrames && screenFrames < 67) {
		NE_SpriteSetParams(spr[0], 34-screenFrames/2, 0, NE_White);
  	} else if (screenFrames == 67) {
	   	NE_SpriteVisible(spr[0], 0);
  	}
	if (pressedA) {

	}
}

void inputPrologue(void) {

}

void setupPrologue(void) {

    strcpy(activeScreen, "pl");
    strcpy(songPlaying, "secilytheme");

    setup2D();

    screenFrames = 0;

    for (int i = 1; i < 40; i++) {
		NE_MaterialDelete(sprMtl[i]);
		sprMtl[i] = NE_MaterialCreate();
		NE_PaletteDelete(sprPal[i]);
		sprPal[i] = NE_PaletteCreate();
		NE_SpriteDelete(spr[i]);
		spr[i] = NE_SpriteCreate();
		NE_SpriteSetParams(spr[i], 31, 1, NE_White);
    }

	setupDialogue("pl");

    NE_SpriteVisible(spr[0], 1);
    
    //NE_MaterialTexLoadGRF(sprMtl[1], sprPal[1], NE_TEXGEN_TEXCOORD, "backgrounds/pl/warehouse_png.grf");
    NE_SpriteSetMaterial(spr[1], sprMtl[1]);
    NE_SpriteSetPos(spr[1], 0, 0);
    NE_SpriteSetPriority(spr[1], 50);

    //NE_MaterialTexLoadGRF(sprMtl[2], sprPal[2], NE_TEXGEN_TEXCOORD, "characters/secily/secily_sword_hold_speak_png.grf");
    NE_SpriteSetMaterial(spr[2], sprMtl[2]);
    NE_SpriteSetPos(spr[2], 0, -38);
    NE_SpriteSetPriority(spr[2], 10);

    NF_LoadTiledBg("nf/table", "table", 256, 256);
	NF_CreateTiledBg(1, 3, "table");

    setupDialogue("pl");
}

void drawPrologue() {
    controlPrologue();
    inputPrologue();
    playBGM(songPlaying);

    NE_SpriteDraw(spr[1]);
    NE_SpriteDraw(spr[2]);

    NE_SpriteDraw(spr[0]);
}