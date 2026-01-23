/*
 * SoundEngine.c
 *
 *  Created on: Jan 23, 2026
 *      Author: Kilo Code
 */

#include "SoundEngine.h"
#include "stm32f4xx_hal.h"
#include <string.h> // For memset

/* External PWM Timer Handle */
extern TIM_HandleTypeDef htim10;

/* Internal State */
static osMessageQueueId_t soundQueueHandle;
static osThreadId_t soundTaskHandle;
static uint8_t volume_percent = 50; // Default volume (0-100)

/* Note Frequencies (Hz) */
#define NOTE_REST 0
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_D5 587
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_G5 784
#define NOTE_A5 880
#define NOTE_B5 988
#define NOTE_C6 1047

/* Melodies */

/* 1. Menu Theme: Simple ambient loop */
static const MusicNote melody_menu[] = {
    {NOTE_C5, 300}, {NOTE_E5, 300}, {NOTE_G5, 300}, {NOTE_E5, 300},
    {NOTE_C5, 300}, {NOTE_G4, 300}, {NOTE_C5, 600},
    {NOTE_REST, 0} // Terminator
};

/* 2. Game Theme: Korobeiniki (Tetris A) - Simplified */
static const MusicNote melody_game[] = {
    // Phrase 1
    {NOTE_E5, 400}, {NOTE_B4, 200}, {NOTE_C5, 200}, {NOTE_D5, 400},
    {NOTE_C5, 200}, {NOTE_B4, 200}, {NOTE_A4, 400}, {NOTE_A4, 200},
    {NOTE_C5, 200}, {NOTE_E5, 400}, {NOTE_D5, 200}, {NOTE_C5, 200},
    {NOTE_B4, 600}, {NOTE_C5, 200}, {NOTE_D5, 400}, {NOTE_E5, 400},
    {NOTE_C5, 400}, {NOTE_A4, 400}, {NOTE_A4, 800},
    {NOTE_REST, 0} // Terminator
};

/* 3. Game Over: Sad Jingle */
static const MusicNote melody_gameover[] = {
    {NOTE_B4, 300}, {NOTE_F4, 300}, {NOTE_D4, 300}, {NOTE_C4, 800},
    {NOTE_REST, 0}
};

/* 4. Line Clear: Victory sound */
static const MusicNote melody_clear[] = {
    {NOTE_E5, 100}, {NOTE_A5, 400},
    {NOTE_REST, 0}
};

/* Helper: Set PWM Frequency */
static void SetFrequency(uint32_t freq)
{
    if (freq == 0)
    {
        /* Stop PWM (0% Duty Cycle) */
        __HAL_TIM_SET_COMPARE(&htim10, TIM_CHANNEL_1, 0);
    }
    else
    {
        /* Calculate Auto-Reload Register (ARR) value
         * APB2 Timer Clock = 168 MHz (if properly config per instruction)
         * Prescaler = 167 -> Timer runs at 1 MHz
         * Period = (1MHz / Freq) - 1
         */
        uint32_t period = (1000000 / freq) - 1;
        
        /* Set new period */
        __HAL_TIM_SET_AUTORELOAD(&htim10, period);
        
        /* Set Duty Cycle based on Volume */
        /* Volume 100 = 50% Duty Cycle (Max loud for Square Wave) */
        /* Volume 0 = 0% Duty Cycle */
        uint32_t duty = (period / 2) * volume_percent / 100;
        
        __HAL_TIM_SET_COMPARE(&htim10, TIM_CHANNEL_1, duty);
        
        /* Ensure Timer is running */
        HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
    }
}

/* API Implementation */

void SoundEngine_Init(void)
{
    /* Queue Creation: Depth 4, uint8_t TrackID */
    soundQueueHandle = osMessageQueueNew(4, sizeof(TrackID), NULL);
    
    /* Task Creation should be handled in freertos.c or main.c, 
       but we provide the function body here. */
}

void SoundEngine_PlayTrack(TrackID track)
{
    if (soundQueueHandle != NULL)
    {
        /* Send to Queue, dont block if full */
        osMessageQueuePut(soundQueueHandle, &track, 0, 0);
    }
}

void SoundEngine_Stop(void)
{
    TrackID stopCmd = TRACK_NONE;
    SoundEngine_PlayTrack(stopCmd);
}

void SoundEngine_SetVolume(uint8_t volume)
{
    if (volume > 100) volume = 100;
    volume_percent = volume;
}

/* FreeRTOS Task */
void SoundEngineTask(void *argument)
{
    TrackID currentRequest;
    TrackID currentTrack = TRACK_NONE;
    TrackID activeBGM = TRACK_NONE;
    const MusicNote* currentMelody = NULL;
    uint32_t noteIndex = 0;
    
    /* Ensure hardware initialized */
    HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
    
    for(;;)
    {
        /* Check for new track request */
        /* If playing, wait 0. If stopped, wait forever (suspend) */
        uint32_t waitTime = (currentMelody == NULL) ? osWaitForever : 0;
        
        if (osMessageQueueGet(soundQueueHandle, &currentRequest, NULL, waitTime) == osOK)
        {
            /* Process New Request */
            noteIndex = 0;
            currentTrack = currentRequest;

            switch(currentRequest)
            {
                case TRACK_MENU:
                    currentMelody = melody_menu;
                    activeBGM = TRACK_MENU;
                    break;
                case TRACK_GAME_THEME_A:
                    currentMelody = melody_game;
                    activeBGM = TRACK_GAME_THEME_A;
                    break;
                case TRACK_GAME_OVER:
                    currentMelody = melody_gameover;
                    // SFX: don't change activeBGM
                    break;
                case TRACK_LINE_CLEAR:
                    currentMelody = melody_clear;
                    // SFX: don't change activeBGM
                    break;
                case TRACK_NONE:
                default:
                    currentMelody = NULL;
                    activeBGM = TRACK_NONE;
                    currentTrack = TRACK_NONE;
                    SetFrequency(0);
                    break;
            }
        }
        
        /* Play Logic */
        if (currentMelody != NULL)
        {
            MusicNote note = currentMelody[noteIndex];
            
            /* Check for terminator */
            if (note.duration == 0 && note.frequency == 0)
            {
                /* Termination/Loop Logic */
                if (currentTrack == TRACK_MENU || currentTrack == TRACK_GAME_THEME_A)
                {
                    noteIndex = 0; // Restart BGM Loop
                }
                else
                {
                    /* SFX Finished: Wait a bit before resuming BGM */
                    SetFrequency(0);
                    osDelay(1000); // Increased gap to 1 second for better separation

                    if (activeBGM != TRACK_NONE)
                    {
                        currentTrack = activeBGM;
                        noteIndex = 0;
                        currentMelody = (activeBGM == TRACK_MENU) ? melody_menu : melody_game;
                    }
                    else
                    {
                        currentTrack = TRACK_NONE;
                        currentMelody = NULL;
                        SetFrequency(0);
                    }
                }
            }
            else
            {
                /* Play Note */
                SetFrequency(note.frequency);
                osDelay(note.duration);
                noteIndex++;
            }
        }
    }
}
