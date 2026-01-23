# Audio System Design for Embedded Tetris

## 1. Current State Analysis

### 1.1 Hardware & Configuration
- **Output Device**: Piezo Buzzer on TIM10 Channel 1.
- **Microcontroller**: STM32F429ZIT6.
- **Operating System**: FreeRTOS with CMSIS-OS V2.
- **Clocking**: TIM10 runs on APB2 (84MHz or 90MHz depending on config), prescaled to 1MHz counter.

### 1.2 Existing Implementation (`Core/Src/main.c`)
- **Control**: Direct PWM manipulation via `__HAL_TIM_SET_AUTORELOAD` and `__HAL_TIM_SET_COMPARE`.
- **Logic**: A dedicated FreeRTOS task `MarioMusicTask` plays a single hardcoded loop (`mario_notes`).
- **Issues**:
  - Tightly coupled to `main.c`.
  - Blocking delays (`osDelay`) make it hard to interrupt or change tracks instantly without logic.
  - No mechanism to change themes based on game state (Menu vs Game).

### 1.3 Screen Structure (`TouchGFX`)
- **MainView**: Entry point (Menu).
- **GameView**: The actual Tetris game.
- **Transition**: Handled by `FrontendApplication`.
- **Requirements**:
  - `MainView` should play a "Menu Theme" (e.g., slower, chill).
  - `GameView` should play the "Main Theme" (Tetris A / Korobeiniki).
  - Game Over state should play a distinct jingle.

---

## 2. Proposed Architecture

The system will use a **Producer-Consumer pattern** decoupling the UI (TouchGFX) from the Real-Time Audio engine (FreeRTOS Task).

### 2.1 Component Diagram (Mermaid)

```mermaid
graph TD
    subgraph TouchGFX [TouchGFX Context (C++)]
        MV[MainView] -->|setupScreen| M[Model]
        GV[GameView] -->|setupScreen| M
        M -->|calls| Bridge[C-Bridge API]
    end

    subgraph Core [System Core (C)]
        Bridge -->|osMessageQueuePut| Q[SoundRequestQueue]
        
        subgraph AudioTask [Sound Engine Configuration]
            ST[SoundTask]
            ST -->|osMessageQueueGet| Q
            ST -->|Updates Pointer| CP[Current Track Pointer]
            ST -->|PWM Control| TIM10[TIM10 HW]
        end
    end
```

### 2.2 Functional Flow
1. **Request**: When a screen is entered (verified via `setupScreen`), the View calls the Model.
2. **Bridge**: The Model calls a C-compatible function `SoundEngine_PlayTrack(TrackID)`.
3. **Queueing**: This function pushes a `TrackID` to a FreeRTOS Message Queue.
4. **Processing**: The `SoundTask` (formerly `MarioMusicTask`) wakes up.
   - If a message is received: It immediately resets the note index and switches the active melody array.
   - If playing: It processes the next note, sets PWM, and sleeps for the note duration.

---

## 3. Data Structures & Data

### 3.1 Note Definition
To save space and simplify processing, melodies will be stored as arrays of `MusicNote`.

```c
typedef struct {
    uint16_t frequency; // Hz (0 = Rest)
    uint16_t duration;  // Milliseconds
} MusicNote;
```

### 3.2 Track Definition (Enum)
```c
typedef enum {
    TRACK_NONE = 0,
    TRACK_MENU,
    TRACK_GAME_THEME_A,
    TRACK_GAME_OVER,
    TRACK_COUNT
} TrackID;
```

### 3.3 Melody Storage
Tracks will be stored in Flash (`const`) to save RAM.

```c
// Example: Tetris Theme A (Korobeiniki)
const MusicNote theme_A[] = {
    {659, 400}, {494, 200}, {523, 200}, {587, 400}, // E5, B4, C5, D5...
    {523, 200}, {494, 200}, {440, 400},             // C5, B4, A4...
    // ...
    {0, 0} // Terminator
};
```

---

## 4. Integration Points

### 4.1 C/C++ Bridge (`SoundEngine.h`)
This header will be included by both C (main) and C++ (Model) files.

```c
#ifdef __cplusplus
extern "C" {
#endif

// Initialize Queue and Task
void SoundEngine_Init(void);

// Send request to change track (Non-blocking)
void SoundEngine_PlayTrack(TrackID track_id);

// Stop all sound immediately
void SoundEngine_Stop(void);

#ifdef __cplusplus
}
#endif
```

### 4.2 TouchGFX Integration

#### Model.hpp
Add a method to handle music requests.
```cpp
// Model.hpp
void playMusic(TrackID trackId);
```

#### MainView.cpp
Trigger the menu theme when the screen loads.
```cpp
// MainView::setupScreen
void MainView::setupScreen()
{
    MainViewViewBase::setupScreen();
    // Transitioning to Menu
    application().getModel().playMusic(TRACK_MENU);
}
```

#### GameView.cpp
Trigger the main theme when the game starts.
```cpp
// GameView::setupScreen
void GameView::setupScreen()
{
    GameViewViewBase::setupScreen();
    // Transitioning to Game
    application().getModel().playMusic(TRACK_GAME_THEME_A);
}
```

---

## 5. Implementation Roadmap

1.  **Create Module**: Create `Core/Src/SoundEngine.c` and `Core/Inc/SoundEngine.h`.
2.  **Migrate Logic**: Move PWM control and looping logic from `main.c` to `SoundEngine.c`.
3.  **Define Melodies**: Transcribe the "Tetris Theme" and a simple "Menu Theme" into `MusicNote` arrays.
4.  **Setup FreeRTOS**:
    - Update `MX_FREERTOS_Init` (or `main.c` manual init) to create the queue.
    - Reconfigure the existing `MarioMusicTask` to be the `SoundTask`.
5.  **Connect UI**: Update `Model.cpp` to call `SoundEngine_PlayTrack`.

## 6. Memory Considerations
- **Flash**: Melodies are small (<< 1KB).
- **RAM**: Minimal overhead (Queue of 2-3 items, Task stack already exists).
- **CPU**: PWM is hardware-driven; Task only wakes up on note changes (every 100-500ms), negligible load.
