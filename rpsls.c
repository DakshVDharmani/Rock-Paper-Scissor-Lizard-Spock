#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <termios.h>
void display_delay(const char* text, int delay)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        putchar(text[i]);
        fflush(stdout);
        usleep(delay * 1000);
    }
    printf("\n");
}
int kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    if (tcgetattr(STDIN_FILENO, &oldt) == -1)
    {
        perror("tcgetattr");
        return 0;
    }
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) == -1)
    {
        perror("tcsetattr");
        return 0;
    }
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    if (oldf == -1)
    {
        perror("fcntl");
        return 0;
    }
    if (fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK) == -1)
    {
        perror("fcntl");
        return 0;
    }
    ch = getchar();
    if (tcsetattr(STDIN_FILENO, TCSANOW, &oldt) == -1)
    {
        perror("tcsetattr");
        return 0;
    }
    if (fcntl(STDIN_FILENO, F_SETFL, oldf) == -1)
    {
        perror("fcntl");
        return 0;
    }
    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}
int countdown ()
{
    restart_countdown:
    time_t startTime = time(NULL);
    char userInput[1000];
    int timeLimit = 30;
    int player_choice = 0;
    display_delay("Welcome to Rock, Paper, Scissors, Lizard, Spock\n", 50);
    display_delay("Choose your move (1-Rock, 2-Paper, 3-Scissors, 4-Lizard, 5-Spock): \n", 50);
    display_delay("You have 30 seconds to answer. Type your choice to stop the countdown.\n", 50);
    while (1)
    {
        time_t currentTime = time(NULL);
        int elapsedTime = (int)difftime(currentTime, startTime);
        if (elapsedTime >= timeLimit)
        {
            display_delay("Time is up!\n", 50);
            goto restart_countdown;
        }
        if (kbhit())
        {
            fgets(userInput, sizeof(userInput), stdin);
            userInput[strcspn(userInput, "\n")] = 0;
            display_delay("You answered: ", 50);
            display_delay(userInput, 50);
            sscanf(userInput, "%d", &player_choice);
            if (player_choice >= 1 && player_choice <= 5)
            {
                break;
            }
            else
            {
                display_delay("Invalid input. Please choose a number between 1 and 5.\n", 50);
            }
        }
        sleep(1);
    }
    return player_choice;
}
void random_single_player()
{
    int player_choice;
    srand(time(NULL));
    int computer_choice = rand() % 5 + 1;
    player_choice = countdown();
    printf("You chose: %d\n", player_choice);
    switch (computer_choice)
    {
        case 1:
            display_delay("Computer chose Rock!\n", 50);
            break;
        case 2:
            display_delay("Computer chose Paper!\n", 50);
            break;
        case 3:
            display_delay("Computer chose Scissors!\n", 50);
            break;
        case 4:
            display_delay("Computer chose Lizard!\n", 50);
            break;
        case 5:
            display_delay("Computer chose Spock!\n", 50);
            break;
        default:
            display_delay("Invalid choice.\n", 50);
    }
    switch (player_choice)
    {
        case 1:
            display_delay("You chose Rock!\n", 50);
            break;
        case 2:
            display_delay("You chose Paper!\n", 50);
            break;
        case 3:
            display_delay("You chose Scissors!\n", 50);
            break;
        case 4:
            display_delay("You chose Lizard!\n", 50);
            break;
        case 5:
            display_delay("You chose Spock!\n", 50);
            break;
        default:
            display_delay("Invalid choice.\n", 50);
    }
    printf("Computer chose: %d\n", computer_choice);
    if (player_choice == computer_choice)
    {
        display_delay("It's a tie!\n", 50);
    }
    else if (player_choice == 1 && (computer_choice == 3 || computer_choice == 4))
    {
        display_delay("You win!\n", 50);
        sleep(1);
        display_delay("Congratulations, Player!\n", 50);
    }
    else if (player_choice == 2 && (computer_choice == 1 || computer_choice == 5))
    {
        display_delay("You win!\n", 50);
        sleep(1);
        display_delay("Congratulations, Player!\n", 50);
    }
    else if (player_choice == 3 && (computer_choice == 2 || computer_choice == 4))
    {
        display_delay("You win!\n", 50);
        sleep(1);
        display_delay("Congratulations, Player!\n", 50);
    }
    else if (player_choice == 4 && (computer_choice == 2 || computer_choice == 5))
    {
        display_delay("You win!\n", 50);
        sleep(1);
        display_delay("Congratulations, Player!\n", 50);
    }
    else if (player_choice == 5 && (computer_choice == 3 || computer_choice == 1))
    {
        display_delay("You win!\n", 50);
        sleep(1);
        display_delay("Congratulations, Player!\n", 50);
    }
    else
    {
        display_delay("You lose!\n", 50);
        display_delay("Better luck next time, Player!\n", 50);
    }
}
void random_double_player()
{
    restart_double_player:
    int player_choice;
    display_delay("Let's start with Player One", 50);
    sleep(1);
    player_choice = countdown();
    int player_one_choice = player_choice;
    display_delay("Let's continue with Player Two", 50);
    sleep(1);
    player_choice = countdown();
    int player_two_choice = player_choice;
    if (player_one_choice == player_two_choice)
    {
        display_delay("It's a tie!\n", 50);
        sleep(1);
    }
    else if (player_one_choice == 1 && (player_two_choice == 3 || player_two_choice == 4))
    {
        display_delay("Player One wins!\n", 50);
        sleep(1);
        display_delay("Player Two, better luck next time!\n", 50);
    }
    else if (player_one_choice == 2 && (player_two_choice == 1 || player_two_choice == 5))
    {
        display_delay("Player One wins!\n", 50);
        sleep(1);
        display_delay("Player Two, better luck next time!\n", 50);
    }
    else if (player_one_choice == 3 && (player_two_choice == 2 || player_two_choice == 4))
    {
        display_delay("Player One wins!\n", 50);
        sleep(1);
        display_delay("Player Two, better luck next time!\n", 50);
    }
    else if (player_one_choice == 4 && (player_two_choice == 2 || player_two_choice == 5))
    {
        display_delay("Player One wins!\n", 50);
        sleep(1);
        display_delay("Player Two, better luck next time!\n", 50);
    }
    else if (player_one_choice == 5 && (player_two_choice == 3 || player_two_choice == 1))
    {
        display_delay("Player One wins!\n", 50);
        sleep(1);
        display_delay("Player Two, better luck next time!\n", 50);
    }
    else if (player_one_choice <= 0 || player_one_choice > 5 || player_two_choice <= 0 || player_two_choice > 5)
    {
        display_delay("Invalid input! Let's try again.\n", 50);
        sleep(1);
        goto restart_double_player;
    }
    else
    {
        display_delay("Player Two wins!\n", 50);
        display_delay("Player One, better luck next time!\n", 50);
        sleep(1);
    }
}
void random_triple_player ()
{
    int player_choice;
    display_delay("Let's start with Player One\n", 50);
    sleep(1);
    player_choice = countdown();
    int player_one_choice = player_choice;
    display_delay("Let's continue with Player Two\n", 50);
    sleep(1);
    player_choice = countdown();
    int player_two_choice = player_choice;
    display_delay("Let's continue with Player Three\n", 50);
    sleep(1);
    player_choice = countdown();
    int player_three_choice = player_choice;
    if (player_one_choice == player_two_choice && player_two_choice == player_three_choice)
    {
        display_delay("It's a tie!\n", 50);
        sleep(1);
    }
    else if (player_one_choice == player_two_choice)
    {
        if (player_one_choice == 1 && (player_three_choice == 3 || player_three_choice == 4))
        {
            display_delay("Player One and Player Two have tied, and they win against PLayer Three\n", 50);
            sleep(1);
            display_delay("Player Three, better luck next time\n", 50);
        }
        else if (player_one_choice == 2 && (player_three_choice == 1 || player_three_choice == 5))
        {
            display_delay("Player One and Player Two have tied, and they win against Player Three\n", 50);
            sleep(1);
            display_delay("Player Player Three, better luck next time\n", 50);
        }
        else if (player_one_choice == 3 && (player_three_choice == 2 || player_three_choice == 4))
        {
            display_delay("Player one and Player two have tied, and they win against Player three\n", 50);
            sleep(1);
            display_delay("Player three, better luck next time\n", 50);
        }
        else if (player_one_choice == 4 && (player_three_choice == 2 || player_three_choice == 5))
        {
            display_delay("player one and player two have tied, and they win against player three\n", 50);
            sleep(1);
            display_delay("Player player three, better luck next time\n", 50);
        }
        else if (player_one_choice == 5 && (player_three_choice == 3 || player_three_choice == 1))
        {
            display_delay("Player One and Player Two have tied, and they win against Player Three\n", 50);
            sleep(1);
            display_delay("Player Three, better luck next time\n", 50);
        }
        else
        {
            display_delay("Player One and Player Two have tied, but Player Three wins against both\n", 50);
            sleep(1);
            display_delay("Player One and Player Two, better luck next time\n", 50);
        }

    }
        else if (player_two_choice == player_three_choice)
        {
            if (player_two_choice == 1 && (player_one_choice == 3 || player_one_choice == 4))
            {
                display_delay("Player Two and Player Three have tied, and they win against Player One\n", 50);
                sleep(1);
                display_delay("Player One, better luck next time\n", 50);
            }
            else if (player_two_choice == 2 && (player_one_choice == 1 || player_one_choice == 5))
            {
                display_delay("Player Two and Player Three have tied, and they win against Player One\n", 50);
                sleep(1);
                display_delay("Player One, better luck next time\n", 50);
            }
            else if (player_two_choice == 3 && (player_one_choice == 2 || player_one_choice == 4))
            {
                display_delay("Player Two and Player Three have tied, and they win against Player One\n", 50);
                sleep(1);
                display_delay("Player One, better luck next time\n", 50);
            }
            else if (player_two_choice == 4 && (player_one_choice == 2 || player_one_choice == 5))
            {
                display_delay("Player Two and Player Three have tied, and they win against Player One\n", 50);
                sleep(1);
                display_delay("Player One, better luck next time\n", 50);
            }
            else if (player_two_choice == 5 && (player_one_choice == 3 || player_one_choice == 1))
            {
                display_delay("Player Two and Player Three have tied, and they win against Player One\n", 50);
                sleep(1);
                display_delay("Player Two and Player Three, better luck next time\n", 50);
            }
            else
            {
                display_delay("Player Two and Player Three have tied, but Player One wins against both\n", 50);
                sleep(1);
                display_delay("Player Two and Player Three, better luck next time\n", 50);
            }
        }
        else if (player_one_choice == player_three_choice)
        {
            if (player_one_choice == 1 && (player_two_choice == 3 || player_two_choice == 4))
            {
                display_delay("Player One and Player Three have tied, and they win against Player Two\n", 50);
                sleep(1);
                display_delay("Player Two, better luck next time\n", 50);
            }
            else if (player_one_choice == 2 && (player_two_choice == 1 || player_two_choice == 5))
            {
                display_delay("Player One and Player Three have tied, and they win against Player Two\n", 50);
                sleep(1);
                display_delay("Player Two, better luck next time\n", 50);
            }
            else if (player_one_choice == 3 && (player_two_choice == 2 || player_two_choice == 4))
            {
                display_delay("Player One and Player Three have tied, and they win against Player Two\n", 50);
                sleep(1);
                display_delay("Player Two, better luck next time\n", 50);
            }
            else if (player_one_choice == 4 && (player_two_choice == 2 || player_two_choice == 5))
            {
                display_delay("Player One and Player Four have tied, and they win against Player Two\n", 50);
                sleep(1);
                display_delay("Player Two, better luck next time\n", 50);
            }
            else if (player_one_choice == 5 && (player_two_choice == 3 || player_two_choice == 1))
            {
                display_delay("Player One and Player Five have tied, and they win against Player Three\n", 50);
                sleep(1);
                display_delay("Player Three, better luck next time\n", 50);
            }
            else
            {
            display_delay("Player One and Player Three have tied, but Player Two wins against both\n", 50);
            sleep(1);
            display_delay("Player One and Player Three, better luck next time\n", 50);
            }
        }
        if ((player_one_choice == 1) && (player_two_choice == 3 || player_two_choice == 4))
        {
            if (player_three_choice == 3 || player_three_choice == 4)
            {
                if (player_three_choice == 3 && player_two_choice == 4)
                {
                    display_delay("Player One wins against Player Three and Player Four, and Player Three wins against Player Four\n", 50);
                    sleep(1);
                    display_delay("Player One, congratulations!\n", 50);
                }
                else if (player_three_choice == 4 && player_two_choice == 3)
                {
                    display_delay("Player One wins against Player Three and Player Four, and Player Four wins against Player Three\n", 50);
                    sleep(1);
                    display_delay("Player One, congratulations!\n", 50);
                }
            }
            else if (player_three_choice == 2 || player_three_choice == 5)
            {
                if (player_two_choice == 3 && player_three_choice == 5)
                {
                    display_delay("Player Three wins against Player Two and Player One, and Player One wins against Player Two\n", 50);
                    sleep(1);
                    display_delay("Player One, congratulations!\n", 50);
                }
                else if (player_two_choice == 3 && player_three_choice == 2)
                {
                    display_delay("The game ties as all three players are dead!\n", 50);
                    sleep(1);
                }
                else if (player_two_choice == 4 && player_three_choice == 5)
                {
                    display_delay("The game ties as all three players are dead!\n", 50);
                    sleep(1);
                }
                else if (player_two_choice == 4 && player_three_choice == 2)
                {
                    display_delay("The game ties as all three players are dead!\n", 50);
                    sleep(1);
                }
            }
        }
        else if (player_one_choice == 1 && (player_two_choice == 2 || player_two_choice == 5))
        {
            if (player_three_choice == 3 || player_three_choice == 4)
            {
                if (player_two_choice == 2 && player_three_choice == 3)
                {
                    display_delay("The game ties as all three players are dead!\n", 50);
                    sleep(1);
                }
                else if (player_two_choice == 2 && player_three_choice == 4)
                {
                    display_delay("The game ties as all three players are dead!\n", 50);
                    sleep(1);
                }
                else if (player_two_choice == 5 && player_three_choice == 3)
                {
                    display_delay("Player Two wins against Player One and Player Three, and Player One wins against Player Three\n", 50);
                    sleep(1);
                    display_delay("Player Two, congratulations!\n", 50);
                }
                else if (player_two_choice == 5 && player_three_choice == 4)
                {
                    display_delay("The game ties as all three players are dead!\n", 50);
                    sleep(1);
                }
            }
            else if (player_three_choice == 2 || player_three_choice == 5)
            {
                if (player_three_choice == 2 && player_two_choice == 5) {
                    display_delay("Player Three wins against Player Two and Player One, and Player Two wins against Player One\n", 50);
                    sleep(1);
                    display_delay("Player Three, congratulations!\n", 50);
                }
                else if (player_three_choice == 5 && player_two_choice == 2) {
                    display_delay("Player Two loses against Player Three and Player One, and Player Three wins against Player One\n", 50);
                    sleep(1);
                    display_delay("Player Two, better luck next time\n", 50);
                }
            }
        }
        else if (player_one_choice == 2 && (player_two_choice == 1 || player_two_choice == 5))
        {
            if (player_three_choice == 1 || player_three_choice == 5)
            {
                if (player_three_choice == 1 && player_two_choice == 5)
                {
                    display_delay("Player Two wins against Player One and Player Three, and Player One wins against Player Three\n", 50);
                    sleep(1);
                    display_delay("Player Two, congratulations!\n", 50);
                }
                else if (player_three_choice == 5 && player_two_choice == 1)
                {
                    display_delay("Player Two wins against Player One and Player Three, and Player Three wins against Player One\n", 50);
                    sleep(1);
                    display_delay("Player Two, congratulations!\n", 50);
                }
            }
            else if (player_three_choice == 3 || player_three_choice == 4)
            {
                if (player_two_choice == 1 && player_three_choice == 3) {
                    display_delay("The game ties as all players are dead!\n", 50);
                    sleep(1);
                }
                else if (player_two_choice == 1 && player_three_choice == 4) {
                    display_delay("The game ties as all players are dead!\n", 50);
                    sleep(1);
                }
                else if (player_two_choice == 5 && player_three_choice == 3) {
                    display_delay("The game ties as all players are dead!\n", 50);
                    sleep(1);
                }
                else if (player_two_choice == 5 && player_three_choice == 4) {
                    display_delay("Player Three wins against Player Two and Player One, and Player One wins against Player Two\n", 50);
                    sleep(1);
                    display_delay("Player Three, congratulations!\n", 50);
                }
            }
        }
        else if (player_one_choice == 2 && (player_two_choice == 3 && player_two_choice == 4))
        {
            if (player_three_choice == 1 || player_three_choice == 5)
            {
                if (player_three_choice == 1 && player_two_choice == 3)
                {
                    display_delay("The game ties as all players are dead.\n", 50);
                    sleep(1);
                }
                else if (player_three_choice == 5 && player_two_choice == 3)
                {
                    display_delay("The game ties as all players are dead!\n", 50);
                    sleep(1);
                }
                else if (player_two_choice == 4 && player_three_choice == 1)
                {
                    display_delay("The game ties as all players are dead!\n", 50);
                    sleep(1);
                }
                else if (player_two_choice == 4 && player_three_choice == 5)
                {
                    display_delay("Player two wins against player one and player three, and player three wins against player one.\n", 50);
                    sleep(1);
                    display_delay("Player two, congratulations!\n", 50);
                }
            }
            else if (player_three_choice == 3 || player_three_choice == 4)
            {
                if (player_two_choice == 4 && player_three_choice == 3)
                {
                    display_delay("Player three wins against player one and player two, and player two wins against player one.\n", 50);
                    sleep(1);
                    display_delay("Player three, congratulations!\n", 50);
                }
                else if (player_three_choice == 4 && player_two_choice == 3)
                {
                    display_delay("Player two wins against player three and player one, and player three wins against player one.\n", 50);
                    sleep(1);
                    display_delay("Player two, congratulations!\n", 50);
                }
            }
        }
        else if (player_one_choice == 3 && (player_two_choice == 4 || player_two_choice == 2))
        {
            if (player_three_choice == 4 && player_three_choice == 2)
            {
                if (player_two_choice == 2 && player_three_choice == 4)
                {
                    display_delay("Player one wins against player two and player three, and player three wins against player two.\n", 50);
                    sleep(1);
                    display_delay("Player one, congratulations!\n", 50);
                }
                else if (player_three_choice == 2 && player_two_choice == 4)
                {
                    display_delay("Player one wins against player two and player three, and player two wins against player three.\n", 50);
                    sleep(1);
                    display_delay("Player one, congratulations!\n", 50);
                }
            }
            else if (player_three_choice == 1 && player_three_choice == 5)
            {
                if (player_three_choice == 1 && player_two_choice == 4)
                {
                    display_delay("Player three wins against player two and player one, and player one wins against player two.\n", 50);
                    sleep(1);
                    display_delay("Player three, congratulations!\n", 50);
                }
                else if (player_three_choice == 5 && player_two_choice == 4)
                {
                    display_delay("The game ties as all players are dead.\n", 50);
                    sleep(1);
                }
                else if (player_three_choice == 1 && player_two_choice == 2)
                {
                    display_delay("The game ties as all players are dead.\n", 50);
                    sleep(1);
                }
                else if (player_three_choice == 5 && player_two_choice == 2)
                {
                    display_delay("The game ties as all players are dead.\n", 50);
                    sleep(1);
                }
            }
        }
        else if (player_one_choice == 3 && (player_two_choice == 1 || player_two_choice == 5))
        {
            if (player_three_choice == 1 || player_three_choice == 5)
            {
                if (player_two_choice == 1 && player_three_choice == 5)
                {
                    display_delay("Player three wins against Player two and Player one, and Player two wins against Player one.\n", 50);
                    sleep(1);
                    display_delay("Player three, congratulations!\n", 50);
                }
                else if (player_two_choice == 5 && player_three_choice == 1)
                {
                    display_delay("Player two wins against Player three and Player one, and Player three wins against Player one.\n", 50);
                    sleep(1);
                    display_delay("Player two, congratulations!\n", 50);
                }
            }
            else if (player_three_choice == 2 || player_three_choice == 4)
            {
                if (player_three_choice == 2 && player_two_choice == 1)
                {
                    display_delay("The game ties as all players are dead.\n", 50);
                    sleep(1);
                }
                else if (player_three_choice == 4 && player_two_choice == 1)
                {
                    display_delay("Player one wins against Player three and Player two, and Player two wins against Player one.\n", 50);
                    sleep(1);
                    display_delay("Player one, better luck next time.\n", 50);
                }
                else if (player_three_choice == 2 && player_two_choice == 5)
                {
                    display_delay("The game ties as all players are dead.\n", 50);
                    sleep(1);
                }
                else if (player_three_choice == 4 && player_two_choice == 5)
                {
                    display_delay("The game ties as all players are dead.\n", 50);
                    sleep(1);
                }
            }
        }
        else if (player_one_choice == 4 && (player_two_choice == 2 || player_two_choice == 5))
        {
            if (player_three_choice == 2 || player_three_choice == 5)
            {
                if (player_three_choice == 2 && player_two_choice == 5)
                {
                    display_delay("Player one wins against Player two and Player three, and Player three wins against Player two.\n", 50);
                    sleep(1);
                    display_delay("Player one, congratulations!\n", 50);
                }
                else if (player_three_choice == 5 && player_two_choice == 2)
                {
                    display_delay("Player one wins against Player three and Player two, and Player two wins against Player three.\n", 50);
                    sleep(1);
                    display_delay("Player one, congratulations!\n", 50);
                }
            }
            else if (player_three_choice == 1 || player_three_choice == 3)
            {
                if (player_three_choice == 1 && player_two_choice == 2)
                {
                    display_delay("The game ties as all players are dead.\n", 50);
                    sleep(1);
                }
                else if (player_three_choice == 3 && player_two_choice == 2)
                {
                    display_delay("Player three wins against Player two and Player one, and Player one wins against Player two.\n", 50);
                    sleep(1);
                    display_delay("Player three, congratulations!\n", 50);
                }
                else if (player_three_choice == 1 && player_two_choice == 5)
                {
                    display_delay("The game ties as all players are dead.\n", 50);
                    sleep(1);
                }
                else if (player_three_choice == 3 && player_two_choice == 5)
                {
                    display_delay("The game ties as all players are dead.\n", 50);
                    sleep(1);
                }
            }
        }
        else if (player_one_choice == 4 && (player_two_choice == 1 || player_two_choice == 3))
        {
            if (player_three_choice == 1 || player_three_choice == 3)
            {
                if (player_three_choice == 1 && player_two_choice == 3)
                {
                    display_delay("Player three wins against Player two and Player one, and Player two wins against Player one.\n", 50);
                    sleep(1);
                    display_delay("Player three, congratulations!\n", 50);
                }
                else if (player_three_choice == 3 && player_two_choice == 1)
                {
                    display_delay("Player two wins against Player one and Player three, and Player three wins against Player one.\n", 50);
                    sleep(1);
                    display_delay("Player two, congratulations!\n", 50);
                }
            }
            else if (player_three_choice == 2 || player_three_choice == 5)
            {
                if (player_three_choice == 2 && player_two_choice == 1)
                {
                    display_delay("The game ties as all players are dead.\n", 50);
                    sleep(1);
                }
                else if (player_three_choice == 5 && player_two_choice == 1)
                {
                    display_delay("The game ties as all players are dead.\n", 50);
                    sleep(1);
                }
                else if (player_three_choice == 2 && player_two_choice == 3)
                {
                    display_delay("Player two wins against Player one and Player three, and Player one wins against Player three.\n", 50);
                    sleep(1);
                    display_delay("Player two, congratulations!\n", 50);
                }
                else if (player_three_choice == 5 && player_two_choice == 3)
                {
                    display_delay("The game ties as all players are dead.\n", 50);
                    sleep(1);
                }
            }
        }
        else if (player_one_choice == 5 && (player_two_choice == 3 || player_two_choice == 1))
        {
            if (player_three_choice == 3 || player_three_choice == 1)
            {
                if (player_three_choice == 3 && player_two_choice == 1)
                {
                    display_delay("Player one wins against Player three and Player two, and Player two wins against Player three.\n", 50);
                    sleep(1);
                    display_delay("Player one, congratulations!\n", 50);
                }
                else if (player_three_choice == 1 || player_two_choice == 3)
                {
                    display_delay("Player one wins against Player three and Player two, and Player three wins against Player two.\n", 50);
                    sleep(1);
                    display_delay("Player one, congratulations!\n", 50);
                }
            }
            else if (player_three_choice == 2 || player_three_choice == 4)
            {
                if (player_three_choice == 2 && player_two_choice == 3)
                {
                    display_delay("The game ties as all players are dead!\n", 50);
                    sleep(1);
                }
                else if (player_three_choice == 4 && player_two_choice == 3)
                {
                    display_delay("The game ties as all players are dead.\n", 50);
                    sleep(1);
                }
                else if (player_three_choice == 2 && player_two_choice == 1)
                {
                    display_delay("Player three wins against Player two and Player one, and Player one wins against Player two.\n", 50);
                    sleep(1);
                    display_delay("Player three, congratulations!\n", 50);
                }
                else if (player_three_choice == 4 && player_two_choice == 1)
                {
                    display_delay("The game ties as all players are dead.\n", 50);
                    sleep(1);
                }
            }
        }
        else if (player_one_choice == 5 && (player_two_choice == 2 || player_two_choice == 4))
        {
            if (player_three_choice == 2 || player_three_choice == 4)
            {
                if (player_three_choice == 2 && player_two_choice == 4)
                {
                    display_delay("Player two wins against Player one and Player three, and Player three wins against Player one.\n", 50);
                    sleep(1);
                    display_delay("Player two, congratulations!\n", 50);
                }
                else if (player_three_choice == 4 && player_two_choice == 2)
                {
                    display_delay("Player three wins against Player two and Player one, and Player two wins against Player one.\n", 50);
                    sleep(1);
                    display_delay("Player three, congratulations!\n", 50);
                }
            }
            else if (player_three_choice == 1 || player_three_choice == 3)
            {
                if (player_three_choice == 1 && player_two_choice == 2)
                {
                    display_delay("Player two wins against Player one and Player three, and Player one wins against Player three.\n", 50);
                    sleep(1);
                    display_delay("Player two, congratulations!\n", 50);
                }
                else if (player_three_choice == 3 && player_two_choice == 2)
                {
                    display_delay("The game ties as all players are dead.\n", 50);
                    sleep(1);
                }
                else if (player_three_choice == 1 && player_two_choice == 4)
                {
                    display_delay("The game ties as all players are dead.\n", 50);
                    sleep(1);
                }
                else if (player_three_choice == 3 && player_two_choice == 4)
                {
                    display_delay("The game ties as all players are dead.\n", 50);
                    sleep(1);
                }
            }
        }
}
    
int main()
{
    restart:
    int num, turns, i;
        display_delay("How many challengers are ready to throw down?\nNote: In consent of only a single player, you will play versus the computer.\nMaximum number of players allowed is three. \nChoose wisely.", 50);
        scanf("%d", &num);
        if (num < 1 || num > 3)
        {
            display_delay("Invalid choice. Please choose a number between 1 and 3.\n", 50);
            goto restart;
        }
        display_delay("How many turns do you want to play?", 50);
        scanf("%d", &turns);
        printf("Each player will get %d turns.\n", turns);
        
        
            if (num == 1)
            {
                display_delay("You have chosen to play against the computer.\n", 50);
                sleep(1);
                display_delay("Player, Welcome to Rock, Paper, Scissors, Lizard, Spock!\n", 50);
                sleep(1);
                display_delay("Before we start the game, we shall equip you with the rules.\n", 50);
                display_delay("Rock crushes Scissors\nScissors cuts Paper\nPaper covers Rock\nRock crushes Lizard\nLizard poisons Spock\nSpock smashes Scissors\nScissors decapitates Lizard\nLizard eats Paper\nPaper disproves Spock\nSpock vaporizes Rock\n", 50);
                display_delay("Now that you are comfortable with the rules, let's begin.\n", 50);
                for (i = 0; i < turns; i++){
                random_single_player();}
            }
            else if (num == 2)
            {
                display_delay("You will play against an opponent.\n", 50);
                display_delay("Player 1 and PLayer 2, welcome to Rock, Paper, Scissors, Lizard, Spock!\n", 50);
                sleep(1);
                display_delay("Before we start the game, we shall equip you with the rules.\n", 50);
                display_delay("Rock crushes Scissors\nScissors cuts Paper\nPaper covers Rock\nRock crushes Lizard\nLizard poisons Spock\nSpock smashes Scissors\nScissors decapitates Lizard\nLizard eats Paper\nPaper disproves Spock\nSpock vaporizes Rock\n", 50);
                display_delay("Now that you are comfortable with the rules, let's begin.\n", 50);
                for (i = 0; i < turns; i++){
                random_double_player();}
            }
            else if (num == 3)
            {
                display_delay("You will play against three opponents.\n", 50);
                display_delay("Player 1, Player 2, and Player 3, welcome to Rock, Paper, Scissors, Lizard, Spock!\n", 50);
                sleep(1);
                display_delay("Before we start the game, we shall equip you with the rules.\n", 50);
                display_delay("Rock crushes Scissors\nScissors cuts Paper\nPaper covers Rock\nRock crushes Lizard\nLizard poisons Spock\nSpock smashes Scissors\nScissors decapitates Lizard\nLizard eats Paper\nPaper disproves Spock\nSpock vaporizes Rock\n", 50);
                display_delay("Now that you are comfortable with the rules, let's begin.\n", 50);
                for (i = 0; i < turns; i++){
                random_triple_player();}
            }
        
    display_delay("Thank you for playing!\n", 50);
    return 0;
}
