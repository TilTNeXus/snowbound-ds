#include <string.h>

#include <nf_lib.h>

#include "screens.h"
#include "sound.h"

int musOffset = 0;
// chunkFileSize is size of chunk in bytes
int chunkFileSize;
// chunkLength is length of chunk in frames
int chunkLength;

void playBGM(char song[]) {
    if (strcmp(song, "mainmenu") == 0) {
      chunkFileSize = 235200;
      chunkLength = chunkFileSize/11025*60+15;
      if ((screenFrames-musOffset)%(4*chunkLength) == 1) {
	if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
	NF_LoadRawSound("audio/music/menutheme.0", 0, 11025, 0);
	NF_PlayRawSound(0, 127, 64, false, 0);
      } else if ((screenFrames-musOffset)%(4*chunkLength) == chunkLength) {
	if (!NF_RAWSOUND[1].available) NF_UnloadRawSound(1);
	NF_LoadRawSound("audio/music/menutheme.1", 1, 11025, 0);
	NF_PlayRawSound(1, 127, 64, false, 0);
      } else if ((screenFrames-musOffset)%(4*chunkLength) == (2*chunkLength)) {
	if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
	NF_LoadRawSound("audio/music/menutheme.2", 0, 11025, 0);
	NF_PlayRawSound(0, 127, 64, false, 0);
      } else if ((screenFrames-musOffset)%(4*chunkLength) == (3*chunkLength)) {
	if (!NF_RAWSOUND[1].available) NF_UnloadRawSound(1);
	NF_LoadRawSound("audio/music/menutheme.3", 1, 11025, 0);
	NF_PlayRawSound(1, 127, 64, false, 0);
      }
    }
}
