#include <filesystem.h>
#include <nds.h>
#include <NEMain.h>

#include "mainmenu.h"
#include "screens.h"

void setupSplash(void) {
    
    strcpy(activeScreen, "splash");
    screenFrames = -30;

    for (int i = 0; i < 7; i++) {
      spr[i] = NE_SpriteCreate();
      sprMtl[i] = NE_MaterialCreate();
      sprPal[i] = NE_PaletteCreate();
    }
    
    NE_MaterialTexLoadGRF(sprMtl[0], sprPal[0], NE_TEXGEN_TEXCOORD, "images/dcrc_splash_bg_png.grf");
    NE_SpriteSetMaterial(spr[0], sprMtl[0]);
    NE_SpriteSetPos(spr[0], 0, 0);
    NE_SpriteSetPriority(spr[0], 10);
    NE_SpriteSetParams(spr[0], 0, 0, NE_White);
    
    NE_MaterialTexLoadGRF(sprMtl[1], sprPal[1], NE_TEXGEN_TEXCOORD, "images/dcrc_splash_png.grf");
    NE_SpriteSetMaterial(spr[1], sprMtl[1]);
    NE_SpriteSetPos(spr[1], 88, 45);
    NE_SpriteSetMaterialCanvas(spr[1], 0, 0, 40, 0);
    NE_SpriteSetSize(spr[1], 40, 0);
    NE_SpriteSetPriority(spr[1], 9);

    NE_SpriteSetMaterial(spr[2], sprMtl[1]);
    NE_SpriteSetPos(spr[2], 128, 130);
    NE_SpriteSetMaterialCanvas(spr[2], 40, 85, 80, 85);
    NE_SpriteSetSize(spr[2], 40, 0);
    NE_SpriteSetPriority(spr[2], 8);

    NE_SpriteSetMaterial(spr[3], sprMtl[1]);
    NE_SpriteSetPos(spr[3], 56, 141);
    NE_SpriteSetMaterialCanvas(spr[3], 0, 93, 64, 93);
    NE_SpriteSetSize(spr[3], 64, 0);
    NE_SpriteSetPriority(spr[3], 7);
    NE_SpriteVisible(spr[3], 0);

    NE_SpriteSetMaterial(spr[4], sprMtl[1]);
    NE_SpriteSetPos(spr[4], 120, 141);
    NE_SpriteSetMaterialCanvas(spr[4], 0, 103, 81, 103);
    NE_SpriteSetSize(spr[4], 81, 0);
    NE_SpriteSetPriority(spr[4], 7);
    NE_SpriteVisible(spr[4], 0);

    NE_SpriteSetMaterial(spr[5], sprMtl[1]);
    NE_SpriteSetPos(spr[5], 56, 141);
    NE_SpriteSetMaterialCanvas(spr[5], 0, 108, 64, 118);
    NE_SpriteSetSize(spr[5], 64, 10);
    NE_SpriteSetPriority(spr[5], 6);
    NE_SpriteVisible(spr[5], 0);

    NE_SpriteSetMaterial(spr[6], sprMtl[1]);
    NE_SpriteSetPos(spr[6], 120, 141);
    NE_SpriteSetMaterialCanvas(spr[6], 0, 118, 81, 128);
    NE_SpriteSetSize(spr[6], 81, 10);
    NE_SpriteSetPriority(spr[6], 6);
    NE_SpriteVisible(spr[6], 0);
}

void drawSplash(void) {
    if (kUp & KEY_A) {
      screenFrames = 255;
    }
    NE_SpriteDraw(spr[0]);
    NE_SpriteDraw(spr[1]);
    NE_SpriteDraw(spr[2]);
    NE_SpriteDraw(spr[3]);
    NE_SpriteDraw(spr[4]);
    NE_SpriteDraw(spr[5]);
    NE_SpriteDraw(spr[6]);
    if (screenFrames < 6) {
      NE_SpriteSetParams(spr[0], 0, 0, NE_White);
    } else if (6 <= screenFrames && screenFrames < 21) {
      NE_SpriteSetParams(spr[0], (screenFrames-5)*31/15, 0, NE_White);
    } else if (30 <= screenFrames && screenFrames < 45) {
      NE_SpriteSetMaterialCanvas(spr[1], 0, 0, 40, (screenFrames-29)*85/15);
      NE_SpriteSetSize(spr[1], 40, (screenFrames-29)*85/15);
    } else if (45 <= screenFrames && screenFrames < 60) {
      NE_SpriteSetMaterialCanvas(spr[2], 40, 85, 80, 85-(screenFrames-44)*85/15);
      NE_SpriteSetSize(spr[2], 40, -(screenFrames-44)*85/15);
    } else if (75 <= screenFrames && screenFrames < 79) {
      NE_SpriteVisible(spr[3], 1);
      NE_SpriteVisible(spr[4], 1);
      NE_SpriteSetMaterialCanvas(spr[3], 0, 92, 64, 94);
      NE_SpriteSetSize(spr[3], 64, 2);
      NE_SpriteSetPos(spr[3], 56, 145);
      NE_SpriteSetMaterialCanvas(spr[4], 0, 102, 81, 104);
      NE_SpriteSetSize(spr[4], 81, 2);
      NE_SpriteSetPos(spr[4], 120, 145);
    } else if (79 <= screenFrames && screenFrames < 83) {
      NE_SpriteSetMaterialCanvas(spr[3], 0, 91, 64, 95);
      NE_SpriteSetSize(spr[3], 64, 4);
      NE_SpriteSetPos(spr[3], 56, 144);
      NE_SpriteSetMaterialCanvas(spr[4], 0, 101, 81, 105);
      NE_SpriteSetSize(spr[4], 81, 4);
      NE_SpriteSetPos(spr[4], 120, 144);
    } else if (83 <= screenFrames && screenFrames < 87) {
      NE_SpriteSetMaterialCanvas(spr[3], 0, 90, 64, 96);
      NE_SpriteSetSize(spr[3], 64, 6);
      NE_SpriteSetPos(spr[3], 56, 143);
      NE_SpriteSetMaterialCanvas(spr[4], 0, 100, 81, 106);
      NE_SpriteSetSize(spr[4], 81, 6);
      NE_SpriteSetPos(spr[4], 120, 143);
    } else if (87 <= screenFrames && screenFrames < 91) {
      NE_SpriteSetMaterialCanvas(spr[3], 0, 89, 64, 97);
      NE_SpriteSetSize(spr[3], 64, 8);
      NE_SpriteSetPos(spr[3], 56, 142);
      NE_SpriteSetMaterialCanvas(spr[4], 0, 99, 81, 107);
      NE_SpriteSetSize(spr[4], 81, 8);
      NE_SpriteSetPos(spr[4], 120, 142);
    } else if (91 <= screenFrames && screenFrames < 96) {
      NE_SpriteSetMaterialCanvas(spr[3], 0, 88, 64, 98);
      NE_SpriteSetSize(spr[3], 64, 10);
      NE_SpriteSetPos(spr[3], 56, 141);
      NE_SpriteSetMaterialCanvas(spr[4], 0, 98, 81, 108);
      NE_SpriteSetSize(spr[4], 81, 10);
      NE_SpriteSetPos(spr[4], 120, 141);
    } else if (96 <= screenFrames && screenFrames < 122) {
      if ((screenFrames & 1) == 0) {
	NE_SpriteVisible(spr[5], 1);
	NE_SpriteVisible(spr[6], 1);
      } else {
	NE_SpriteVisible(spr[5], 0);
	NE_SpriteVisible(spr[6], 0);
      }
      NE_SpriteSetParams(spr[5], (122-screenFrames)*31/26, 0, NE_White);
      NE_SpriteSetParams(spr[6], (122-screenFrames)*31/26, 0, NE_White);
    } else if (180 <= screenFrames && screenFrames < 210) {
      NE_SpriteSetParams(spr[0], -(screenFrames-209)*31/29, 0, NE_White);
      NE_SpriteSetParams(spr[1], -(screenFrames-209)*31/29, 1, NE_White);
      NE_SpriteSetParams(spr[2], -(screenFrames-209)*31/29, 2, NE_White);
      NE_SpriteSetParams(spr[3], -(screenFrames-209)*31/29, 3, NE_White);
      NE_SpriteSetParams(spr[4], -(screenFrames-209)*31/29, 4, NE_White);
    } else if (screenFrames == 210) {
      /* NE_SpriteVisible(spr[0], 0);
      NE_SpriteVisible(spr[1], 0);
      NE_SpriteVisible(spr[2], 0);
      NE_SpriteVisible(spr[3], 0);
      NE_SpriteVisible(spr[4], 0);
      NE_SpriteVisible(spr[5], 0);
      NE_SpriteVisible(spr[6], 0); */
      NE_SpriteDeleteAll();
    } else if (screenFrames == 255) {
      strcpy(activeScreen, "mainmenu");
      setupMainMenu();
    }   
}
