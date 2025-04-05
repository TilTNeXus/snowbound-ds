#include <string.h>

#include <filesystem.h>
#include <nds.h>
#include <NEMain.h>

#include "mainmenu.h"
#include "volumeselect.h"
#include "prologue.h"
#include "screens.h"

int volumeSelect;
int scroll;
bool changed;

void volumeSelectControl(void) {
    if (5 < screenFrames && screenFrames < 36) {
      	NE_SpriteSetParams(spr[0], 36-screenFrames, 0, NE_White);
    } else if (screenFrames == 37) {
     	NE_SpriteVisible(spr[0], 0);
    }
    if (changed) {
      	if (scroll < volumeSelect*40) {
			scroll += 6;
      	} else if (scroll > volumeSelect*40) {
			scroll -= 6;
      	} else if (scroll == volumeSelect*40) {
			changed = 0;
      	}
      	for (int i = 0; i < 15; i++) {
			NE_SpriteSetPos(spr[2+i], 32, 8+40*i-scroll);
      	}
    }
	if (pressedA) {
		switch (volumeSelect) {
			case 0:
				setupPrologue();
				break;
			default:
				break;
		}
	}
}
void inputVolumeSelect(void) {
    if (kUp & KEY_UP) {
      	tc = screenFrames;
      	pressedA = 0;
      	changed = 1;
      	if (0 < volumeSelect) {
			volumeSelect--;
      	}
    } else if (kUp & KEY_DOWN) {
      	tc = screenFrames;
      	pressedA = 0;
      	changed = 1;
      	if (volumeSelect < 13) {
			volumeSelect++;
      	}
    } else if (kUp & KEY_A) {
    	pressedA = 1;
    	tc = screenFrames;
    } else if (kUp & KEY_B) {
    	changed = 0;
    	NE_SpriteVisible(spr[0], 1);
    	NE_SpriteSetParams(spr[0], 31, 0, NE_White);
    	setupMainMenu();
    }
}

void setupVolumeSelect(void) {

    strcpy(activeScreen, "volumes");

    screenFrames = 0;
    volumeSelect = 0;
    pressedA = 0;
    changed = 0;
    scroll = 0;

    for (int i = 1; i < 40; i++) {
		NE_MaterialDelete(sprMtl[i]);
		sprMtl[i] = NE_MaterialCreate();
		NE_PaletteDelete(sprPal[i]);
		sprPal[i] = NE_PaletteCreate();
		NE_SpriteDelete(spr[i]);
		spr[i] = NE_SpriteCreate();
		NE_SpriteSetParams(spr[i], 31, 1, NE_White);
    }

    NE_SpriteVisible(spr[0], 1);
    
    NE_MaterialTexLoadGRF(sprMtl[1], sprPal[1], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/table_dark_png.grf");
    NE_SpriteSetMaterial(spr[1], sprMtl[1]);
    NE_SpriteSetPos(spr[1], 0, 0);
    NE_SpriteSetPriority(spr[1], 50);

    NE_MaterialTexLoadGRF(sprMtl[2], sprPal[2], NE_TEXGEN_TEXCOORD, "gui/volumeselect/prologue_png.grf");
    NE_SpriteSetMaterial(spr[2], sprMtl[2]);
    NE_SpriteSetPos(spr[2], 32, 8);
    NE_SpriteSetPriority(spr[2], 20);

    NE_MaterialTexLoadGRF(sprMtl[3], sprPal[3], NE_TEXGEN_TEXCOORD, "gui/volumeselect/volumeone_png.grf");
    NE_SpriteSetMaterial(spr[3], sprMtl[3]);
    NE_SpriteSetPos(spr[3], 32, 48);
    NE_SpriteSetPriority(spr[3], 19);

    NE_MaterialTexLoadGRF(sprMtl[4], sprPal[4], NE_TEXGEN_TEXCOORD, "gui/volumeselect/upcominglocked_png.grf");
    NE_SpriteSetMaterial(spr[4], sprMtl[4]);
    NE_SpriteSetPos(spr[4], 32, 88);
    NE_SpriteSetPriority(spr[4], 18);

    NE_SpriteSetMaterial(spr[5], sprMtl[4]);
    NE_SpriteSetPos(spr[5], 32, 128);
    NE_SpriteSetPriority(spr[5], 17);

    NE_SpriteSetMaterial(spr[6], sprMtl[4]);
    NE_SpriteSetPos(spr[6], 32, 168);
    NE_SpriteSetPriority(spr[6], 17);

    NE_SpriteSetMaterial(spr[7], sprMtl[4]);
    NE_SpriteSetPos(spr[7], 32, 208);
    NE_SpriteSetPriority(spr[7], 17);

    NE_SpriteSetMaterial(spr[8], sprMtl[4]);
    NE_SpriteSetPos(spr[8], 32, 248);
    NE_SpriteSetPriority(spr[8], 17);

    NE_SpriteSetMaterial(spr[9], sprMtl[4]);
    NE_SpriteSetPos(spr[9], 32, 288);
    NE_SpriteSetPriority(spr[9], 17);

    NE_SpriteSetMaterial(spr[10], sprMtl[4]);
    NE_SpriteSetPos(spr[10], 32, 328);
    NE_SpriteSetPriority(spr[10], 17);

    NE_SpriteSetMaterial(spr[11], sprMtl[4]);
    NE_SpriteSetPos(spr[11], 32, 368);
    NE_SpriteSetPriority(spr[11], 17);

    NE_SpriteSetMaterial(spr[12], sprMtl[4]);
    NE_SpriteSetPos(spr[12], 32, 408);
    NE_SpriteSetPriority(spr[12], 17);

    NE_SpriteSetMaterial(spr[13], sprMtl[4]);
    NE_SpriteSetPos(spr[13], 32, 448);
    NE_SpriteSetPriority(spr[13], 17);

    NE_SpriteSetMaterial(spr[14], sprMtl[4]);
    NE_SpriteSetPos(spr[14], 32, 488);
    NE_SpriteSetPriority(spr[14], 17);

	NE_SpriteSetMaterial(spr[15], sprMtl[4]);
    NE_SpriteSetPos(spr[15], 32, 488);
    NE_SpriteSetPriority(spr[15], 17);

}

void drawVolumeSelect(int screen) {
    volumeSelectControl();
    inputVolumeSelect();
    NE_SpriteDraw(spr[1]);

    for (int i = 2; i < 16; i++) {
		if (!screen) NE_SpriteSetPos(spr[i], spr[i]->x, spr[i]->y+256);
		NE_SpriteDraw(spr[i]);
		if (!screen) NE_SpriteSetPos(spr[i], spr[i]->x, spr[i]->y-256);
	}

    NE_SpriteDraw(spr[0]);
}
