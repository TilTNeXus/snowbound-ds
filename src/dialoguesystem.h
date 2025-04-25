#pragma once

extern uint16 scriptPosition;
extern uint16 scriptMax;
extern char *script;
void setupDialogue(char volume[]);
void readScript(void);
void advance(uint8 direction);