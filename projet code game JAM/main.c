#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int main(void)
{
    Game game;
    Money money;
    SnowmanIconeID iconeID;
    HP hp;

    game.state = MENUE;

    initGame(&game, &money, &iconeID, &hp);

    while (sfRenderWindow_isOpen(game.window)) 
    {
        handleEvent(&game);

        if (game.state==MENUE)
        {
            drawMenu(&game);
            updateMenu(&game);
        }
        if (game.state == PLAYING)
        {
            updateGame(&game, &money, &iconeID, &hp);
            drawGame(&game, &money, &hp);
        }
    }

    cleanupGame(&game);
    return EXIT_SUCCESS;
}

