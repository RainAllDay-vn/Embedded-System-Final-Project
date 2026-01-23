/*
 * SoundEngine.h
 *
 *  Created on: Jan 23, 2026
 *      Author: Kilo Code
 */

#ifndef INC_SOUNDENGINE_H_
#define INC_SOUNDENGINE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h" // For uint16_t, etc.
#include "cmsis_os.h" // For osMessageQueueId_t (if needed in public API, usually not)

/* Note Definition */
typedef struct {
    uint16_t frequency; // Hz (0 = Rest)
    uint16_t duration;  // Milliseconds
} MusicNote;

/* Track Definitions */
typedef enum {
    TRACK_NONE = 0,
    TRACK_MENU,
    TRACK_GAME_THEME_A,
    TRACK_GAME_OVER,
    TRACK_LINE_CLEAR,
    TRACK_COUNT
} TrackID;

/* Public API */
void SoundEngine_Init(void);
void SoundEngine_PlayTrack(TrackID track);
void SoundEngine_Stop(void);
void SoundEngine_SetVolume(uint8_t volume);

/* Task Function (Exposed for FreeRTOS creation) */
void SoundEngineTask(void *argument);

#ifdef __cplusplus
}
#endif

#endif /* INC_SOUNDENGINE_H_ */
