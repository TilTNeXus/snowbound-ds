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
int startSprite = 3;

/*  go through the script, get every unique character sprite and background, 
    store pointers to sprites, materials, and palettes alongside the name to identify them for later use
*/
void loadSprites(void) {
    
    loadedCharSprites = 0;
    for (json_t const* scriptItem = json_getChild(json_getProperty(parent, "script")); scriptItem != 0; scriptItem = json_getSibling(scriptItem)) {
        char bgName[32];
        char bgPath[64];
        strcpy(bgName, json_getPropertyValue(scriptItem, "bg"));
        sprintf(bgPath, "backgrounds/%s/%s_png.grf", volume, bgName);
        bool hasBeenLoaded = 0;
        for (int i = 0; i < MAX_CHARSPRITES; i++) {
            if (strcmp(charSprites[i].name, bgName) == 0) {
                hasBeenLoaded = 1;
                break;
            }
        }
        if (!hasBeenLoaded) {
            NE_MaterialDelete(sprMtl[startSprite+loadedCharSprites]);
            sprMtl[startSprite+loadedCharSprites] = NE_MaterialCreate();
            NE_PaletteDelete(sprPal[startSprite+loadedCharSprites]);
            sprPal[startSprite+loadedCharSprites] = NE_PaletteCreate();
            NE_MaterialTexLoadGRF(sprMtl[startSprite+loadedCharSprites], sprPal[startSprite+loadedCharSprites], NE_TEXGEN_TEXCOORD, bgPath);
            NE_SpriteSetMaterial(spr[startSprite+loadedCharSprites], sprMtl[startSprite+loadedCharSprites]);
            NE_SpriteVisible(spr[startSprite+loadedCharSprites], 1);
            NE_SpriteSetPos(spr[startSprite+loadedCharSprites], 0, 0);
            NE_SpriteSetPriority(spr[startSprite+loadedCharSprites], 50);
            charSprites[loadedCharSprites].sprite = &spr[startSprite+loadedCharSprites];
            charSprites[loadedCharSprites].mtl = &sprMtl[startSprite+loadedCharSprites];
            charSprites[loadedCharSprites].pal = &sprPal[startSprite+loadedCharSprites];
            strcpy(charSprites[loadedCharSprites].name, bgName);
            loadedCharSprites++;
        }

        for (json_t const* charactersItem = json_getChild(json_getProperty(scriptItem, "chrs")); charactersItem != 0; charactersItem = json_getSibling(charactersItem)) {
            char charSpriteName[32];
            char charSpritePath[64];
            char charName[16];
            char charSprite[32];
            if (charactersItem != 0) {
                strcpy(charName, json_getPropertyValue(charactersItem, "chr"));
                strcpy(charSprite, json_getPropertyValue(charactersItem, "spr"));
                sprintf(charSpriteName, "%s_%s", charName, charSprite);
                sprintf(charSpritePath, "characters/%s/%s_png.grf", charName, charSpriteName);

                hasBeenLoaded = 0;
                for (int i = 0; i < MAX_CHARSPRITES; i++) {
                    if (strcmp(charSprites[i].name, charSpriteName) == 0) {
                        hasBeenLoaded = 1;
                        break;
                    }
                }

                if (!hasBeenLoaded) {
                    NE_MaterialDelete(sprMtl[startSprite+loadedCharSprites]);
                    sprMtl[startSprite+loadedCharSprites] = NE_MaterialCreate();
                    NE_PaletteDelete(sprPal[startSprite+loadedCharSprites]);
                    sprPal[startSprite+loadedCharSprites] = NE_PaletteCreate();
                    NE_MaterialTexLoadGRF(sprMtl[startSprite+loadedCharSprites], sprPal[startSprite+loadedCharSprites], NE_TEXGEN_TEXCOORD, charSpritePath);
                    NE_SpriteSetMaterial(spr[startSprite+loadedCharSprites], sprMtl[startSprite+loadedCharSprites]);
                    NE_SpriteVisible(spr[startSprite+loadedCharSprites], 1);
                    NE_SpriteSetPos(spr[startSprite+loadedCharSprites], 0, -37);
                    NE_SpriteSetPriority(spr[startSprite+loadedCharSprites], 10);
                    charSprites[loadedCharSprites].sprite = &spr[startSprite+loadedCharSprites];
                    charSprites[loadedCharSprites].mtl = &sprMtl[startSprite+loadedCharSprites];
                    charSprites[loadedCharSprites].pal = &sprPal[startSprite+loadedCharSprites];
                    strcpy(charSprites[loadedCharSprites].name, charSpriteName);
                    loadedCharSprites++;
                }
            }
        }
    }
}

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
    loadSprites();

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

int charWidth(char c) {
    u32 codepoint = (u32)c;
    fseek(fnt, 93, SEEK_SET);
    u32 id = 0;
	u32 w = 0;
	while (ftell(fnt) < 3373 && w == 0) {
	    fread(&id, 4, 1, fnt);
	    if (codepoint == id) {
		    fseek(fnt, 12, SEEK_CUR);
            fread(&w, 2, 1, fnt);
	    } else {
		    fseek(fnt, 16, SEEK_CUR);
	    }
	}
    return w;
}

void writeFormattedText(int scr, int layer, int x, int y, char s[]) {
    strcpy(activeDialogue, "");
    char out[1000];
    strcpy(out, s);
    char* word = strtok(out, " ");
    char line[40] = "";
    int lineWidth = 0;
    while (word) {
        int wordWidth = 0;
        for (int i = 0; i < strlen(word); i++) {
            wordWidth += charWidth(word[i]);
        }
        lineWidth += wordWidth;
        if(lineWidth+wordWidth<=260-x){
            strcat(line,word);
            strcat(line," ");
            lineWidth += 3;
        } else {
            strcat(activeDialogue, line);
            strcat(activeDialogue, "\n");
            lineWidth = 0;
            strcpy(line, word);
            strcat(line, " ");
            y++;
        }
        word = strtok(NULL, " ");
    }
    strcat(activeDialogue, line);
}

void readScript(void) {

    char bgName[100];
    char charSpriteName[4][100];
    char character[4][16];
    char sprite[4][32];
    char textbox[16];
    char text[320];
    uint8 characterID;
    uint8 loadedCharacters = 0;

    int id = 0;
    for (json_t const* scriptItem = json_getChild(json_getProperty(parent, "script")); scriptItem != 0; scriptItem = json_getSibling(scriptItem)) {
        if (id == scriptPosition) {
            strcpy(text, json_getPropertyValue(scriptItem, "say"));
            if (json_getProperty(scriptItem, "bg")) {
                sprintf(bgName, "%s", json_getPropertyValue(scriptItem, "bg"));
            } else {
                strcpy(bgName, "");
            }
            if (json_getProperty(scriptItem, "mus")) {
                if (strcmp(songPlaying, json_getPropertyValue(scriptItem, "mus")) != 0) {
                    strcpy(songPlaying, json_getPropertyValue(scriptItem, "mus"));
                    musOffset = screenFrames;
                    soundKill(0);
                    soundKill(1);
                    soundKill(2);
                }
            }
            characterID = 0;
            for (json_t const* charactersItem = json_getChild(json_getProperty(scriptItem, "chrs")); charactersItem != 0; charactersItem = json_getSibling(charactersItem)) {
                loadedCharacters = characterID;
                if (charactersItem != 0) {
                    strcpy(character[characterID], json_getPropertyValue(charactersItem, "chr"));
                    strcpy(sprite[characterID], json_getPropertyValue(charactersItem, "spr"));
                    sprintf(charSpriteName[characterID], "%s_%s", character[characterID], sprite[characterID]);
                    if (json_getProperty(charactersItem, "trans")) {
                        strcpy(tnamea[characterID], json_getPropertyValue(charactersItem, "trans"));
                    } else {
                        strcpy(tnamea[characterID], "");
                    }
                    characterID++;
                } 
            }
            strcpy(textbox, json_getPropertyValue(scriptItem, "box"));
        }
        id++;
    }
    if (!strcmp(bgName, "") == 0) {
        for (int i = 0; i < MAX_CHARSPRITES; i++) {
            if (strcmp(charSprites[i].name, bgName) == 0) {
                activeBGSprite.sprite = charSprites[i].sprite;
                break;
            }
        }
    }
    for (int i = 0; i <= loadedCharacters; i++) {
        for (int j = 0; j < MAX_CHARSPRITES; j++) {
            if (strcmp(charSprites[j].name, charSpriteName[i]) == 0) {
                onScreenCharSprites[i].sprite = charSprites[j].sprite;
                break;
            }
        }
    }
    //createTextbox(textbox);
    //writeFormattedText(1, 0, 1, 3, text);
}


void advance(uint8 direction) {
    if (direction == 1 && scriptPosition < scriptMax) {
        scriptPosition++;
        readScript();
    } else if (direction == 0 && 0 < scriptPosition) {
        scriptPosition--;
        readScript();
    }
}