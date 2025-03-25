#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <filesystem.h>
#include <nds.h>
#include <NEMain.h>
#include <nf_lib.h>

#include "mainmenu.h"
#include "screens.h"

NE_Sprite *sprite[10];

char activeScreen[10] = "mainmenu";

void draw3D_top(void) {
    NE_2DViewInit();
    drawMainMenu(1);
}

void draw3D_bottom(void) {
    NE_2DViewInit();
    drawMainMenu(0);
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

    NE_InitDual3D();
    NE_InitConsole();
    /*setup2D();

    NF_WriteText(1, 0, 1, 1, buffer);
    NF_UpdateTextLayers();*/

    setupMainMenu();
    printf("%d", NE_TextureFreeMem());
    while (1) {
        NE_WaitForVBL(0);
	//oamUpdate(&oamSub);
        scanKeys();
        uint32_t keys = keysHeld();
	
        // Refresh shadow OAM copy
        //NF_SpriteOamSet(1);

        // Draw 3D scene
	if(strcmp(activeScreen, "mainmenu") == 0) {
        NE_ProcessDual(draw3D_top, draw3D_bottom);
	}
    }
    return 0;
}
