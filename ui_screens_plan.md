# Tetris Art - UI/UX Design Plan (240x320 Handheld)

## 1. Aesthetic Direction: "Modern Retro"
*   **Style:** Sharp Pixel Art with Modern Post-Processing (Bloom/Glow).
*   **Resolution:** 240x320px (QVGA).
*   **Color Palette:** Standard Tetris Colors but with "Neon" variants.
    *   **I (Cyan):** #00FBFF | **O (Yellow):** #FFD500
    *   **T (Purple):** #BE00FF | **S (Green):** #00FF41
    *   **Z (Red):** #FF003C | **J (Blue):** #003CFF | **L (Orange):** #FF8A00
*   **Grid:** 120x240 pixels (10 columns x 20 rows, 12px per block).

## 2. Screen Layout (240x320)

### A. The Main Game View
*   **Left Sidebar (0 to 60px):**
    *   **HOLD:** 48x48px box (Top).
    *   **LEVEL:** Small digital readout (Middle).
    *   **LINES:** Counter (Bottom).
*   **The Matrix (60 to 180px):**
    *   Centered 10x20 grid.
    *   1px dark-grey grid lines (#1A1A1A).
    *   Subtle "CRT" scanline overlay for texture.
*   **Right Sidebar (180 to 240px):**
    *   **NEXT:** 48x48px box (Top).
    *   **SCORE:** Vertical stack of numbers.
    *   **GOAL:** Points/Lines to next level.

### B. Header / Footer (Top 40px / Bottom 40px)
*   **Top 40px:** Small "TETRIS ART" logo in center.
*   **Bottom 40px:** Contextual buttons (e.g., "PAUSE" or "MENU").

## 3. Visual Effects
*   **Pixel Glow:** Blocks have a 1-2px outer glow of their own color.
*   **Ghost Piece:** A 1px dashed outline of the landing position.
*   **Hard Drop Shudder:** A screen shake of 1-2 pixels when a piece "Hard Drops."
*   **Line Clear Flash:** The entire row flashes pure white (#FFFFFF) for 2 frames before disappearing.

## 4. Typography
*   **Main:** 8-bit or 16-bit Pixel Font (e.g., *Press Start 2P* or a custom thin pixel font).
*   **Numbers:** High-contrast digital segment style.
