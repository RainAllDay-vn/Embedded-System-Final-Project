# Embedded Tetris 🎮✨

> **A Modern Retro Tetris Game on STM32F429I-DISCO**

![STM32](https://img.shields.io/badge/STM32F429-ARM_Cortex--M4-blue?logo=stmicroelectronics)
![TouchGFX](https://img.shields.io/badge/TouchGFX-4.x-orange)
![FreeRTOS](https://img.shields.io/badge/FreeRTOS-CMSIS--RTOS_V2-green)
![C](https://img.shields.io/badge/Language-C/C++-blue?logo=c)

## 🚀 Overview

**Embedded Tetris** is a fully functional Tetris game implementation running on the STM32F429I-DISCO development board. Built with a "Modern Retro" aesthetic, this project demonstrates embedded systems programming combining real-time operating systems, hardware-accelerated graphics, and responsive game mechanics.

The game features smooth 60 FPS rendering, hardware-randomized piece generation, screen-specific soundtracks, and an intuitive touch-based interface - all running on a resource-constrained embedded platform.

## 💡 Key Features

### 🎮 Core Gameplay
- **Classic Tetris Mechanics**: Full implementation of standard Tetris rules including piece rotation, line clearing, and scoring
- **Ghost Piece**: Visual indicator showing the landing position of the current piece
- **Hold & Next Piece**: Strategic gameplay with piece holding and preview functionality
- **Progressive Difficulty**: Level-based speed increases for challenging gameplay

### 🎨 Visual Experience
- **Modern Retro Aesthetic**: Neon-colored blocks with pixel-perfect rendering at 240x320 resolution
- **Hardware-Accelerated Graphics**: DMA2D (Chrom-ART) for efficient framebuffer operations
- **Visual Effects**: Hard drop screen shake, line clear flashes, and smooth animations
- **CRT Scanline Overlay**: Authentic retro display feel

### 🎵 Audio System
- **Screen-Specific Soundtracks**: Different music for Main Menu and Gameplay screens
- **Hardware PWM Audio**: Buzzer-based sound generation using TIM10
- **Producer-Consumer Architecture**: FreeRTOS queue-based sound engine for asynchronous playback
- **Game Event Sounds**: Audio feedback for line clears, piece drops, and game over

### 🎯 Hardware Integration
- **Button Controls**: Four physical buttons (PB12, PB13, PG2, PG3) with interrupt-based input processing
- **Hardware RNG**: True random number generation for unbiased piece sequences
- **Double Buffering**: Smooth tear-free rendering using SDRAM framebuffer
- **Optimized Performance**: 168 MHz system clock with efficient memory management

## 🛠️ Technology Stack

This project is built using industry-standard embedded development tools and frameworks.

### **Hardware Platform**
- **MCU**: STM32F429ZIT6 (ARM Cortex-M4, 180 MHz, 2MB Flash, 256KB RAM)
- **Board**: STM32F429I-DISCO Discovery Kit
- **Display**: 2.4" QVGA (240x320) TFT LCD with ILI9341 driver
- **Controls**: Four GPIO buttons (PB12, PB13, PG2, PG3) with interrupt-based input
- **Memory**: External 8MB SDRAM for framebuffer and heap
- **Audio**: On-board buzzer with PWM generation

### **Software Framework**
- **STM32CubeIDE**: Primary development environment and build system
- **TouchGFX 4.x**: Hardware-accelerated GUI framework with C++ frontend
- **FreeRTOS**: Real-time operating system with CMSIS-RTOS V2 wrapper
- **STM32 HAL**: Hardware abstraction layer for peripheral management

### **Languages & Tools**
- **C**: Low-level drivers, FreeRTOS tasks, HAL integration
- **C++**: TouchGFX UI implementation (MVP pattern)
- **Assembly**: Startup code and low-level initialization
- **STM32CubeMX**: Hardware configuration and code generation

### **Key Libraries**
- **CMSIS**: Cortex Microcontroller Software Interface Standard
- **Middleware**: ST TouchGFX and FreeRTOS integration
- **GCC/Clang**: Compiler support for multiple toolchains

## 🏗️ System Architecture

The system follows a **Model-View-Presenter (MVP)** architecture integrated with FreeRTOS for multitasking.

### **Core Components**

#### 1. Hardware Abstraction Layer (HAL)
- **Drivers**: GPIO, SPI (LCD), I2C (Touch), LTDC (Display Controller), DMA2D (Graphics Accelerator), RNG (Random Number), FMC (SDRAM)
- **Files**: `Core/Src/stm32f4xx_hal_*.c`

#### 2. FreeRTOS Task Management
- **DefaultTask**: GUI rendering and TouchGFX event loop (Stack: 4096 words)
- **SoundEngineTask**: Audio playback and track management
- **TetrisLogicTask**: Game logic updates and state management

#### 3. TouchGFX Application Layer
- **Model**: Stores game state, score, grid, and next piece. Bridges C++ UI with C hardware backend
- **View**: Handles rendering of Tetris grid, sidebars, and UI elements
- **Presenter**: Mediation logic between Model and View

#### 4. Audio Subsystem
- **Producer-Consumer Pattern**: UI screens produce sound requests, SoundEngineTask consumes them
- **Bridge**: `SoundEngine.c` provides C API for audio control
- **Data**: Melodies stored as `MusicNote` arrays in Flash memory

### **Directory Structure**
```
Embedded-System-Final-Project/
├── Core/                          # Core application code
│   ├── Inc/                       # Header files
│   │   ├── main.h                 # Main header
│   │   ├── FreeRTOSConfig.h       # RTOS configuration
│   │   └── SoundEngine.h          # Audio system interface
│   └── Src/                       # Source files
│       ├── main.c                 # Main initialization
│       ├── freertos.c             # FreeRTOS tasks
│       └── SoundEngine.c          # Audio implementation
├── TouchGFX/                      # GUI framework
│   ├── gui/                       # UI implementation
│   │   ├── include/gui/           # Header files
│   │   │   ├── common/            # Shared definitions
│   │   │   ├── mainview_screen/   # Menu screen
│   │   │   ├── gameview_screen/   # Game screen
│   │   │   └── model/             # Data model
│   │   └── src/                   # Implementation
│   ├── assets/                    # Images and fonts
│   └── target/                    # Hardware abstraction
├── Middlewares/                   # Third-party libraries
│   └── Third_Party/FreeRTOS/      # RTOS source
├── STM32CubeIDE/                  # IDE project files
├── EWARM/                         # IAR Embedded Workbench
├── MDK-ARM/                       # Keil µVision
└── gcc/                           # GCC Makefile build
```

## 📋 Getting Started

### Prerequisites
- **STM32CubeIDE** (recommended) or alternative IDE (IAR EWARM, Keil MDK-ARM)
- **STM32F429I-DISCO** development board
- **USB Mini-B cable** for power and debugging
- **ST-Link V2** drivers (included with STM32CubeIDE)

### Hardware Setup
1. Connect the STM32F429I-DISCO board to your computer via USB Mini-B cable
2. Ensure the board is powered (LD1 should be lit)
3. The board will be recognized as an ST-Link device

### Software Setup

#### Option 1: STM32CubeIDE (Recommended)
1. **Clone the repository**
   ```bash
   git clone https://github.com/yourusername/Embedded-System-Final-Project.git
   cd Embedded-System-Final-Project
   ```

2. **Open the project**
   - Launch STM32CubeIDE
   - Select `File` → `Open Projects from File System...`
   - Navigate to `STM32CubeIDE/` folder and import the project

3. **Build the project**
   - Click the **Build** button (hammer icon) or press `Ctrl+B`
   - Wait for compilation to complete

4. **Flash and debug**
   - Click the **Debug** button (bug icon) or press `F11`
   - The IDE will flash the firmware and start debugging

#### Option 2: GCC Makefile
1. **Navigate to GCC directory**
   ```bash
   cd gcc
   ```

2. **Build using Make**
   ```bash
   make
   ```

3. **Flash using ST-Link**
   ```bash
   st-flash write build/STM32F429I_DISCO_REV_D01.bin 0x8000000
   ```

### Running the Game
1. After flashing, the game will start automatically
2. **Main Menu**: Press UP button to start a new game
3. **Controls**:
   - **UP Button**: Short press to rotate, long press (500ms) to hold piece
   - **DOWN Button**: Short press for soft drop, long press (500ms) for hard drop
   - **LEFT Button**: Move piece left
   - **RIGHT Button**: Move piece right
4. **Pause**: Use the on-screen pause button to pause/resume

## 🎮 Game Controls

The game uses physical buttons on the STM32F429I-DISCO board for control. Each button supports both short and long press actions.

| Button | GPIO Pin | Short Press | Long Press (500ms) |
|--------|----------|-------------|-------------------|
| **UP** | PB12 | Rotate Piece | Swap/Hold Piece |
| **DOWN** | PG2 | Soft Drop | Hard Drop |
| **LEFT** | PG3 | Move Left | - |
| **RIGHT** | PB13 | Move Right | - |

### Button Layout
```
┌──────────────────────────────┐
│                              │
│         [UP] (PB12)          │
│   Short: Rotate  Long: Hold  │
│                              │
│   [LEFT] (PG3) [RIGHT] (PB13)│
│    Move Left    Move Right   │
│                              │
│        [DOWN] (PG2)          │
│   Short: Drop   Long: Hard   │
│                              │
└──────────────────────────────┘
```

### Input Processing
- **Interrupt-based**: All buttons use GPIO interrupts for responsive input
- **Debouncing**: 50ms minimum interval between events (200ms for LEFT/RIGHT)
- **Queue-based**: Button events are queued via FreeRTOS message queues
- **Timer callbacks**: Long-press detection uses FreeRTOS timers

## 📊 Performance Specifications

- **Frame Rate**: 60 FPS target with VSYNC synchronization
- **System Clock**: 168 MHz (optimized for RNG stability)
- **Display Resolution**: 240x320 pixels (QVGA Portrait)
- **Color Depth**: 16bpp (RGB565)
- **Memory Usage**:
  - Framebuffer: ~300KB (double buffered in SDRAM)
  - Heap: Configured in external SDRAM
  - Stack: 4KB for GUI task

## 🔧 Configuration

### Clock Configuration
- **HSE Input**: 8 MHz external crystal
- **System Clock**: 168 MHz via PLL
- **PLL Configuration**: N=336, Q=7 for 48 MHz RNG clock

### Key Peripherals
| Peripheral | Purpose | Configuration |
|------------|---------|---------------|
| LTDC | Display controller | 240x320 @ 60Hz |
| DMA2D | Graphics acceleration | Chrom-ART enabled |
| TIM10 | Audio PWM | 50% duty cycle |
| RNG | Random piece generation | 48 MHz clock |
| FMC | External SDRAM | 8MB @ 84 MHz |

### Button GPIO Configuration
| Pin | Mode | Pull-up | Interrupt | Debounce |
|-----|------|---------|------------|----------|
| PB12 | UP | Yes | Rising/Falling | 50ms |
| PB13 | RIGHT | Yes | Rising | 200ms |
| PG2 | DOWN | Yes | Rising/Falling | 50ms |
| PG3 | LEFT | Yes | Rising/Falling | 50ms |

## 👨‍💻 Author

**Long Vu**
