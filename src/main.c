#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <filesystem.h>
#include <nds.h>
#include <NEMain.h>
#include <nf_lib.h>

#include "screens.h"
#include "sound.h"

#include "splash.h"
#include "mainmenu.h"
#include "volumeselect.h"

#include "prologue.h"

int screenFrames = 0;
char activeScreen[10] = "mainmenu";

NE_Sprite *spr[40];
NE_Material *sprMtl[40];
NE_Palette *sprPal[40];

uint32_t kHeld;
uint32_t kDown;
uint32_t kUp;

int tc;
bool pressedA;

void draw3D_top(void) {
    NE_2DViewInit();
    if (strcmp(activeScreen, "splash") == 0) {
      drawSplash();
    } else if (strcmp(activeScreen, "mainmenu") == 0) {
      drawMainMenu(1);
    } else if (strcmp(activeScreen, "volumes") == 0) {
      drawVolumeSelect(1);
    } else if (strcmp(activeScreen, "pl") == 0) {
      drawPrologue();
    }
}

void draw3D_bottom(void) {
    NE_2DViewInit();
    if (strcmp(activeScreen, "mainmenu") == 0) {
      drawMainMenu(0);
    } else if (strcmp(activeScreen, "volumes") == 0) {
      drawVolumeSelect(0);
    } 
}


void setup2D(void) {
    NF_Set2D(1, 0);
    
    NF_InitTiledBgBuffers();
    NF_InitTiledBgSys(1);
    NF_InitTextSys(1);
    
    NF_LoadTextFont("font/default", "default", 256, 256, 0);
    NF_CreateTextLayer(1, 0, 0, "default");
}


int main(void) {
    // Initialize nitroFS before doing anything else
    printf("Starting nitroFS...\n");
    if (!nitroFSInit(NULL)) {
        printf("Failed to start nitroFS\n");
        printf("Press START to exit\n");
        while (1) {
            swiWaitForVBlank();
            scanKeys();
            if (keysHeld() & KEY_START)
                return -1;
        }
    }

    swiWaitForVBlank();

    NF_SetRootFolder("NITROFS");

    // Setup interrupt handlers
    irqEnable(IRQ_HBLANK);
    irqSet(IRQ_VBLANK, NE_VBLFunc);
    irqSet(IRQ_HBLANK, NE_HBLFunc);
    
    if (strcmp(activeScreen, "mainmenu") == 0) {
      NE_InitDual3D();
    } else {
      NE_Init3D();
    }
    
    NE_InitConsole();

    for (int i = 0; i < 40; i++) {
      spr[i] = NE_SpriteCreate();
      sprMtl[i] = NE_MaterialCreate();
      sprPal[i] = NE_PaletteCreate();
    }
    
    setupSplash();
    
    soundEnable();
    NF_InitRawSoundBuffers();
    while (1) {
      printf("\x1b[2J%d\n%d", NE_TextureFreeMem(), screenFrames);
        NE_WaitForVBL(NE_UPDATE_GUI);
	screenFrames++;
	//oamUpdate(&oamSub);
        scanKeys();
        kHeld = keysHeld();
	kDown = keysDown();
	kUp = keysUp();
        // Refresh shadow OAM copy
        //NF_SpriteOamSet(1);

        // Draw 3D scene
	if (strcmp(activeScreen, "mainmenu") == 0 || strcmp(activeScreen, "volumes") == 0) {
          NE_ProcessDual(draw3D_top, draw3D_bottom);
	} else {
	  NE_Process(draw3D_top);
	}
    }
    return 0;
}
