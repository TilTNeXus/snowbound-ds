#include <string.h>

#include <nf_lib.h>

#include "screens.h"
#include "sound.h"

int musOffset = 0;

void playBGM(char song[]) {
    if (strcmp(song, "mainmenu") == 0) {
      if ((screenFrames-musOffset)%5112 == 1) {
	if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
	NF_LoadRawSound("audio/music/menutheme.0", 0, 11025, 0);
	NF_PlayRawSound(0, 127, 64, false, 0);
      } else if ((screenFrames-musOffset)%5112 == 1278) {
	if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
	NF_LoadRawSound("audio/music/menutheme.1", 0, 11025, 0);
	NF_PlayRawSound(0, 127, 64, false, 0);
      } else if ((screenFrames-musOffset)%5112 == 2556) {
	if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
	NF_LoadRawSound("audio/music/menutheme.2", 0, 11025, 0);
	NF_PlayRawSound(0, 127, 64, false, 0);
      } else if ((screenFrames-musOffset)%5112 == 3834) {
	if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
	NF_LoadRawSound("audio/music/menutheme.3", 0, 11025, 0);
	NF_PlayRawSound(0, 127, 64, false, 0);
      }
    }
}
