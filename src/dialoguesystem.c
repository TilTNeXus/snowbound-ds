#include <filesystem.h>
#include <nds.h>
#include <NEMain.h>
#include <nf_lib.h>
#include "tiny-json/tiny-json.h"

#include "screens.h"
#include "dialoguesystem.h"

uint16 scriptPosition;
json_t const* parent;
char volume[6];
uint16 scriptMax;

void setupDialogue(char vol[]) {
    
    scriptPosition = 0;
    strcpy(volume, vol);

    FILE *scriptFile;
    char scriptFilePath[64];
    sprintf(scriptFilePath, "nitro:/scripts/%s.json", volume);

    scriptFile = fopen(scriptFilePath, "r");
    fseek(scriptFile, 0, SEEK_END);
    long scriptLength = ftell(scriptFile);
    fseek(scriptFile, 0, SEEK_SET);
    char *script = malloc(scriptLength + 1);
    fread(script, 1, scriptLength, scriptFile);
    fclose(scriptFile);
    script[scriptLength] = '\0';

    json_t jsonMemory[scriptLength];
    parent = json_create(script, jsonMemory, scriptLength);
    //free(script);

    NF_DefineTextColor(1, 0, 0, 31, 31, 31); // white
    NF_DefineTextColor(1, 0, 1, 0, 0, 0); // black

    readScript();

}

void createTextbox(char talking[]) {
    NF_TEXT[1][0].pal = 0;
    if (strcmp(talking, "narration") == 0) {
        NF_TEXT[1][0].pal = 1;
        NF_LoadTiledBg("nf/textbox/narration", "textbox", 256, 256);
    } else if (strcmp(talking, "secily") == 0) {
        NF_LoadTiledBg("nf/textbox/secily", "textbox", 256, 256);
    }
    NF_CreateTiledBg(1, 2, "textbox");
}

void writeFormattedText(int scr, int layer, int x, int y, char s[]) {
    char out[1000];
    strcpy(out,s);
    char* word = strtok(out, " ");
    char line[40] = "";
    while (word) {
        if(strlen(line)+strlen(word)<=30-x){
            strcat(line,word);
            strcat(line," ");
        } else {
            NF_WriteText(scr, layer, x, y, line);
            strcpy(line, word);
            strcat(line, " ");
            y++;
        }
        word = strtok(NULL, " ");
    }
    NF_WriteText(scr, layer, x, y, line);
}

void readScript(void) {

    char bgSpritePath[100];
    char charSpritePath[4][100];
    char character[4][16];
    char sprite[4][32];
    char textbox[16];
    char text[320];
    uint8 characterID;
    uint8 loadedCharacters = 0;

    for (json_t const* scriptItem = json_getChild(json_getProperty(parent, "script")); scriptItem != 0; scriptItem = json_getSibling(scriptItem)) {
        if (json_getInteger(json_getProperty(scriptItem, "id")) == scriptPosition) {
            strcpy(text, json_getPropertyValue(scriptItem, "dialogue"));
            sprintf(bgSpritePath, "backgrounds/%s/%s_png.grf", volume, json_getPropertyValue(scriptItem, "background"));
            characterID = 0;
            for (json_t const* charactersItem = json_getChild(json_getProperty(scriptItem, "characters")); charactersItem != 0; charactersItem = json_getSibling(charactersItem)) {
                loadedCharacters = characterID;
                strcpy(character[characterID], json_getPropertyValue(charactersItem, "character"));
                strcpy(sprite[characterID], json_getPropertyValue(charactersItem, "sprite"));
                sprintf(charSpritePath[characterID], "characters/%s/%s_%s_png.grf", character[characterID], character[characterID], sprite[characterID]);
                characterID++;
            }
            strcpy(textbox, json_getPropertyValue(scriptItem, "talking"));
        }
    }

    NE_MaterialTexLoadGRF(sprMtl[1], sprPal[1], NE_TEXGEN_TEXCOORD, bgSpritePath);
    NE_SpriteSetMaterial(spr[1], sprMtl[1]);

    for (int i = 0; i <= loadedCharacters; i++) {
        NE_MaterialTexLoadGRF(sprMtl[2+i], sprPal[2+i], NE_TEXGEN_TEXCOORD, charSpritePath[i]);
        NE_SpriteSetMaterial(spr[2+i], sprMtl[2+i]);
        NE_SpriteVisible(spr[2+i], 1);
    }
    createTextbox(textbox);
    writeFormattedText(1, 0, 1, 3, text);
}

void advance(uint8 direction) {
    NF_ClearTextLayer(1, 0);
    NF_UnloadTiledBg("textbox");
    if (direction == 1 && scriptPosition < scriptMax) {
        scriptPosition++;
    } else if (direction == 0 && 0 < scriptPosition) {
        scriptPosition--;
    }
    readScript();
}