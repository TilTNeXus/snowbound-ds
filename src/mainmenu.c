#include <string.h>

#include <filesystem.h>
#include <nds.h>
#include <NEMain.h>

#include "mainmenu.h"
#include "volumeselect.h"
#include "screens.h"
#include "sound.h"

int mainMenuSelect;

void mainMenuControl(void) {
    switch (mainMenuSelect) {
    	case 0:
      		NE_SpriteSetMaterialCanvas(spr[33], 0, 16, 71, 32);
      		NE_SpriteSetMaterialCanvas(spr[34], 0, 32, 71, 48);
      		NE_SpriteSetMaterialCanvas(spr[35], 71, 0, 164, 16);
      		NE_SpriteSetMaterialCanvas(spr[36], 71, 32, 190, 48);
     	 	NE_SpriteSetMaterialCanvas(spr[37], 165, 0, 256, 16);
      		NE_SpriteSetMaterialCanvas(spr[38], 192, 32, 256, 48);
      		break;
    	case 1:
     		NE_SpriteSetMaterialCanvas(spr[33], 0, 0, 71, 16);
      		NE_SpriteSetMaterialCanvas(spr[34], 0, 48, 71, 64);
      		NE_SpriteSetMaterialCanvas(spr[35], 71, 0, 164, 16);
      		NE_SpriteSetMaterialCanvas(spr[36], 71, 32, 190, 48);
      		NE_SpriteSetMaterialCanvas(spr[37], 165, 0, 256, 16);
      		NE_SpriteSetMaterialCanvas(spr[38], 192, 32, 256, 48);
      		break;
    	case 2:
      		NE_SpriteSetMaterialCanvas(spr[33], 0, 0, 71, 16);
      		NE_SpriteSetMaterialCanvas(spr[34], 0, 32, 71, 48);
      		NE_SpriteSetMaterialCanvas(spr[35], 71, 16, 164, 32);
      		NE_SpriteSetMaterialCanvas(spr[36], 71, 32, 190, 48);
      		NE_SpriteSetMaterialCanvas(spr[37], 165, 0, 256, 16);
      		NE_SpriteSetMaterialCanvas(spr[38], 192, 32, 256, 48);
      		break;
    	case 3:
      		NE_SpriteSetMaterialCanvas(spr[33], 0, 0, 71, 16);
      		NE_SpriteSetMaterialCanvas(spr[34], 0, 32, 71, 48);
      		NE_SpriteSetMaterialCanvas(spr[35], 71, 0, 164, 16);
      		NE_SpriteSetMaterialCanvas(spr[36], 71, 48, 190, 64);
      		NE_SpriteSetMaterialCanvas(spr[37], 165, 0, 256, 16);
      		NE_SpriteSetMaterialCanvas(spr[38], 192, 32, 256, 48);
      		break;
    	case 4:
      		NE_SpriteSetMaterialCanvas(spr[33], 0, 0, 71, 16);
      		NE_SpriteSetMaterialCanvas(spr[34], 0, 32, 71, 48);
      		NE_SpriteSetMaterialCanvas(spr[35], 71, 0, 164, 16);
      		NE_SpriteSetMaterialCanvas(spr[36], 71, 32, 190, 48);
      		NE_SpriteSetMaterialCanvas(spr[37], 165, 16, 256, 32);
      		NE_SpriteSetMaterialCanvas(spr[38], 192, 32, 256, 48);
      		break;
    	case 5:
      		NE_SpriteSetMaterialCanvas(spr[33], 0, 0, 71, 16);
      		NE_SpriteSetMaterialCanvas(spr[34], 0, 32, 71, 48);
      		NE_SpriteSetMaterialCanvas(spr[35], 71, 0, 164, 16);
      		NE_SpriteSetMaterialCanvas(spr[36], 71, 32, 190, 48);
      		NE_SpriteSetMaterialCanvas(spr[37], 165, 0, 256, 16);
      		NE_SpriteSetMaterialCanvas(spr[38], 192, 48, 256, 64);
      		break;
    }
    if (screenFrames - tc < 11 && !pressedA) {
      	NE_SpriteSetPos(spr[33+mainMenuSelect], 10+screenFrames-tc, 28+24*mainMenuSelect);
    }
    for (int i = 0; i < 6; i++) {
      	if (spr[33+i]->x > 10 && i != mainMenuSelect) {
			NE_SpriteSetPos(spr[33+i], spr[33+i]->x-1, 28+24*i);
      	}
    }
    if (mainMenuSelect == 0 && pressedA) {
      	if (screenFrames - tc < 91) {
			NE_SpriteSetParams(spr[0], (screenFrames-tc)*31/90, 0, NE_White);
			soundSetVolume(0, 127-(screenFrames-tc)*127/90);
			soundSetVolume(1, 127-(screenFrames-tc)*127/90);
      	} else if (screenFrames - tc == 91) {
			setupVolumeSelect();
    	}
    } else if (mainMenuSelect == 5 && pressedA) {
      	if (screenFrames - tc < 16) {
			NE_SpriteSetParams(spr[0], 1+(screenFrames-tc)*2, 0, NE_White);
			soundSetVolume(0, 127-(screenFrames-tc)*127/15);
			soundSetVolume(1, 127-(screenFrames-tc)*127/15);
      	} else if (screenFrames - tc == 20) {
			NE_End();
			//exit(0);
			systemShutDown();
      	}
    }
    if (5 < screenFrames && screenFrames < 10) {
      	NE_SpriteSetParams(spr[0], 79-screenFrames*8, 0, NE_White);
    } else if (screenFrames == 10) {
      	NE_SpriteVisible(spr[0], 0);
    }
}
void inputMainMenu(void) {
    if (kUp & KEY_UP) {
      	if (!pressedA) {
			tc = screenFrames;
			NE_SpriteVisible(spr[0], 0);
			if (0 < mainMenuSelect) {
	  			mainMenuSelect--;
			} else {
	  			mainMenuSelect = 5;
			}
      	}
    } else if (kUp & KEY_DOWN) {
      	if (!pressedA) {
			tc = screenFrames;
			NE_SpriteVisible(spr[0], 0);
			if (mainMenuSelect < 5) {
	  			mainMenuSelect++;
			} else {
	  			mainMenuSelect = 0;
			}
      	}
    } else if (kUp & KEY_A) {
      	if (!pressedA) tc = screenFrames;
      	pressedA = 1;
    	NE_SpriteVisible(spr[0], 1);
    }
		
}

void setupMainMenu(void) {
    
  //NE_InitDual3D_DMA();
    
    strcpy(activeScreen, "mainmenu");

    screenFrames = 0;
    tc = 0;
    musOffset = screenFrames;
    mainMenuSelect = 0;
    pressedA = 0;

    soundKill(0);
    soundKill(1);
    
    for (int i = 1; i < 40; i++) {
      	NE_SpriteDelete(spr[i]);
      	NE_MaterialDelete(sprMtl[i]);
      	NE_PaletteDelete(sprPal[i]);
      	spr[i] = NE_SpriteCreate();
      	sprMtl[i] = NE_MaterialCreate();
      	sprPal[i] = NE_PaletteCreate();
      	NE_SpriteSetParams(spr[i], 31, 1, NE_White);
    }

    NE_SpriteVisible(spr[0], 1);
    
    NE_MaterialTexLoadGRF(sprMtl[1], sprPal[1], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/table_png.grf");
    NE_SpriteSetMaterial(spr[1], sprMtl[1]);
    NE_SpriteSetPos(spr[1], 0, 0);
    NE_SpriteSetPriority(spr[1], 50);

    NE_MaterialTexLoadGRF(sprMtl[2], sprPal[2], NE_TEXGEN_TEXCOORD, "gui/title_idle_png.grf");
    NE_SpriteSetMaterial(spr[2], sprMtl[2]);
    NE_SpriteSetPos(spr[2], 16, 18);
    NE_SpriteSetPriority(spr[2], 2);

    NE_MaterialTexLoadGRF(sprMtl[3], sprPal[3], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v1_hamifi_png.grf");
    NE_SpriteSetMaterial(spr[3], sprMtl[3]);
    NE_SpriteSetPos(spr[3], 161, 11);
    NE_SpriteSetPriority(spr[3], 49);

    NE_MaterialTexLoadGRF(sprMtl[4], sprPal[4], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v1_sestro_1_png.grf");
    NE_SpriteSetMaterial(spr[4], sprMtl[4]);
    NE_SpriteSetPos(spr[4], 20, 5);
    NE_SpriteSetPriority(spr[4], 48);

    NE_MaterialTexLoadGRF(sprMtl[5], sprPal[5], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v1_sestro_2_png.grf");
    NE_SpriteSetMaterial(spr[5], sprMtl[5]);
    NE_SpriteSetPos(spr[5], 166, 177);
    NE_SpriteSetPriority(spr[5], 48);

    NE_MaterialTexLoadGRF(sprMtl[6], sprPal[6], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v2_rypite_png.grf");
    NE_SpriteSetMaterial(spr[6], sprMtl[6]);
    NE_SpriteSetPos(spr[6], 36, 0);
    NE_SpriteSetPriority(spr[6], 47);

    NE_MaterialTexLoadGRF(sprMtl[7], sprPal[7], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v2_sirage_png.grf");
    NE_SpriteSetMaterial(spr[7], sprMtl[7]);
    NE_SpriteSetPos(spr[7], 20, 60);
    NE_SpriteSetPriority(spr[7], 46);

    NE_MaterialTexLoadGRF(sprMtl[8], sprPal[8], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v3_bytcon_png.grf");
    NE_SpriteSetMaterial(spr[8], sprMtl[8]);
    NE_SpriteSetPos(spr[8], 121, 25);
    NE_SpriteSetPriority(spr[8], 45);

    NE_MaterialTexLoadGRF(sprMtl[9], sprPal[9], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v3_husske_png.grf");
    NE_SpriteSetMaterial(spr[9], sprMtl[9]);
    NE_SpriteSetPos(spr[9], 90, 45);
    NE_SpriteSetPriority(spr[9], 44);

    NE_MaterialTexLoadGRF(sprMtl[10], sprPal[10], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v4_endari_png.grf");
    NE_SpriteSetMaterial(spr[10], sprMtl[10]);
    NE_SpriteSetPos(spr[10], 132, 72);
    NE_SpriteSetPriority(spr[10], 43);

    NE_MaterialTexLoadGRF(sprMtl[11], sprPal[11], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v4_oricka_png.grf");
    NE_SpriteSetMaterial(spr[11], sprMtl[11]);
    NE_SpriteSetPos(spr[11], 75, 130);
    NE_SpriteSetPriority(spr[11], 42);

    NE_MaterialTexLoadGRF(sprMtl[12], sprPal[12], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v5_occeus_png.grf");
    NE_SpriteSetMaterial(spr[12], sprMtl[12]);
    NE_SpriteSetPos(spr[12], 0, 15);
    NE_SpriteSetPriority(spr[12], 41);

    NE_MaterialTexLoadGRF(sprMtl[13], sprPal[13], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v5_mshiri_png.grf");
    NE_SpriteSetMaterial(spr[13], sprMtl[13]);
    NE_SpriteSetPos(spr[13], 70, 71);
    NE_SpriteSetPriority(spr[13], 41);

    NE_MaterialTexLoadGRF(sprMtl[14], sprPal[14], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v6_raurou_png.grf");
    NE_SpriteSetMaterial(spr[14], sprMtl[14]);
    NE_SpriteSetPos(spr[14], 155, 102);
    NE_SpriteSetPriority(spr[14], 40);

    NE_MaterialTexLoadGRF(sprMtl[15], sprPal[15], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v6_cadlys_png.grf");
    NE_SpriteSetMaterial(spr[15], sprMtl[15]);
    NE_SpriteSetPos(spr[15], 0, 131);
    NE_SpriteSetPriority(spr[15], 39);

    NE_MaterialTexLoadGRF(sprMtl[16], sprPal[16], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v7_necron_png.grf");
    NE_SpriteSetMaterial(spr[16], sprMtl[16]);
    NE_SpriteSetPos(spr[16], 142, 96);
    NE_SpriteSetPriority(spr[16], 38);

    NE_MaterialTexLoadGRF(sprMtl[17], sprPal[17], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v7_gerbat_png.grf");
    NE_SpriteSetMaterial(spr[17], sprMtl[17]);
    NE_SpriteSetPos(spr[17], 0, 137);
    NE_SpriteSetPriority(spr[17], 37);
    NE_SpriteSetMaterialCanvas(spr[17], 0, 0, 64, 46);
    NE_SpriteSetSize(spr[17], 64, 46);

    NE_SpriteSetMaterial(spr[18], sprMtl[17]);
    NE_SpriteSetPos(spr[18], 138, 0);
    NE_SpriteSetPriority(spr[18], 37);
    NE_SpriteSetMaterialCanvas(spr[18], 0, 47, 64, 64);
    NE_SpriteSetSize(spr[18], 64, 17);

    NE_MaterialTexLoadGRF(sprMtl[18], sprPal[18], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v8_valtel_png.grf");
    NE_SpriteSetMaterial(spr[19], sprMtl[18]);
    NE_SpriteSetPos(spr[19], 88, 164);
    NE_SpriteSetPriority(spr[19], 36);

    NE_MaterialTexLoadGRF(sprMtl[19], sprPal[19], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v8_sabine_png.grf");
    NE_SpriteSetMaterial(spr[20], sprMtl[19]);
    NE_SpriteSetPos(spr[20], 212, 134);
    NE_SpriteSetPriority(spr[20], 35);

    NE_MaterialTexLoadGRF(sprMtl[20], sprPal[20], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v9_glomer_png.grf");
    NE_SpriteSetMaterial(spr[21], sprMtl[20]);
    NE_SpriteSetPos(spr[21], 120, 160);
    NE_SpriteSetPriority(spr[21], 34);

    NE_MaterialTexLoadGRF(sprMtl[21], sprPal[21], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v9_grubname_png.grf");
    NE_SpriteSetMaterial(spr[22], sprMtl[21]);
    NE_SpriteSetPos(spr[22], 201, 0);
    NE_SpriteSetPriority(spr[22], 33);

    NE_MaterialTexLoadGRF(sprMtl[22], sprPal[22], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v9_cinare_png.grf");
    NE_SpriteSetMaterial(spr[23], sprMtl[22]);
    NE_SpriteSetPos(spr[23], 48, 26);
    NE_SpriteSetPriority(spr[23], 32);

    NE_MaterialTexLoadGRF(sprMtl[23], sprPal[23], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v10_crytum_png.grf");
    NE_SpriteSetMaterial(spr[24], sprMtl[23]);
    NE_SpriteSetPos(spr[24], 82, 0);
    NE_SpriteSetPriority(spr[24], 31);

    NE_MaterialTexLoadGRF(sprMtl[24], sprPal[24], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v10_hayyan_png.grf");
    NE_SpriteSetMaterial(spr[25], sprMtl[24]);
    NE_SpriteSetPos(spr[25], 23, 54);
    NE_SpriteSetPriority(spr[25], 30);
    NE_SpriteSetMaterialCanvas(spr[25], 0, 0, 40, 32);
    NE_SpriteSetSize(spr[25], 40, 32);

    NE_SpriteSetMaterial(spr[26], sprMtl[24]);
    NE_SpriteSetPos(spr[26], 232, 90);
    NE_SpriteSetPriority(spr[26], 29);
    NE_SpriteSetMaterialCanvas(spr[26], 40, 0, 64, 32);
    NE_SpriteSetSize(spr[26], 24, 32);

    NE_MaterialTexLoadGRF(sprMtl[25], sprPal[25], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v11_yeshin_png.grf");
    NE_SpriteSetMaterial(spr[27], sprMtl[25]);
    NE_SpriteSetPos(spr[27], 140, 140);
    NE_SpriteSetPriority(spr[27], 28);

    NE_MaterialTexLoadGRF(sprMtl[26], sprPal[26], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v11_aumtzi_png.grf");
    NE_SpriteSetMaterial(spr[28], sprMtl[26]);
    NE_SpriteSetPos(spr[28], 18, 77);
    NE_SpriteSetPriority(spr[28], 27);

    NE_MaterialTexLoadGRF(sprMtl[27], sprPal[27], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v12_seinru_png.grf");
    NE_SpriteSetMaterial(spr[29], sprMtl[27]);
    NE_SpriteSetPos(spr[29], 192, 40);
    NE_SpriteSetPriority(spr[29], 26);

    NE_MaterialTexLoadGRF(sprMtl[28], sprPal[28], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v12_edolon_png.grf");
    NE_SpriteSetMaterial(spr[30], sprMtl[28]);
    NE_SpriteSetPos(spr[30], 80, 55);
    NE_SpriteSetPriority(spr[30], 25);

    NE_MaterialTexLoadGRF(sprMtl[29], sprPal[29], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/v12_al_png.grf");
    NE_SpriteSetMaterial(spr[31], sprMtl[29]);
    NE_SpriteSetPos(spr[31], 150, 25);
    NE_SpriteSetPriority(spr[31], 24);

    NE_MaterialTexLoadGRF(sprMtl[30], sprPal[30], NE_TEXGEN_TEXCOORD, "backgrounds/mainmenu/layers/epilogue_png.grf");
    NE_SpriteSetMaterial(spr[32], sprMtl[30]);
    NE_SpriteSetPos(spr[32], 96, 66);
    NE_SpriteSetPriority(spr[32], 23);
    
    NE_MaterialTexLoadGRF(sprMtl[31], sprPal[31], NE_TEXGEN_TEXCOORD, "gui/mainmenu_buttons_png.grf");
    NE_SpriteSetMaterial(spr[33], sprMtl[31]);
    NE_SpriteSetPos(spr[33], 20, 28);
    NE_SpriteSetMaterialCanvas(spr[33], 0, 16, 71, 32);
    NE_SpriteSetSize(spr[33], 71, 16);
    NE_SpriteSetPriority(spr[33], 1);

    NE_SpriteSetMaterial(spr[34], sprMtl[31]);
    NE_SpriteSetPos(spr[34], 10, 52);
    NE_SpriteSetMaterialCanvas(spr[34], 0, 32, 71, 48);
    NE_SpriteSetSize(spr[34], 71, 16);
    NE_SpriteSetPriority(spr[34], 2);

    NE_SpriteSetMaterial(spr[35], sprMtl[31]);
    NE_SpriteSetPos(spr[35], 10, 76);
    NE_SpriteSetMaterialCanvas(spr[35], 71, 0, 164, 16);
    NE_SpriteSetSize(spr[35], 93, 16);
    NE_SpriteSetPriority(spr[35], 3);

    NE_SpriteSetMaterial(spr[36], sprMtl[31]);
    NE_SpriteSetPos(spr[36], 10, 100);
    NE_SpriteSetMaterialCanvas(spr[36], 71, 32, 190, 48);
    NE_SpriteSetSize(spr[36], 119, 16);
    NE_SpriteSetPriority(spr[36], 4);

    NE_SpriteSetMaterial(spr[37], sprMtl[31]);
    NE_SpriteSetPos(spr[37], 10, 124);
    NE_SpriteSetMaterialCanvas(spr[37], 165, 0, 256, 16);
    NE_SpriteSetSize(spr[37], 91, 16);
    NE_SpriteSetPriority(spr[37], 5);

    NE_SpriteSetMaterial(spr[38], sprMtl[31]);
    NE_SpriteSetPos(spr[38], 10, 148);
    NE_SpriteSetMaterialCanvas(spr[38], 192, 32, 256, 48);
    NE_SpriteSetSize(spr[38], 64, 16);
    NE_SpriteSetPriority(spr[38], 6);
    
}

void drawMainMenu(int screen) {
    playBGM("mainmenu");
    inputMainMenu();
    mainMenuControl();
    if (5 < screenFrames) {
    NE_SpriteDraw(spr[1]); // table
    // top screen
    if (!screen) {
      	NE_SpriteDraw(spr[2]); // title
      	NE_SpriteDraw(spr[3]); // hamifi
      	NE_SpriteDraw(spr[6]); // rypite
      	NE_SpriteDraw(spr[8]); // bytcon
      	NE_SpriteDraw(spr[12]); // occeus
      	NE_SpriteDraw(spr[14]); // raurou
      NE_SpriteDraw(spr[16]); // necron
      NE_SpriteDraw(spr[17]); // gerbat picture
      NE_SpriteDraw(spr[19]); // valtel
      NE_SpriteDraw(spr[21]); // glomer
      NE_SpriteDraw(spr[22]); // grubname
      NE_SpriteDraw(spr[24]); // crytum
      NE_SpriteDraw(spr[26]); // clips
      NE_SpriteDraw(spr[28]); // aumtzi
      NE_SpriteDraw(spr[30]); // edolon
      NE_SpriteDraw(spr[32]); // epilogue
    } else { // bottom screen
      NE_SpriteDraw(spr[4]); // sestro lego
      NE_SpriteDraw(spr[5]); // sestro notes
      NE_SpriteDraw(spr[7]); // sirage
      NE_SpriteDraw(spr[9]); // husske
      NE_SpriteDraw(spr[10]); // endari
      NE_SpriteDraw(spr[11]); // oricka
      NE_SpriteDraw(spr[13]); // mshiri
      NE_SpriteDraw(spr[15]); // cadlys
      NE_SpriteDraw(spr[18]); // gerbat ball
      NE_SpriteDraw(spr[20]); // sabine
      NE_SpriteDraw(spr[23]); // cinare
      NE_SpriteDraw(spr[25]); // hayyan
      NE_SpriteDraw(spr[27]); // yeshin
      NE_SpriteDraw(spr[29]); // seinru
      NE_SpriteDraw(spr[31]); // al
      NE_SpriteDraw(spr[33]); // start
      NE_SpriteDraw(spr[34]); // load
      NE_SpriteDraw(spr[35]); // options
      NE_SpriteDraw(spr[36]); // trollodex
      NE_SpriteDraw(spr[37]); // credits
      NE_SpriteDraw(spr[38]); // exit
    }
    
    NE_SpriteDraw(spr[0]); // blackcover
    }
}
