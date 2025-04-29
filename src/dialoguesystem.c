#include "tiny-json/tiny-json.h"

#include "screens.h"
#include "dialoguesystem.h"
#include "transforms.h"
#include "sound.h"

uint16 scriptPosition;
json_t const* parent;
char volume[6];
uint16 scriptMax;
char activeDialogue[300];

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

    //NF_DefineTextColor(1, 0, 0, 31, 31, 31); // white
    //NF_DefineTextColor(1, 0, 1, 0, 0, 0); // black

    readScript();
    
}

void createTextbox(char talking[]) {
    if (strcmp(NF_TILEDBG[1].name, "textbox") == 0) NF_UnloadTiledBg("textbox");
    NF_TEXT[1][0].pal = 0;
    if (strcmp(talking, "secily") == 0) {
        NF_LoadTiledBg("nf/textbox/secily", "textbox", 256, 256);
    } else {
        NF_TEXT[1][0].pal = 1;
        NF_LoadTiledBg("nf/textbox/narration", "textbox", 256, 256);
    }
    NF_CreateTiledBg(1, 2, "textbox");
}

void writeFormattedText(int scr, int layer, int x, int y, char s[]) {
    strcpy(activeDialogue, "");
    char out[1000];
    strcpy(out, s);
    char* word = strtok(out, " ");
    char line[40] = "";
    while (word) {
        if(strlen(line)+strlen(word)<=40-x){
            strcat(line,word);
            strcat(line," ");
        } else {
            strcat(activeDialogue, line);
            strcat(activeDialogue, "\n");
            strcpy(line, word);
            strcat(line, " ");
            y++;
        }
        word = strtok(NULL, " ");
    }
    strcat(activeDialogue, line);
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
            if (json_getProperty(scriptItem, "background")) {
                sprintf(bgSpritePath, "backgrounds/%s/%s_png.grf", volume, json_getPropertyValue(scriptItem, "background"));
            } else {
                strcpy(bgSpritePath, "");
            }
            if (json_getProperty(scriptItem, "music")) {
                if (strcmp(songPlaying, json_getPropertyValue(scriptItem, "music")) != 0) {
                    strcpy(songPlaying, json_getPropertyValue(scriptItem, "music"));
                    musOffset = screenFrames;
                    soundKill(0);
                    soundKill(1);
                    soundKill(2);
                }
            }
            characterID = 0;
            for (json_t const* charactersItem = json_getChild(json_getProperty(scriptItem, "characters")); charactersItem != 0; charactersItem = json_getSibling(charactersItem)) {
                loadedCharacters = characterID;
                if (charactersItem != 0) {
                    strcpy(character[characterID], json_getPropertyValue(charactersItem, "character"));
                    strcpy(sprite[characterID], json_getPropertyValue(charactersItem, "sprite"));
                    sprintf(charSpritePath[characterID], "characters/%s/%s_%s_png.grf", character[characterID], character[characterID], sprite[characterID]);
                    if (json_getProperty(charactersItem, "transform")) {
                        strcpy(tnamea[characterID], json_getPropertyValue(charactersItem, "transform"));
                    } else {
                        strcpy(tnamea[characterID], "");
                    }
                    characterID++;
                } else {
                    strcpy(charSpritePath[characterID], "");
                }
            }
            strcpy(textbox, json_getPropertyValue(scriptItem, "talking"));
        }
    }
    if (!strcmp(bgSpritePath, "") == 0) {
        NE_MaterialDelete(sprMtl[1]);
	    sprMtl[1] = NE_MaterialCreate();
	    NE_PaletteDelete(sprPal[1]);
	    sprPal[1] = NE_PaletteCreate();
        NE_MaterialTexLoadGRF(sprMtl[1], sprPal[1], NE_TEXGEN_TEXCOORD, bgSpritePath);
        NE_SpriteSetMaterial(spr[1], sprMtl[1]);
    }
    for (int i = 0; i <= loadedCharacters; i++) {
        if (!strcmp(charSpritePath[i], "") == 0) {
            NE_MaterialDelete(sprMtl[2+i]);
	        sprMtl[2+i] = NE_MaterialCreate();
	        NE_PaletteDelete(sprPal[2+i]);
	        sprPal[2+i] = NE_PaletteCreate();
            NE_MaterialTexLoadGRF(sprMtl[2+i], sprPal[2+i], NE_TEXGEN_TEXCOORD, charSpritePath[i]);
            NE_SpriteSetMaterial(spr[2+i], sprMtl[2+i]);
            NE_SpriteVisible(spr[2+i], 1);
            tca[i] = screenFrames;
        }
    }
    //createTextbox(textbox);
    writeFormattedText(1, 0, 1, 3, text);
}

void advance(uint8 direction) {
    if (direction == 1 && scriptPosition < scriptMax) {
        //NF_ClearTextLayer(1, 0);
        scriptPosition++;
        readScript();
    } else if (direction == 0 && 0 < scriptPosition) {
        //NF_ClearTextLayer(1, 0);
        scriptPosition--;
        readScript();
    }
}