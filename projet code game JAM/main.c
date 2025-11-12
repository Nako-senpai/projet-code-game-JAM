#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int main(void)
{
    Game game;
    initGame(&game);

    while (sfRenderWindow_isOpen(game.window))
    {
        handleEvent(&game);
        updateGame(&game);
        drawGame(&game);
    }

    cleanupGame(&game);
    return EXIT_SUCCESS;
}

