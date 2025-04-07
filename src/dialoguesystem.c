#include <filesystem.h>
#include <nds.h>
#include <NEMain.h>
#include <nf_lib.h>
#include "tiny-json/tiny-json.h"

#include "screens.h"
#include "dialoguesystem.h"

uint16 scriptPosition;

void setupDialogue(char volume[]) {
    
    scriptPosition = 0;

    FILE *scriptFile;
    char scriptFilePath[64];
    strcpy(scriptFilePath, "nitro:/scripts/");
    strcat(scriptFilePath, volume);
    strcat(scriptFilePath, ".json");

    scriptFile = fopen(scriptFilePath, "r");
    char script[1000];
    fread(script, 1, 1000, scriptFile);
    fclose(scriptFile);

    json_t jsonMemory[1000];
    json_t const* parent = json_create(script, jsonMemory, 1000);
    
    char background[16]; 
    char character[16]; 
    char sprite[32]; 

    for (json_t const* scriptItem = json_getChild(json_getProperty(parent, "script")); scriptItem != 0; scriptItem = json_getSibling(scriptItem)) {
        if (json_getInteger(json_getProperty(scriptItem, "id")) == scriptPosition) {
            NF_WriteText(1, 0, 1, 3, json_getPropertyValue(scriptItem, "dialogue"));
            strcpy(background, json_getPropertyValue(scriptItem, "background"));
            strcpy(character, json_getPropertyValue(scriptItem, "character"));
            strcpy(sprite, json_getPropertyValue(scriptItem, "sprite"));
        }
    }

    char bgSpritePath[100];
    sprintf(bgSpritePath, "backgrounds/%s/%s_png.grf", volume, background);

    NE_MaterialTexLoadGRF(sprMtl[1], sprPal[1], NE_TEXGEN_TEXCOORD, bgSpritePath);

    char charSpritePath[100];
    sprintf(charSpritePath, "characters/%s/%s_%s_png.grf", character, character, sprite);

    NE_MaterialTexLoadGRF(sprMtl[2], sprPal[2], NE_TEXGEN_TEXCOORD, charSpritePath);

}
void advance(void) {

}