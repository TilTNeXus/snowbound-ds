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
char activeScreen[10] = "splash";

NE_Sprite *spr[40];
NE_Material *sprMtl[40];
NE_Palette *sprPal[40];
NE_Sprite *textSpr;
NE_Material *textMtl = NULL;

uint32_t kHeld;
uint32_t kDown;
uint32_t kUp;

int tc;
bool pressedA;
bool pressedB;
char songPlaying[20] = " ";
bool noTransition = 0;
bool changed = 0;
FILE *fnt;

void draw3D_top(void) {
    NE_2DViewInit();
    if (strcmp(activeScreen, "splash") == 0) {
      	drawSplash(0);
    } else if (strcmp(activeScreen, "mainmenu") == 0) {
      	drawMainMenu(0);
    } else if (strcmp(activeScreen, "volumes") == 0) {
      	drawVolumeSelect(0);
    } else if (strcmp(activeScreen, "pl") == 0) {
      	drawPrologue(0);
    }
}

void draw3D_bottom(void) {
    NE_2DViewInit();
    if (strcmp(activeScreen, "splash") == 0) {
        drawSplash(1);
    } if (strcmp(activeScreen, "mainmenu") == 0) {
      	drawMainMenu(1);
    } else if (strcmp(activeScreen, "volumes") == 0) {
      	drawVolumeSelect(1);
    } else if (strcmp(activeScreen, "pl") == 0) {
        drawPrologue(1);
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
    
    //NE_InitConsole();

    for (int i = 0; i < 40; i++) {
      	spr[i] = NE_SpriteCreate();
      	sprMtl[i] = NE_MaterialCreate();
      	sprPal[i] = NE_PaletteCreate();
    }
    
    setupSplash();

    soundEnable();
    NF_InitRawSoundBuffers();

    fnt = fopen("font/ndsbios.fnt", "rb");

    NE_RichTextInit(0);
    NE_RichTextMetadataLoadFAT(0, "font/ndsbios.fnt");
    NE_RichTextMaterialLoadGRF(0, "font/ndsbios_0_png.grf");

    while (1) {
      	//printf("\x1b[2J%d\n%d\n", NE_TextureFreeMem(), screenFrames);
        NE_WaitForVBL(0);
		screenFrames++;
        scanKeys();
        kHeld = keysHeld();
		kDown = keysDown();
		kUp = keysUp();

        // Draw 3D scene
        if (strcmp(activeScreen, "splash") == 0) controlSplash();
        else if (strcmp(activeScreen, "mainmenu") == 0) controlMainMenu();
        else if (strcmp(activeScreen, "volumes") == 0) controlVolumeSelect();
        else if (strcmp(activeScreen, "pl") == 0) controlPrologue();
        if (strcmp(activeScreen, "splash") != 0) {
            NE_ProcessDual(draw3D_bottom, draw3D_top);
        } else {
            NE_Process(draw3D_top);
        }
        
    }
    //NE_RichTextEnd(0);
    fclose(fnt);
    return 0;
}