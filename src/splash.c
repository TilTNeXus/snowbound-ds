#include <filesystem.h>
#include <nds.h>
#include <NEMain.h>

#include "mainmenu.h"
#include "screens.h"

NE_Sprite *splashBG;
NE_Sprite *splashDC;
NE_Sprite *splashRC;
NE_Sprite *splashSub1;
NE_Sprite *splashSub2;
NE_Sprite *splashSubInv1;
NE_Sprite *splashSubInv2;

void setupSplash(void) {
    
    NE_Material *splashBGMtl = NE_MaterialCreate();
    NE_Palette *splashBGPal = NE_PaletteCreate();
    NE_Material *splashIconMtl = NE_MaterialCreate();
    NE_Palette *splashIconPal = NE_PaletteCreate();
    strcpy(activeScreen, "splash");
    screenFrames = -30;

    NE_MaterialTexLoadGRF(splashBGMtl, splashBGPal, NE_TEXGEN_TEXCOORD, "images/dcrc_splash_bg_png.grf");
    splashBG = NE_SpriteCreate();
    NE_SpriteSetMaterial(splashBG, splashBGMtl);
    NE_SpriteSetPos(splashBG, 0, 0);
    NE_SpriteSetPriority(splashBG, 10);
    NE_SpriteSetParams(splashBG, 0, 0, NE_White);
    
    NE_MaterialTexLoadGRF(splashIconMtl, splashIconPal, NE_TEXGEN_TEXCOORD, "images/dcrc_splash_png.grf");
    splashDC = NE_SpriteCreate();
    NE_SpriteSetMaterial(splashDC, splashIconMtl);
    NE_SpriteSetPos(splashDC, 88, 45);
    NE_SpriteSetMaterialCanvas(splashDC, 0, 0, 40, 0);
    NE_SpriteSetSize(splashDC, 40, 0);
    NE_SpriteSetPriority(splashDC, 9);

    splashRC = NE_SpriteCreate();
    NE_SpriteSetMaterial(splashRC, splashIconMtl);
    NE_SpriteSetPos(splashRC, 128, 130);
    NE_SpriteSetMaterialCanvas(splashRC, 40, 85, 80, 85);
    NE_SpriteSetSize(splashRC, 40, 0);
    NE_SpriteSetPriority(splashRC, 8);

    splashSub1 = NE_SpriteCreate();
    NE_SpriteSetMaterial(splashSub1, splashIconMtl);
    NE_SpriteSetPos(splashSub1, 56, 141);
    NE_SpriteSetMaterialCanvas(splashSub1, 0, 93, 64, 93);
    NE_SpriteSetSize(splashSub1, 64, 0);
    NE_SpriteSetPriority(splashSub1, 7);
    NE_SpriteVisible(splashSub1, 0);

    splashSub2 = NE_SpriteCreate();
    NE_SpriteSetMaterial(splashSub2, splashIconMtl);
    NE_SpriteSetPos(splashSub2, 120, 141);
    NE_SpriteSetMaterialCanvas(splashSub2, 0, 103, 81, 103);
    NE_SpriteSetSize(splashSub2, 81, 0);
    NE_SpriteSetPriority(splashSub2, 7);
    NE_SpriteVisible(splashSub2, 0);

    splashSubInv1 = NE_SpriteCreate();
    NE_SpriteSetMaterial(splashSubInv1, splashIconMtl);
    NE_SpriteSetPos(splashSubInv1, 56, 141);
    NE_SpriteSetMaterialCanvas(splashSubInv1, 0, 108, 64, 118);
    NE_SpriteSetSize(splashSubInv1, 64, 10);
    NE_SpriteSetPriority(splashSubInv1, 6);
    NE_SpriteVisible(splashSubInv1, 0);

    splashSubInv2 = NE_SpriteCreate();
    NE_SpriteSetMaterial(splashSubInv2, splashIconMtl);
    NE_SpriteSetPos(splashSubInv2, 120, 141);
    NE_SpriteSetMaterialCanvas(splashSubInv2, 0, 118, 81, 128);
    NE_SpriteSetSize(splashSubInv2, 81, 10);
    NE_SpriteSetPriority(splashSubInv2, 6);
    NE_SpriteVisible(splashSubInv2, 0);
}

void drawSplash(void) {
    NE_SpriteDraw(splashBG);
    NE_SpriteDraw(splashDC);
    NE_SpriteDraw(splashRC);
    NE_SpriteDraw(splashSub1);
    NE_SpriteDraw(splashSub2);
    NE_SpriteDraw(splashSubInv1);
    NE_SpriteDraw(splashSubInv2);
    if (screenFrames < 6) {
      NE_SpriteSetParams(splashBG, 0, 0, NE_White);
    } else if (6 <= screenFrames && screenFrames < 21) {
      NE_SpriteSetParams(splashBG, (screenFrames-5)*31/15, 0, NE_White);
    } else if (30 <= screenFrames && screenFrames < 45) {
      NE_SpriteSetMaterialCanvas(splashDC, 0, 0, 40, (screenFrames-29)*85/15);
      NE_SpriteSetSize(splashDC, 40, (screenFrames-29)*85/15);
    } else if (45 <= screenFrames && screenFrames < 60) {
      NE_SpriteSetMaterialCanvas(splashRC, 40, 85, 80, 85-(screenFrames-44)*85/15);
      NE_SpriteSetSize(splashRC, 40, -(screenFrames-44)*85/15);
    } else if (75 <= screenFrames && screenFrames < 79) {
      NE_SpriteVisible(splashSub1, 1);
      NE_SpriteVisible(splashSub2, 1);
      NE_SpriteSetMaterialCanvas(splashSub1, 0, 92, 64, 94);
      NE_SpriteSetSize(splashSub1, 64, 2);
      NE_SpriteSetPos(splashSub1, 56, 145);
      NE_SpriteSetMaterialCanvas(splashSub2, 0, 102, 81, 104);
      NE_SpriteSetSize(splashSub2, 81, 2);
      NE_SpriteSetPos(splashSub2, 120, 145);
    } else if (79 <= screenFrames && screenFrames < 83) {
      NE_SpriteSetMaterialCanvas(splashSub1, 0, 91, 64, 95);
      NE_SpriteSetSize(splashSub1, 64, 4);
      NE_SpriteSetPos(splashSub1, 56, 144);
      NE_SpriteSetMaterialCanvas(splashSub2, 0, 101, 81, 105);
      NE_SpriteSetSize(splashSub2, 81, 4);
      NE_SpriteSetPos(splashSub2, 120, 144);
    } else if (83 <= screenFrames && screenFrames < 87) {
      NE_SpriteSetMaterialCanvas(splashSub1, 0, 90, 64, 96);
      NE_SpriteSetSize(splashSub1, 64, 6);
      NE_SpriteSetPos(splashSub1, 56, 143);
      NE_SpriteSetMaterialCanvas(splashSub2, 0, 100, 81, 106);
      NE_SpriteSetSize(splashSub2, 81, 6);
      NE_SpriteSetPos(splashSub2, 120, 143);
    } else if (87 <= screenFrames && screenFrames < 91) {
      NE_SpriteSetMaterialCanvas(splashSub1, 0, 89, 64, 97);
      NE_SpriteSetSize(splashSub1, 64, 8);
      NE_SpriteSetPos(splashSub1, 56, 142);
      NE_SpriteSetMaterialCanvas(splashSub2, 0, 99, 81, 107);
      NE_SpriteSetSize(splashSub2, 81, 8);
      NE_SpriteSetPos(splashSub2, 120, 142);
    } else if (91 <= screenFrames && screenFrames < 96) {
      NE_SpriteSetMaterialCanvas(splashSub1, 0, 88, 64, 98);
      NE_SpriteSetSize(splashSub1, 64, 10);
      NE_SpriteSetPos(splashSub1, 56, 141);
      NE_SpriteSetMaterialCanvas(splashSub2, 0, 98, 81, 108);
      NE_SpriteSetSize(splashSub2, 81, 10);
      NE_SpriteSetPos(splashSub2, 120, 141);
    } else if (96 <= screenFrames && screenFrames < 122) {
      if ((screenFrames & 1) == 0) {
	NE_SpriteVisible(splashSubInv1, 1);
	NE_SpriteVisible(splashSubInv2, 1);
      } else {
	NE_SpriteVisible(splashSubInv1, 0);
	NE_SpriteVisible(splashSubInv2, 0);
      }
      NE_SpriteSetParams(splashSubInv1, (122-screenFrames)*31/26, 0, NE_White);
      NE_SpriteSetParams(splashSubInv2, (122-screenFrames)*31/26, 0, NE_White);
    } else if (180 <= screenFrames && screenFrames < 210) {
      NE_SpriteSetParams(splashBG, -(screenFrames-209)*31/29, 0, NE_White);
      NE_SpriteSetParams(splashDC, -(screenFrames-209)*31/29, 1, NE_White);
      NE_SpriteSetParams(splashRC, -(screenFrames-209)*31/29, 2, NE_White);
      NE_SpriteSetParams(splashSub1, -(screenFrames-209)*31/29, 3, NE_White);
      NE_SpriteSetParams(splashSub2, -(screenFrames-209)*31/29, 4, NE_White);
    } else if (screenFrames == 210) {
      NE_SpriteVisible(splashBG, 0);
      NE_SpriteVisible(splashDC, 0);
      NE_SpriteVisible(splashRC, 0);
      NE_SpriteVisible(splashSub1, 0);
      NE_SpriteVisible(splashSub2, 0);
      NE_SpriteDeleteAll();
    } else if (screenFrames == 255) {
      strcpy(activeScreen, "mainmenu");
      setupMainMenu();
    }   
}
