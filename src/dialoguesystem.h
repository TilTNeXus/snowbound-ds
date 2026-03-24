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
    char charactersPath[4][128];
    //charSprite_t *characters[4];
    int speaking;
    char dialogue[256];
} scriptElement;
extern scriptElement *scriptArray;
void setTextColor(int color);
enum textboxID {
    textbox_narration = 0,
    textbox_choice = 1,
    textbox_secily = 2
};