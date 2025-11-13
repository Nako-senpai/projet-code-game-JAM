#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int main(void)
{
    Game game;
    Money money;
    SnowmanIconeID iconeID;


    initGame(&game, &money);

    while (sfRenderWindow_isOpen(game.window))
    {
        handleEvent(&game);
        updateGame(&game, &money, &iconeID);
        drawGame(&game);
    }

    cleanupGame(&game);
    return EXIT_SUCCESS;
}

