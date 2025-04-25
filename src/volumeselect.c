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

void controlVolumeSelect(void) {
    if (5 < screenFrames && screenFrames < 67) {
        if (noTransition) {
            screenFrames = 66;
            noTransition = 0;
        }
      	NE_SpriteSetParams(spr[0], 34-screenFrames/2, 0, NE_White);
    } else if (screenFrames == 67) {
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
    } else if (pressedA) {
        if (screenFrames - tc < 63) {
            NE_SpriteSetParams(spr[0], (screenFrames-tc)/2, 0, NE_White);
            if ((1 < screenFrames - tc) && (kUp & KEY_A)) {
				screenFrames = tc + 61;
				noTransition = 1;
			}
        } else if (screenFrames - tc == 63) {
		    switch (volumeSelect) {
			    case 0:
				    setupPrologue();
				    break;
		    	default:
		    		break;
		    }
	    }
    } else if (pressedB) {
        if (screenFrames - tc < 8) {
            NE_SpriteSetParams(spr[0], (screenFrames-tc)*4, 0, NE_White);
        } else if (screenFrames - tc == 8) {
		    setupMainMenu();
	    }
    }
    inputVolumeSelect();
}
void inputVolumeSelect(void) {
    if (kUp & KEY_UP) {
        if (!pressedA) {
            tc = screenFrames;
            pressedA = 0;
            changed = 1;
            if (0 < volumeSelect) {
              volumeSelect--;
            }
      }   
    } else if (kUp & KEY_DOWN) {
        if (!pressedA) {
      	    tc = screenFrames;
      	    pressedA = 0;
      	    changed = 1;
      	    if (volumeSelect < 13) {
		    	volumeSelect++;
      	    }
        }   
    } else if (kUp & KEY_A) {
        if (!pressedA) tc = screenFrames;
        changed = 0;
        pressedA = 1;
        NE_SpriteVisible(spr[0], 1);
    } else if (kUp & KEY_B) {
    	changed = 0;
        pressedB = 1;
        tc = screenFrames;
        NE_SpriteVisible(spr[0], 1);
    }
}

void setupVolumeSelect(void) {

    strcpy(activeScreen, "volumes");

    screenFrames = 0;
    volumeSelect = 0;
    pressedA = 0;
    pressedB = 0;
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
    
    for (int i = 4; i < 16; i++) {
        NE_SpriteSetMaterial(spr[i], sprMtl[4]);
        NE_SpriteSetPos(spr[i], 32, 40*i-72);
        NE_SpriteSetPriority(spr[i], 22-i);
    }
}

void drawVolumeSelect(int screen) {

    NE_SpriteDraw(spr[1]);

    for (int i = 2; i < 16; i++) {
		if (!screen) NE_SpriteSetPos(spr[i], spr[i]->x, spr[i]->y+256);
		NE_SpriteDraw(spr[i]);
		if (!screen) NE_SpriteSetPos(spr[i], spr[i]->x, spr[i]->y-256);
	}

    NE_SpriteDraw(spr[0]);
}
