#pragma once

/**
 * This enum class is used in the main() function. Used for logical definition for elements which should be drawn.
 */
enum class GameState {
    inMainMenu,
    inGame,
    inMode,
    inHighScores,
    inLoadGame,
    inSaveGame,
    inDeleteGame
};