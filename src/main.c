#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <filesystem.h>
#include <nds.h>
#include <NEMain.h>
#include <nf_lib.h>

NE_Sprite *sprite[10];
const unsigned short iconPal[256];
#define iconPalLen 32
int angle = 0;

void draw3D(void) {
    NE_ClearColorSet(RGB15(2, 18, 21), 31, 63);
    NE_2DViewInit();
    
    NE_SpriteDraw(sprite[0]);
    NE_SpriteSetRot(sprite[0], angle);
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
    consoleDemoInit();
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

    NE_Init3D();
    setup2D();

    NF_WriteText(1, 0, 1, 1, "Hello world");
    NF_UpdateTextLayers();

    NE_Material *material = NE_MaterialCreate();
    NE_Palette *pal = NE_PaletteCreate();
    NE_MaterialTexLoadGRF(material, pal, NE_TEXGEN_TEXCOORD, "backgrounds/pl/warehouse_png.grf");
    
    sprite[0] = NE_SpriteCreate();

    NE_SpriteSetMaterial(sprite[0], material);
    NE_SpriteSetPos(sprite[0], 0, 0);
    NE_SpriteSetPriority(sprite[0], 10);

    while (1) {
        NE_WaitForVBL(NE_UPDATE_ANIMATIONS);
	oamUpdate(&oamSub);
        scanKeys();
        uint32_t keys = keysHeld();

	angle = (angle+1)%512;
	
        // Refresh shadow OAM copy
        NF_SpriteOamSet(1);

        // Draw 3D scene
        NE_Process(draw3D);
    }
    return 0;
}
