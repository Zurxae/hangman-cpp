#include "hangman.h"

int main()
{
    hangman game;

    //Initialize random seed
    srand(time(NULL));

    //Intro
    game.intro();

    do
    {
        game.play();
    } while (game.isPlaying());

    game.outro();

    return 0;
}