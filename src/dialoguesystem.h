#pragma once

extern uint16 scriptPosition;
extern uint16 scriptMax;
void setupDialogue(char volume[]);
void readScript(void);
void advance(uint8 direction);