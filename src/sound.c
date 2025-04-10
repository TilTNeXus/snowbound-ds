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
      	chunkLength = chunkFileSize/11025*60+13;
      	if ((screenFrames-musOffset)%(4*chunkLength) == 1) {
			if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
			NF_LoadRawSound("audio/music/menutheme.0", 0, 11025, 0);
			NF_PlayRawSound(0, 127, 64, false, 0);
      	} else if ((screenFrames-musOffset)%(4*chunkLength) == chunkLength) {
			if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
			NF_LoadRawSound("audio/music/menutheme.1", 0, 11025, 0);
			NF_PlayRawSound(0, 127, 64, false, 0);
      	} else if ((screenFrames-musOffset)%(4*chunkLength) == (2*chunkLength)) {
			if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
			NF_LoadRawSound("audio/music/menutheme.2", 0, 11025, 0);
			NF_PlayRawSound(0, 127, 64, false, 0);
      	} else if ((screenFrames-musOffset)%(4*chunkLength) == (3*chunkLength)) {
			if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
			NF_LoadRawSound("audio/music/menutheme.3", 0, 11025, 0);
			NF_PlayRawSound(0, 127, 64, false, 0);
    	}
    } else if (strcmp(song, "secilytheme") == 0) {
		chunkFileSize = 233532;
		chunkLength = chunkFileSize/11025*60+5;
		if ((screenFrames-musOffset)%(8*chunkLength) == 1) {
	  		if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
	  		NF_LoadRawSound("audio/music/secilytheme.0", 0, 11025, 0);
	  		NF_PlayRawSound(0, 127, 64, false, 0);
		} else if ((screenFrames-musOffset)%(8*chunkLength) == chunkLength) {
	  		if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
	  		NF_LoadRawSound("audio/music/secilytheme.1", 0, 11025, 0);
	  		NF_PlayRawSound(0, 127, 64, false, 0);
		} else if ((screenFrames-musOffset)%(8*chunkLength) == (2*chunkLength)) {
	  		if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
	  		NF_LoadRawSound("audio/music/secilytheme.2", 0, 11025, 0);
	 		NF_PlayRawSound(0, 127, 64, false, 0);
		} else if ((screenFrames-musOffset)%(8*chunkLength) == (3*chunkLength)) {
	  		if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
	  		NF_LoadRawSound("audio/music/secilytheme.3", 0, 11025, 0);
	 		NF_PlayRawSound(0, 127, 64, false, 0);
		} else if ((screenFrames-musOffset)%(8*chunkLength) == (4*chunkLength)) {
			if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
			NF_LoadRawSound("audio/music/secilytheme.4", 0, 11025, 0);
		   	NF_PlayRawSound(0, 127, 64, false, 0);
	  	} else if ((screenFrames-musOffset)%(8*chunkLength) == (5*chunkLength)) {
			if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
			NF_LoadRawSound("audio/music/secilytheme.5", 0, 11025, 0);
		   	NF_PlayRawSound(0, 127, 64, false, 0);
	  	} else if ((screenFrames-musOffset)%(8*chunkLength) == (6*chunkLength)) {
			if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
			NF_LoadRawSound("audio/music/secilytheme.6", 0, 11025, 0);
		   	NF_PlayRawSound(0, 127, 64, false, 0);
	  	} else if ((screenFrames-musOffset)%(8*chunkLength) == (7*chunkLength)) {
			if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
			NF_LoadRawSound("audio/music/secilytheme.7", 0, 11025, 0);
		   	NF_PlayRawSound(0, 127, 64, false, 0);
	  	}
	} else if (strcmp(song, "secilyfight") == 0) {
		chunkFileSize = 194652;
		chunkLength = chunkFileSize/11025*60+5;
		if ((screenFrames-musOffset)%(8*chunkLength) == 1) {
	  		if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
	  		NF_LoadRawSound("audio/music/secilyfight.0", 0, 11025, 0);
	  		NF_PlayRawSound(0, 127, 64, false, 0);
		} else if ((screenFrames-musOffset)%(8*chunkLength) == chunkLength) {
	  		if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
	  		NF_LoadRawSound("audio/music/secilyfight.1", 0, 11025, 0);
	  		NF_PlayRawSound(0, 127, 64, false, 0);
		} else if ((screenFrames-musOffset)%(8*chunkLength) == (2*chunkLength)) {
	  		if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
	  		NF_LoadRawSound("audio/music/secilyfight.2", 0, 11025, 0);
	 		NF_PlayRawSound(0, 127, 64, false, 0);
		} else if ((screenFrames-musOffset)%(8*chunkLength) == (3*chunkLength)) {
	  		if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
	  		NF_LoadRawSound("audio/music/secilyfight.3", 0, 11025, 0);
	 		NF_PlayRawSound(0, 127, 64, false, 0);
		} else if ((screenFrames-musOffset)%(8*chunkLength) == (4*chunkLength)) {
			if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
			NF_LoadRawSound("audio/music/secilyfight.4", 0, 11025, 0);
		   	NF_PlayRawSound(0, 127, 64, false, 0);
	  	} else if ((screenFrames-musOffset)%(8*chunkLength) == (5*chunkLength)) {
			if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
			NF_LoadRawSound("audio/music/secilyfight.5", 0, 11025, 0);
		   	NF_PlayRawSound(0, 127, 64, false, 0);
	  	} else if ((screenFrames-musOffset)%(8*chunkLength) == (6*chunkLength)) {
			if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
			NF_LoadRawSound("audio/music/secilyfight.6", 0, 11025, 0);
		   	NF_PlayRawSound(0, 127, 64, false, 0);
	  	} else if ((screenFrames-musOffset)%(8*chunkLength) == (7*chunkLength)) {
			if (!NF_RAWSOUND[0].available) NF_UnloadRawSound(0);
			NF_LoadRawSound("audio/music/secilyfight.7", 0, 11025, 0);
		   	NF_PlayRawSound(0, 127, 64, false, 0);
	  	}
	}
}
