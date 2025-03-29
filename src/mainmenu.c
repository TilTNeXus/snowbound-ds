#include <string.h>

#include <filesystem.h>
#include <nds.h>
#include <NEMain.h>

#include "mainmenu.h"
#include "screens.h"
#include "sound.h"

int mainMenuSelect;

void mainMenuSelector(void) {
    switch (mainMenuSelect) {
    case 0:
      NE_SpriteSetMaterialCanvas(spr[32], 0, 16, 71, 32);
      NE_SpriteSetMaterialCanvas(spr[33], 0, 32, 71, 48);
      NE_SpriteSetMaterialCanvas(spr[34], 71, 0, 164, 16);
      NE_SpriteSetMaterialCanvas(spr[35], 71, 32, 190, 48);
      NE_SpriteSetMaterialCanvas(spr[36], 165, 0, 256, 16);
      NE_SpriteSetMaterialCanvas(spr[37], 192, 32, 256, 48);
      break;
    case 1:
      NE_SpriteSetMaterialCanvas(spr[32], 0, 0, 71, 16);
      NE_SpriteSetMaterialCanvas(spr[33], 0, 48, 71, 64);
      NE_SpriteSetMaterialCanvas(spr[34], 71, 0, 164, 16);
      NE_SpriteSetMaterialCanvas(spr[35], 71, 32, 190, 48);
      NE_SpriteSetMaterialCanvas(spr[36], 165, 0, 256, 16);
      NE_SpriteSetMaterialCanvas(spr[37], 192, 32, 256, 48);
      break;
    case 2:
      NE_SpriteSetMaterialCanvas(spr[32], 0, 0, 71, 16);
      NE_SpriteSetMaterialCanvas(spr[33], 0, 32, 71, 48);
      NE_SpriteSetMaterialCanvas(spr[34], 71, 16, 164, 32);
      NE_SpriteSetMaterialCanvas(spr[35], 71, 32, 190, 48);
      NE_SpriteSetMaterialCanvas(spr[36], 165, 0, 256, 16);
      NE_SpriteSetMaterialCanvas(spr[37], 192, 32, 256, 48);
      break;
    case 3:
      NE_SpriteSetMaterialCanvas(spr[32], 0, 0, 71, 16);
      NE_SpriteSetMaterialCanvas(spr[33], 0, 32, 71, 48);
      NE_SpriteSetMaterialCanvas(spr[34], 71, 0, 164, 16);
      NE_SpriteSetMaterialCanvas(spr[35], 71, 48, 190, 64);
      NE_SpriteSetMaterialCanvas(spr[36], 165, 0, 256, 16);
      NE_SpriteSetMaterialCanvas(spr[37], 192, 32, 256, 48);
      break;
    case 4:
      NE_SpriteSetMaterialCanvas(spr[32], 0, 0, 71, 16);
      NE_SpriteSetMaterialCanvas(spr[33], 0, 32, 71, 48);
      NE_SpriteSetMaterialCanvas(spr[34], 71, 0, 164, 16);
      NE_SpriteSetMaterialCanvas(spr[35], 71, 32, 190, 48);
      NE_SpriteSetMaterialCanvas(spr[36], 165, 16, 256, 32);
      NE_SpriteSetMaterialCanvas(spr[37], 192, 32, 256, 48);
      break;
    case 5:
      NE_SpriteSetMaterialCanvas(spr[32], 0, 0, 71, 16);
      NE_SpriteSetMaterialCanvas(spr[33], 0, 32, 71, 48);
      NE_SpriteSetMaterialCanvas(spr[34], 71, 0, 164, 16);
      NE_SpriteSetMaterialCanvas(spr[35], 71, 32, 190, 48);
      NE_SpriteSetMaterialCanvas(spr[36], 165, 0, 256, 16);
      NE_SpriteSetMaterialCanvas(spr[37], 192, 48, 256, 64);
      break;
    }
    if (screenFrames - tc < 11) {
      NE_SpriteSetPos(spr[32+mainMenuSelect], 10+screenFrames-tc, 28+24*mainMenuSelect);
    }
    for (int i = 0; i < 6; i++) {
      if (spr[32+i]->x > 10 && i != mainMenuSelect) {
	NE_SpriteSetPos(spr[32+i], spr[32+i]->x-1, 28+24*i);
      }
    }
}
void inputMainMenu(void) {
    if (kUp & KEY_UP) {
      tc = screenFrames;
      if (0 < mainMenuSelect) {
	mainMenuSelect--;
      } else {
	mainMenuSelect = 5;
      }
    } else if (kUp & KEY_DOWN) {
      tc = screenFrames;
      if (mainMenuSelect < 5) {
	mainMenuSelect++;
      } else {
	mainMenuSelect = 0;
      }
    }
}

void setupMainMenu(void) {
    musOffset = screenFrames;
    strcpy(activeScreen, "mainmenu");

    mainMenuSelect = 0;

    for (int i = 0; i < 38; i++) {
      NE_SpriteDelete(spr[i]);
      NE_MaterialDelete(sprMtl[i]);
      NE_PaletteDelete(sprPal[i]);
      spr[i] = NE_SpriteCreate();
      sprMtl[i] = NE_MaterialCreate();
      sprPal[i] = NE_PaletteCreate();
    }
    
    NE_MaterialTexLoadGRF(sprMtl[0], sprPal[0], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/table_png.grf");
    spr[0] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[0], sprMtl[0]);
    NE_SpriteSetPos(spr[0], 0, 0);
    NE_SpriteSetPriority(spr[0], 50);

    NE_MaterialTexLoadGRF(sprMtl[1], sprPal[1], NE_TEXGEN_TEXCOORD, "gui/title_idle_png.grf");
    spr[1] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[1], sprMtl[1]);
    NE_SpriteSetPos(spr[1], 16, 18);
    NE_SpriteSetPriority(spr[1], 2);

    NE_MaterialTexLoadGRF(sprMtl[2], sprPal[2], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v1_hamifi_png.grf");
    spr[2] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[2], sprMtl[2]);
    NE_SpriteSetPos(spr[2], 161, 11);
    NE_SpriteSetPriority(spr[2], 49);

    NE_MaterialTexLoadGRF(sprMtl[3], sprPal[3], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v1_sestro_1_png.grf");
    spr[3] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[3], sprMtl[3]);
    NE_SpriteSetPos(spr[3], 20, 5);
    NE_SpriteSetPriority(spr[3], 48);

    NE_MaterialTexLoadGRF(sprMtl[4], sprPal[4], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v1_sestro_2_png.grf");
    spr[4] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[4], sprMtl[4]);
    NE_SpriteSetPos(spr[4], 166, 177);
    NE_SpriteSetPriority(spr[4], 48);

    NE_MaterialTexLoadGRF(sprMtl[5], sprPal[5], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v2_rypite_png.grf");
    spr[5] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[5], sprMtl[5]);
    NE_SpriteSetPos(spr[5], 36, 0);
    NE_SpriteSetPriority(spr[5], 47);

    NE_MaterialTexLoadGRF(sprMtl[6], sprPal[6], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v2_sirage_png.grf");
    spr[6] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[6], sprMtl[6]);
    NE_SpriteSetPos(spr[6], 20, 60);
    NE_SpriteSetPriority(spr[6], 46);

    NE_MaterialTexLoadGRF(sprMtl[7], sprPal[7], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v3_bytcon_png.grf");
    spr[7] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[7], sprMtl[7]);
    NE_SpriteSetPos(spr[7], 121, 25);
    NE_SpriteSetPriority(spr[7], 45);

    NE_MaterialTexLoadGRF(sprMtl[8], sprPal[8], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v3_husske_png.grf");
    spr[8] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[8], sprMtl[8]);
    NE_SpriteSetPos(spr[8], 90, 45);
    NE_SpriteSetPriority(spr[8], 44);

    NE_MaterialTexLoadGRF(sprMtl[9], sprPal[9], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v4_endari_png.grf");
    spr[9] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[9], sprMtl[9]);
    NE_SpriteSetPos(spr[9], 132, 72);
    NE_SpriteSetPriority(spr[9], 43);

    NE_MaterialTexLoadGRF(sprMtl[10], sprPal[10], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v4_oricka_png.grf");
    spr[10] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[10], sprMtl[10]);
    NE_SpriteSetPos(spr[10], 75, 130);
    NE_SpriteSetPriority(spr[10], 42);

    NE_MaterialTexLoadGRF(sprMtl[11], sprPal[11], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v5_occeus_png.grf");
    spr[11] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[11], sprMtl[11]);
    NE_SpriteSetPos(spr[11], 0, 15);
    NE_SpriteSetPriority(spr[11], 41);

    NE_MaterialTexLoadGRF(sprMtl[12], sprPal[12], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v5_mshiri_png.grf");
    spr[12] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[12], sprMtl[12]);
    NE_SpriteSetPos(spr[12], 70, 71);
    NE_SpriteSetPriority(spr[12], 41);

    NE_MaterialTexLoadGRF(sprMtl[13], sprPal[13], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v6_raurou_png.grf");
    spr[13] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[13], sprMtl[13]);
    NE_SpriteSetPos(spr[13], 155, 102);
    NE_SpriteSetPriority(spr[13], 40);

    NE_MaterialTexLoadGRF(sprMtl[14], sprPal[14], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v6_cadlys_png.grf");
    spr[14] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[14], sprMtl[14]);
    NE_SpriteSetPos(spr[14], 0, 131);
    NE_SpriteSetPriority(spr[14], 39);

    NE_MaterialTexLoadGRF(sprMtl[15], sprPal[15], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v7_necron_png.grf");
    spr[15] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[15], sprMtl[15]);
    NE_SpriteSetPos(spr[15], 142, 96);
    NE_SpriteSetPriority(spr[15], 38);

    NE_MaterialTexLoadGRF(sprMtl[16], sprPal[16], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v7_gerbat_png.grf");
    spr[16] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[16], sprMtl[16]);
    NE_SpriteSetPos(spr[16], 0, 137);
    NE_SpriteSetPriority(spr[16], 37);
    NE_SpriteSetMaterialCanvas(spr[16], 0, 0, 64, 46);
    NE_SpriteSetSize(spr[16], 64, 46);

    spr[17] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[17], sprMtl[16]);
    NE_SpriteSetPos(spr[17], 138, 0);
    NE_SpriteSetPriority(spr[17], 37);
    NE_SpriteSetMaterialCanvas(spr[17], 0, 47, 64, 64);
    NE_SpriteSetSize(spr[17], 64, 17);

    NE_MaterialTexLoadGRF(sprMtl[17], sprPal[17], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v8_valtel_png.grf");
    spr[18] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[18], sprMtl[17]);
    NE_SpriteSetPos(spr[18], 88, 164);
    NE_SpriteSetPriority(spr[18], 36);

    NE_MaterialTexLoadGRF(sprMtl[18], sprPal[18], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v8_sabine_png.grf");
    spr[19] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[19], sprMtl[18]);
    NE_SpriteSetPos(spr[19], 212, 134);
    NE_SpriteSetPriority(spr[19], 35);

    NE_MaterialTexLoadGRF(sprMtl[19], sprPal[19], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v9_glomer_png.grf");
    spr[20] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[20], sprMtl[19]);
    NE_SpriteSetPos(spr[20], 120, 160);
    NE_SpriteSetPriority(spr[20], 34);

    NE_MaterialTexLoadGRF(sprMtl[20], sprPal[20], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v9_grubname_png.grf");
    spr[21] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[21], sprMtl[20]);
    NE_SpriteSetPos(spr[21], 201, 0);
    NE_SpriteSetPriority(spr[21], 33);

    NE_MaterialTexLoadGRF(sprMtl[21], sprPal[21], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v9_cinare_png.grf");
    spr[22] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[22], sprMtl[21]);
    NE_SpriteSetPos(spr[22], 48, 26);
    NE_SpriteSetPriority(spr[22], 32);

    NE_MaterialTexLoadGRF(sprMtl[22], sprPal[22], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v10_crytum_png.grf");
    spr[23] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[23], sprMtl[22]);
    NE_SpriteSetPos(spr[23], 82, 0);
    NE_SpriteSetPriority(spr[23], 31);

    NE_MaterialTexLoadGRF(sprMtl[23], sprPal[23], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v10_hayyan_png.grf");
    spr[24] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[24], sprMtl[23]);
    NE_SpriteSetPos(spr[24], 23, 54);
    NE_SpriteSetPriority(spr[24], 30);
    NE_SpriteSetMaterialCanvas(spr[24], 0, 0, 40, 32);
    NE_SpriteSetSize(spr[24], 40, 32);

    spr[25] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[25], sprMtl[23]);
    NE_SpriteSetPos(spr[25], 232, 90);
    NE_SpriteSetPriority(spr[25], 29);
    NE_SpriteSetMaterialCanvas(spr[25], 40, 0, 64, 32);
    NE_SpriteSetSize(spr[25], 24, 32);

    NE_MaterialTexLoadGRF(sprMtl[24], sprPal[24], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v11_yeshin_png.grf");
    spr[26] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[26], sprMtl[24]);
    NE_SpriteSetPos(spr[26], 140, 140);
    NE_SpriteSetPriority(spr[26], 28);

    NE_MaterialTexLoadGRF(sprMtl[25], sprPal[25], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v11_aumtzi_png.grf");
    spr[27] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[27], sprMtl[25]);
    NE_SpriteSetPos(spr[27], 18, 77);
    NE_SpriteSetPriority(spr[27], 27);

    NE_MaterialTexLoadGRF(sprMtl[26], sprPal[26], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v12_seinru_png.grf");
    spr[28] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[28], sprMtl[26]);
    NE_SpriteSetPos(spr[28], 192, 40);
    NE_SpriteSetPriority(spr[28], 26);

    NE_MaterialTexLoadGRF(sprMtl[27], sprPal[27], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v12_edolon_png.grf");
    spr[29] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[29], sprMtl[27]);
    NE_SpriteSetPos(spr[29], 80, 55);
    NE_SpriteSetPriority(spr[29], 25);

    NE_MaterialTexLoadGRF(sprMtl[28], sprPal[28], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v12_al_png.grf");
    spr[30] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[30], sprMtl[28]);
    NE_SpriteSetPos(spr[30], 150, 25);
    NE_SpriteSetPriority(spr[30], 24);

    NE_MaterialTexLoadGRF(sprMtl[29], sprPal[29], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/epilogue_png.grf");
    spr[31] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[31], sprMtl[29]);
    NE_SpriteSetPos(spr[31], 96, 66);
    NE_SpriteSetPriority(spr[31], 23);

    NE_MaterialTexLoadGRF(sprMtl[30], sprPal[30], NE_TEXGEN_TEXCOORD, "gui/mainmenu_buttons_png.grf");
    spr[32] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[32], sprMtl[30]);
    NE_SpriteSetPos(spr[32], 20, 28);
    NE_SpriteSetMaterialCanvas(spr[32], 0, 16, 71, 32);
    NE_SpriteSetSize(spr[32], 71, 16);
    NE_SpriteSetPriority(spr[32], 0);

    spr[33] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[33], sprMtl[30]);
    NE_SpriteSetPos(spr[33], 10, 52);
    NE_SpriteSetMaterialCanvas(spr[33], 0, 32, 71, 48);
    NE_SpriteSetSize(spr[33], 71, 16);
    NE_SpriteSetPriority(spr[33], 1);

    spr[34] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[34], sprMtl[30]);
    NE_SpriteSetPos(spr[34], 10, 76);
    NE_SpriteSetMaterialCanvas(spr[34], 71, 0, 164, 16);
    NE_SpriteSetSize(spr[34], 93, 16);
    NE_SpriteSetPriority(spr[34], 2);

    spr[35] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[35], sprMtl[30]);
    NE_SpriteSetPos(spr[35], 10, 100);
    NE_SpriteSetMaterialCanvas(spr[35], 71, 32, 190, 48);
    NE_SpriteSetSize(spr[35], 119, 16);
    NE_SpriteSetPriority(spr[35], 3);

    spr[36] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[36], sprMtl[30]);
    NE_SpriteSetPos(spr[36], 10, 124);
    NE_SpriteSetMaterialCanvas(spr[36], 165, 0, 256, 16);
    NE_SpriteSetSize(spr[36], 91, 16);
    NE_SpriteSetPriority(spr[36], 4);

    spr[37] = NE_SpriteCreate();
    NE_SpriteSetMaterial(spr[37], sprMtl[30]);
    NE_SpriteSetPos(spr[37], 10, 148);
    NE_SpriteSetMaterialCanvas(spr[37], 192, 32, 256, 48);
    NE_SpriteSetSize(spr[37], 64, 16);
    NE_SpriteSetPriority(spr[37], 5);
}

void drawMainMenu(int screen) {
    playBGM("mainmenu");
    inputMainMenu();
    mainMenuSelector();
    NE_SpriteDraw(spr[0]);
    // top screen
    if (!screen) {
      NE_SpriteDraw(spr[1]);
      NE_SpriteDraw(spr[2]); // hamifi
      NE_SpriteDraw(spr[5]); // rypite
      NE_SpriteDraw(spr[7]); // bytcon
      NE_SpriteDraw(spr[11]); // occeus
      NE_SpriteDraw(spr[13]); // raurou
      NE_SpriteDraw(spr[15]); // necron
      NE_SpriteDraw(spr[16]); // gerbat picture
      NE_SpriteDraw(spr[18]); // valtel
      NE_SpriteDraw(spr[20]); // glomer
      NE_SpriteDraw(spr[21]); // grubname
      NE_SpriteDraw(spr[23]); // crytum
      NE_SpriteDraw(spr[25]); // clips
      NE_SpriteDraw(spr[27]); // aumtzi
      NE_SpriteDraw(spr[29]); // edolon
      NE_SpriteDraw(spr[31]); // epilogue
    } else { // bottom screen
      NE_SpriteDraw(spr[3]); // sestro lego
      NE_SpriteDraw(spr[4]); // sestro notes
      NE_SpriteDraw(spr[6]); // sirage
      NE_SpriteDraw(spr[8]); // husske
      NE_SpriteDraw(spr[9]); // endari
      NE_SpriteDraw(spr[10]); // oricka
      NE_SpriteDraw(spr[12]); // mshiri
      NE_SpriteDraw(spr[14]); // cadlys
      NE_SpriteDraw(spr[17]); // gerbat ball
      NE_SpriteDraw(spr[19]); // sabine
      NE_SpriteDraw(spr[22]); // cinare
      NE_SpriteDraw(spr[24]); // hayyan
      NE_SpriteDraw(spr[26]); // yeshin
      NE_SpriteDraw(spr[28]); // seinru
      NE_SpriteDraw(spr[30]); // al
      NE_SpriteDraw(spr[32]); // start
      NE_SpriteDraw(spr[33]); // load
      NE_SpriteDraw(spr[34]); // options
      NE_SpriteDraw(spr[35]); // trollodex
      NE_SpriteDraw(spr[36]); // credits
      NE_SpriteDraw(spr[37]); // exit
    }
}
