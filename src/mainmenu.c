#include <string.h>

#include <filesystem.h>
#include <nds.h>
#include <NEMain.h>
#include <nf_lib.h>

#include "mainmenu.h"
#include "screens.h"

NE_Sprite *mmBG;
NE_Sprite *mmTitle;
NE_Sprite *mmObject[30];

void setupMainMenu(void) {
    strcpy(activeScreen, "mainmenu");
    NE_Material *mmBGMtl = NE_MaterialCreate();
    NE_Palette *mmBGPal = NE_PaletteCreate();
    
    NE_Material *mmTitleMtl = NE_MaterialCreate();
    NE_Palette *mmTitlePal = NE_PaletteCreate();
    
    NE_Material *mm0Mtl = NE_MaterialCreate();
    NE_Palette *mm0Pal = NE_PaletteCreate();

    NE_Material *mm1Mtl = NE_MaterialCreate();
    NE_Palette *mm1Pal = NE_PaletteCreate();
    
    NE_Material *mm2Mtl = NE_MaterialCreate();
    NE_Palette *mm2Pal = NE_PaletteCreate();

    NE_Material *mm3Mtl = NE_MaterialCreate();
    NE_Palette *mm3Pal = NE_PaletteCreate();

    
    NE_MaterialTexLoadGRF(mmBGMtl, mmBGPal, NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/table_png.grf");
    mmBG = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmBG, mmBGMtl);
    NE_SpriteSetPos(mmBG, 0, 0);
    NE_SpriteSetPriority(mmBG, 50);

    NE_MaterialTexLoadGRF(mmTitleMtl, mmTitlePal, NE_TEXGEN_TEXCOORD, "gui/title_idle_png.grf");
    mmTitle = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmTitle, mmTitleMtl);
    NE_SpriteSetPos(mmTitle, 16, 24);
    NE_SpriteSetPriority(mmTitle, 2);

    NE_MaterialTexLoadGRF(mm0Mtl, mm0Pal, NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v1_hamifi_png.grf");
    mmObject[0] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[0], mm0Mtl);
    NE_SpriteSetPos(mmObject[0], 160, 11);
    NE_SpriteSetPriority(mmObject[0], 49);

    NE_MaterialTexLoadGRF(mm1Mtl, mm1Pal, NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v1_sestro_png.grf");
    mmObject[1] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[1], mm1Mtl);
    NE_SpriteSetPos(mmObject[1], 0, 0);
    NE_SpriteSetPriority(mmObject[1], 48);

    NE_MaterialTexLoadGRF(mm2Mtl, mm2Pal, NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v2_rypite_png.grf");
    mmObject[2] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[2], mm2Mtl);
    NE_SpriteSetPos(mmObject[2], 36, 0);
    NE_SpriteSetPriority(mmObject[2], 47);

    NE_MaterialTexLoadGRF(mm3Mtl, mm3Pal, NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v2_sirage_png.grf");
    mmObject[3] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[3], mm3Mtl);
    NE_SpriteSetPos(mmObject[3], 20, 50);
    NE_SpriteSetPriority(mmObject[3], 46);
}

void drawMainMenu(int screen) {
    NE_SpriteDraw(mmBG);
    if (!screen) {
      NE_SpriteDraw(mmTitle);
      NE_SpriteDraw(mmObject[0]);
      NE_SpriteDraw(mmObject[2]);
    } else {
      NE_SpriteDraw(mmObject[1]);
      NE_SpriteDraw(mmObject[3]);
    }
}
