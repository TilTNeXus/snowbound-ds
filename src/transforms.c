#include <NEMain.h>

#include "screens.h"
#include "transforms.h"

char tnamea[4][16];
uint16 tca[4];

void transforms(void) {
    for (int layer = 0; layer < 4; layer++) {
        if (strcmp(tnamea[layer], "middle") == 0) {
            NE_SpriteSetPos(spr[2+layer], 0, -37);
        } else if (strcmp(tnamea[layer], "twitch") == 0) {
            if (screenFrames - tca[layer] == 0) NE_SpriteSetPos(spr[2+layer], 0, -37);
            if (screenFrames - tca[layer] == 1) NE_SpriteSetPos(spr[2+layer], 1, -36);
            if (screenFrames - tca[layer] == 2) NE_SpriteSetPos(spr[2+layer], 1, -35);
            if (screenFrames - tca[layer] == 3) NE_SpriteSetPos(spr[2+layer], 2, -34);
            if (screenFrames - tca[layer] == 4) NE_SpriteSetPos(spr[2+layer], 1, -35);
            if (screenFrames - tca[layer] == 6) NE_SpriteSetPos(spr[2+layer], 0, -35);
            if (screenFrames - tca[layer] == 7) strcpy(tnamea[layer], "");
        }
    }
}