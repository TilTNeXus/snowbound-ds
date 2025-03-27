#include <string.h>

#include <filesystem.h>
#include <nds.h>
#include <NEMain.h>

#include "mainmenu.h"
#include "screens.h"
#include "sound.h"

NE_Sprite *mmBG;
NE_Sprite *mmTitle;
NE_Sprite *mmObject[30];
NE_Material *mmObjMtl[30];
NE_Palette *mmObjPal[30];

void setupMainMenu(void) {
    musOffset = screenFrames;
    strcpy(activeScreen, "mainmenu");
    NE_Material *mmBGMtl = NE_MaterialCreate();
    NE_Palette *mmBGPal = NE_PaletteCreate();
    
    NE_Material *mmTitleMtl = NE_MaterialCreate();
    NE_Palette *mmTitlePal = NE_PaletteCreate();

    for (int i = 0; i < 30; i++) {
        mmObjMtl[i] = NE_MaterialCreate();
	mmObjPal[i] = NE_PaletteCreate();
    }
    
    NE_MaterialTexLoadGRF(mmBGMtl, mmBGPal, NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/table_png.grf");
    mmBG = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmBG, mmBGMtl);
    NE_SpriteSetPos(mmBG, 0, 0);
    NE_SpriteSetPriority(mmBG, 50);

    NE_MaterialTexLoadGRF(mmTitleMtl, mmTitlePal, NE_TEXGEN_TEXCOORD, "gui/title_idle_png.grf");
    mmTitle = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmTitle, mmTitleMtl);
    NE_SpriteSetPos(mmTitle, 16, 18);
    NE_SpriteSetPriority(mmTitle, 2);

    NE_MaterialTexLoadGRF(mmObjMtl[0], mmObjPal[0], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v1_hamifi_png.grf");
    mmObject[0] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[0], mmObjMtl[0]);
    NE_SpriteSetPos(mmObject[0], 161, 11);
    NE_SpriteSetPriority(mmObject[0], 49);

    NE_MaterialTexLoadGRF(mmObjMtl[1], mmObjPal[1], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v1_sestro_1_png.grf");
    mmObject[1] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[1], mmObjMtl[1]);
    NE_SpriteSetPos(mmObject[1], 20, 5);
    NE_SpriteSetPriority(mmObject[1], 48);

    NE_MaterialTexLoadGRF(mmObjMtl[2], mmObjPal[2], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v1_sestro_2_png.grf");
    mmObject[2] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[2], mmObjMtl[2]);
    NE_SpriteSetPos(mmObject[2], 166, 177);
    NE_SpriteSetPriority(mmObject[2], 48);

    NE_MaterialTexLoadGRF(mmObjMtl[3], mmObjPal[3], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v2_rypite_png.grf");
    mmObject[3] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[3], mmObjMtl[3]);
    NE_SpriteSetPos(mmObject[3], 36, 0);
    NE_SpriteSetPriority(mmObject[3], 47);

    NE_MaterialTexLoadGRF(mmObjMtl[4], mmObjPal[4], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v2_sirage_png.grf");
    mmObject[4] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[4], mmObjMtl[4]);
    NE_SpriteSetPos(mmObject[4], 20, 60);
    NE_SpriteSetPriority(mmObject[4], 46);

    NE_MaterialTexLoadGRF(mmObjMtl[5], mmObjPal[5], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v3_bytcon_png.grf");
    mmObject[5] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[5], mmObjMtl[5]);
    NE_SpriteSetPos(mmObject[5], 121, 25);
    NE_SpriteSetPriority(mmObject[5], 45);

    NE_MaterialTexLoadGRF(mmObjMtl[6], mmObjPal[6], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v3_husske_png.grf");
    mmObject[6] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[6], mmObjMtl[6]);
    NE_SpriteSetPos(mmObject[6], 90, 45);
    NE_SpriteSetPriority(mmObject[6], 44);

    NE_MaterialTexLoadGRF(mmObjMtl[7], mmObjPal[7], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v4_endari_png.grf");
    mmObject[7] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[7], mmObjMtl[7]);
    NE_SpriteSetPos(mmObject[7], 132, 72);
    NE_SpriteSetPriority(mmObject[7], 43);

    NE_MaterialTexLoadGRF(mmObjMtl[8], mmObjPal[8], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v4_oricka_png.grf");
    mmObject[8] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[8], mmObjMtl[8]);
    NE_SpriteSetPos(mmObject[8], 75, 130);
    NE_SpriteSetPriority(mmObject[8], 42);

    NE_MaterialTexLoadGRF(mmObjMtl[9], mmObjPal[9], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v5_occeus_png.grf");
    mmObject[9] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[9], mmObjMtl[9]);
    NE_SpriteSetPos(mmObject[9], 0, 15);
    NE_SpriteSetPriority(mmObject[9], 41);

    NE_MaterialTexLoadGRF(mmObjMtl[10], mmObjPal[10], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v5_mshiri_png.grf");
    mmObject[10] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[10], mmObjMtl[10]);
    NE_SpriteSetPos(mmObject[10], 70, 71);
    NE_SpriteSetPriority(mmObject[10], 41);

    NE_MaterialTexLoadGRF(mmObjMtl[11], mmObjPal[11], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v6_raurou_png.grf");
    mmObject[11] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[11], mmObjMtl[11]);
    NE_SpriteSetPos(mmObject[11], 155, 102);
    NE_SpriteSetPriority(mmObject[11], 40);

    NE_MaterialTexLoadGRF(mmObjMtl[12], mmObjPal[12], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v6_cadlys_png.grf");
    mmObject[12] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[12], mmObjMtl[12]);
    NE_SpriteSetPos(mmObject[12], 0, 131);
    NE_SpriteSetPriority(mmObject[12], 39);

    NE_MaterialTexLoadGRF(mmObjMtl[13], mmObjPal[13], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v7_necron_png.grf");
    mmObject[13] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[13], mmObjMtl[13]);
    NE_SpriteSetPos(mmObject[13], 142, 96);
    NE_SpriteSetPriority(mmObject[13], 38);

    NE_MaterialTexLoadGRF(mmObjMtl[14], mmObjPal[14], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v7_gerbat_png.grf");
    mmObject[14] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[14], mmObjMtl[14]);
    NE_SpriteSetPos(mmObject[14], 0, 137);
    NE_SpriteSetPriority(mmObject[14], 37);
    NE_SpriteSetMaterialCanvas(mmObject[14], 0, 0, 64, 46);
    NE_SpriteSetSize(mmObject[14], 64, 46);

    mmObject[15] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[15], mmObjMtl[14]);
    NE_SpriteSetPos(mmObject[15], 138, 0);
    NE_SpriteSetPriority(mmObject[15], 37);
    NE_SpriteSetMaterialCanvas(mmObject[15], 0, 47, 64, 64);
    NE_SpriteSetSize(mmObject[15], 64, 17);

    NE_MaterialTexLoadGRF(mmObjMtl[15], mmObjPal[15], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v8_valtel_png.grf");
    mmObject[16] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[16], mmObjMtl[15]);
    NE_SpriteSetPos(mmObject[16], 88, 164);
    NE_SpriteSetPriority(mmObject[16], 36);

    NE_MaterialTexLoadGRF(mmObjMtl[16], mmObjPal[16], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v8_sabine_png.grf");
    mmObject[17] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[17], mmObjMtl[16]);
    NE_SpriteSetPos(mmObject[17], 212, 134);
    NE_SpriteSetPriority(mmObject[17], 35);

    NE_MaterialTexLoadGRF(mmObjMtl[17], mmObjPal[17], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v9_glomer_png.grf");
    mmObject[18] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[18], mmObjMtl[17]);
    NE_SpriteSetPos(mmObject[18], 120, 160);
    NE_SpriteSetPriority(mmObject[18], 34);

    NE_MaterialTexLoadGRF(mmObjMtl[18], mmObjPal[18], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v9_grubname_png.grf");
    mmObject[19] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[19], mmObjMtl[18]);
    NE_SpriteSetPos(mmObject[19], 201, 0);
    NE_SpriteSetPriority(mmObject[19], 33);

    NE_MaterialTexLoadGRF(mmObjMtl[19], mmObjPal[19], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v9_cinare_png.grf");
    mmObject[20] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[20], mmObjMtl[19]);
    NE_SpriteSetPos(mmObject[20], 48, 26);
    NE_SpriteSetPriority(mmObject[20], 32);

    NE_MaterialTexLoadGRF(mmObjMtl[20], mmObjPal[20], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v10_crytum_png.grf");
    mmObject[21] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[21], mmObjMtl[20]);
    NE_SpriteSetPos(mmObject[21], 82, 0);
    NE_SpriteSetPriority(mmObject[21], 31);

    NE_MaterialTexLoadGRF(mmObjMtl[21], mmObjPal[21], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v10_hayyan_png.grf");
    mmObject[22] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[22], mmObjMtl[21]);
    NE_SpriteSetPos(mmObject[22], 23, 54);
    NE_SpriteSetPriority(mmObject[22], 30);
    NE_SpriteSetMaterialCanvas(mmObject[22], 0, 0, 40, 32);
    NE_SpriteSetSize(mmObject[22], 40, 32);

    mmObject[23] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[23], mmObjMtl[21]);
    NE_SpriteSetPos(mmObject[23], 232, 90);
    NE_SpriteSetPriority(mmObject[23], 29);
    NE_SpriteSetMaterialCanvas(mmObject[23], 40, 0, 64, 32);
    NE_SpriteSetSize(mmObject[23], 24, 32);

    NE_MaterialTexLoadGRF(mmObjMtl[22], mmObjPal[22], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v11_yeshin_png.grf");
    mmObject[24] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[24], mmObjMtl[22]);
    NE_SpriteSetPos(mmObject[24], 140, 140);
    NE_SpriteSetPriority(mmObject[24], 28);

    NE_MaterialTexLoadGRF(mmObjMtl[23], mmObjPal[23], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v11_aumtzi_png.grf");
    mmObject[25] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[25], mmObjMtl[23]);
    NE_SpriteSetPos(mmObject[25], 18, 77);
    NE_SpriteSetPriority(mmObject[25], 27);

    NE_MaterialTexLoadGRF(mmObjMtl[24], mmObjPal[24], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v12_seinru_png.grf");
    mmObject[26] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[26], mmObjMtl[24]);
    NE_SpriteSetPos(mmObject[26], 192, 40);
    NE_SpriteSetPriority(mmObject[26], 26);

    NE_MaterialTexLoadGRF(mmObjMtl[25], mmObjPal[25], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v12_edolon_png.grf");
    mmObject[27] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[27], mmObjMtl[25]);
    NE_SpriteSetPos(mmObject[27], 80, 55);
    NE_SpriteSetPriority(mmObject[27], 25);

    NE_MaterialTexLoadGRF(mmObjMtl[26], mmObjPal[26], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v12_al_png.grf");
    mmObject[28] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[28], mmObjMtl[26]);
    NE_SpriteSetPos(mmObject[28], 150, 25);
    NE_SpriteSetPriority(mmObject[28], 24);

    NE_MaterialTexLoadGRF(mmObjMtl[27], mmObjPal[27], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/epilogue_png.grf");
    mmObject[29] = NE_SpriteCreate();
    NE_SpriteSetMaterial(mmObject[29], mmObjMtl[27]);
    NE_SpriteSetPos(mmObject[29], 96, 66);
    NE_SpriteSetPriority(mmObject[29], 23);
}

void drawMainMenu(int screen) {
    playBGM("mainmenu");
    NE_SpriteDraw(mmBG);
    // top screen
    if (!screen) {
      NE_SpriteDraw(mmTitle);
      NE_SpriteDraw(mmObject[0]); // hamifi
      NE_SpriteDraw(mmObject[3]); // rypite
      NE_SpriteDraw(mmObject[5]); // bytcon
      NE_SpriteDraw(mmObject[9]); // occeus
      NE_SpriteDraw(mmObject[11]); // raurou
      NE_SpriteDraw(mmObject[13]); // necron
      NE_SpriteDraw(mmObject[14]); // gerbat picture
      NE_SpriteDraw(mmObject[16]); // valtel
      NE_SpriteDraw(mmObject[18]); // glomer
      NE_SpriteDraw(mmObject[19]); // grubname
      NE_SpriteDraw(mmObject[21]); // crytum
      NE_SpriteDraw(mmObject[23]); // clips
      NE_SpriteDraw(mmObject[25]); // aumtzi
      NE_SpriteDraw(mmObject[27]); // edolon
      NE_SpriteDraw(mmObject[29]); // epilogue
    } else { // bottom screen
      NE_SpriteDraw(mmObject[1]); // sestro lego
      NE_SpriteDraw(mmObject[2]); // sestro notes
      NE_SpriteDraw(mmObject[4]); // sirage
      NE_SpriteDraw(mmObject[6]); // husske
      NE_SpriteDraw(mmObject[7]); // endari
      NE_SpriteDraw(mmObject[8]); // oricka
      NE_SpriteDraw(mmObject[10]); // mshiri
      NE_SpriteDraw(mmObject[12]); // cadlys
      NE_SpriteDraw(mmObject[15]); // gerbat ball
      NE_SpriteDraw(mmObject[17]); // sabine
      NE_SpriteDraw(mmObject[20]); // cinare
      NE_SpriteDraw(mmObject[22]); // hayyan
      NE_SpriteDraw(mmObject[24]); // yeshin
      NE_SpriteDraw(mmObject[26]); // seinru
      NE_SpriteDraw(mmObject[28]); // al
    }
}
