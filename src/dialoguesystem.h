#pragma once

extern uint16 scriptPosition;
extern uint16 scriptMax;
extern char *script;
extern char activeDialogue[300];
void setupDialogue(char volume[]);
void readScript(void);
void advance(uint8 direction);