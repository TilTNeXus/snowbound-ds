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
#include "transforms.h"

void controlPrologue(void) {
	if (5 < screenFrames && screenFrames < 67) {
		NE_SpriteSetParams(spr[0], 34-screenFrames/2, 0, NE_White);
        if (noTransition) {
            screenFrames = 66;
            noTransition = 0;
        }
  	} else if (screenFrames == 67) {
	   	NE_SpriteVisible(spr[0], 0);
  	}
    inputPrologue();
    playBGM(songPlaying);
    transforms();
}

void inputPrologue(void) {
    if (kUp & KEY_A) {
        advance(1);
    } else if (kUp & KEY_B) {
        advance(0);
    }
}

void setupPrologue(void) {

    strcpy(activeScreen, "pl");
    strcpy(songPlaying, "secilytheme");

    //setup2D();

    screenFrames = 0;
    scriptMax = 50;

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
    
    NE_SpriteSetPos(spr[1], 0, 0);
    NE_SpriteSetPriority(spr[1], 50);

    NE_SpriteSetPos(spr[2], 0, -37);
    NE_SpriteSetPriority(spr[2], 10);

    //NF_LoadTiledBg("nf/table", "table", 256, 256);
	//NF_CreateTiledBg(1, 3, "table");
    
}

void drawPrologue(int screen) {
    if (!screen) {
        NE_SpriteDraw(spr[1]);
        NE_SpriteDraw(spr[2]);
    } else {
        NE_RichTextRender3D(0, "You proffer the dueling rapier, your\nsecond-best, to the ruffian. You took down \nhis two mates easily enough, and now he's \nthe last one standing. Unarmed and afraid.", 8, 24);
    }
}