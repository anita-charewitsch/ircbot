#include "Bot.h"

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        perror("Es sind drei Argumente notwendig");
        exit(1);
    }
    Bot *bot = new Bot("BabyBot", "babybot123");
    bot->ConnectToServer(string(argv[1]), atoi(argv[2]), argv[3]);

    delete bot;
    return 0;
}
