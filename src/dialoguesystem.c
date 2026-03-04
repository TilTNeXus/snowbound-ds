#include "tiny-json/tiny-json.h"

#include "screens.h"
#include "dialoguesystem.h"
#include "transforms.h"
#include "sound.h"

uint16 scriptPosition;
json_t const* parent;
char volume[6];
uint16 scriptMax;
int startSprite = 3;
scriptElement *scriptArray = NULL;

/*  go through the script, get every unique character sprite and background, 
    store pointers to sprites, materials, and palettes alongside the name to identify them for later use
    then store pointers to those in an array for each position of the script
*/
void loadSprites(void) {
    
    loadedSprites = 0;
    // get length of script and allocate
    int scriptCounter = 0;
    for (json_t const* scriptItem = json_getChild(json_getProperty(parent, "script")); scriptItem != 0; scriptItem = json_getSibling(scriptItem)) {
        scriptCounter++;
    }
    if (scriptArray != NULL) free(scriptArray);
    scriptArray = malloc((scriptCounter+1)*sizeof(scriptElement));
    
    scriptCounter = 0;
    for (json_t const* scriptItem = json_getChild(json_getProperty(parent, "script")); scriptItem != 0; scriptItem = json_getSibling(scriptItem)) {
        bool hasBeenLoaded = 0;
        
        // loading backgrounds
        char bgName[32];
        char bgPath[64];
        snprintf(bgName, 31, json_getPropertyValue(scriptItem, "bg"));
        snprintf(bgPath, 63, "backgrounds/%s/%s_png.grf", volume, bgName);
        // search through the loaded sprites to see if this background has already been loaded
        for (int i = 0; i < loadedSprites; i++) {
            if (strcmp(charSprites[i].name, bgName) == 0) {
                hasBeenLoaded = 1;
                scriptArray[scriptCounter].bg = &charSprites[i];
                break;
            }
        }
        // if the bg has not been loaded, then load it
        if (!hasBeenLoaded) {
            int index = startSprite+loadedSprites;
            printf("%d\n", index);
            NE_MaterialDelete(sprMtl[index]);
            sprMtl[index] = NE_MaterialCreate();

            NE_PaletteDelete(sprPal[index]);
            sprPal[index] = NE_PaletteCreate();

            //NE_MaterialTexLoadGRF(sprMtl[index], sprPal[index], NE_TEXGEN_TEXCOORD, bgPath);
            NE_SpriteSetMaterial(spr[index], sprMtl[index]);
            NE_SpriteVisible(spr[index], 1);
            NE_SpriteSetPos(spr[index], 0, 0);
            NE_SpriteSetPriority(spr[index], 50);

            charSprites[loadedSprites].sprite = spr[index];
            charSprites[loadedSprites].mtl = sprMtl[index];
            charSprites[loadedSprites].pal = sprPal[index];
            snprintf(charSprites[loadedSprites].name, 31, bgName);

            scriptArray[scriptCounter].bg = &charSprites[loadedSprites];
            loadedSprites++;
        }

        int loadedCharacters = 0;
        // go through all the chr in the chrs section
        
        for (json_t const* charactersItem = json_getChild(json_getProperty(scriptItem, "chrs")); charactersItem != 0; charactersItem = json_getSibling(charactersItem)) {
            char charSpriteName[64];
            char charSpritePath[128];
            char charName[16];
            char charSprite[32];
            
            // if there is a character
            snprintf(charName, 15, json_getPropertyValue(charactersItem, "chr"));
            snprintf(charSprite, 31, json_getPropertyValue(charactersItem, "spr"));
            snprintf(charSpriteName, 63, "%s_%s", charName, charSprite);
            snprintf(charSpritePath, 127, "characters/%s/%s_png.grf", charName, charSpriteName);

            // search through the loaded sprites to see if this character has already been loaded
            hasBeenLoaded = 0;
            for (int i = 0; i < loadedSprites; i++) {
                if (strcmp(charSprites[i].name, charSpriteName) == 0) {
                    hasBeenLoaded = 1;
                    scriptArray[scriptCounter].characters[loadedCharacters] = &charSprites[i];
                    break;
                }
            }
            // if the character has not been loaded, then load it
            if (!hasBeenLoaded) {
                int index = startSprite+loadedSprites;
                printf("%d\n", index);
                NE_MaterialDelete(sprMtl[index]);
                sprMtl[index] = NE_MaterialCreate();
                
                NE_PaletteDelete(sprPal[index]);
                sprPal[index] = NE_PaletteCreate();
                
                NE_MaterialTexLoadGRF(sprMtl[index], sprPal[index], NE_TEXGEN_TEXCOORD, charSpritePath);
                NE_SpriteSetMaterial(spr[index], sprMtl[index]);
                NE_SpriteVisible(spr[index], 1);
                NE_SpriteSetPos(spr[index], 0, -37);
                NE_SpriteSetPriority(spr[index], 10);
                
                charSprites[loadedSprites].sprite = spr[index];
                charSprites[loadedSprites].mtl = sprMtl[index];
                charSprites[loadedSprites].pal = sprPal[index];
                
                strcpy(charSprites[loadedSprites].name, charSpriteName);
                
                scriptArray[scriptCounter].characters[loadedCharacters] = &charSprites[loadedSprites];
                loadedSprites++;
            }
            loadedCharacters++;
        }
        strncpy(scriptArray[scriptCounter].dialogue, json_getPropertyValue(scriptItem, "say"), 255);
        scriptCounter++;
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
    free(script);

    readScript();
    
}

void readScript(void) {

    /*
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
    } */
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