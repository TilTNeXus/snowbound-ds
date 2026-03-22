#pragma once
#include "screens.h"

extern uint16 scriptPosition;
extern uint16 scriptMax;
extern char *script;
extern char activeDialogue[300];
void setupDialogue(char volume[]);
void readScript(void);
void advance(uint8 direction);
typedef struct scriptElement {
    //charSprite_t *bg;
    char bgPath[128];
    int musicID;
    char charactersPath[128][4];
    //charSprite_t *characters[4];
    int speaking;
    char dialogue[256];
} scriptElement;
extern scriptElement *scriptArray;