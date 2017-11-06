#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prints the hangman. The number of body parts displayed
// corresponds to the the number of incorrect guesses the player
// has made so far
void print_hangman(int numStrikes)
{
    // Prints the top of the gallows pole
    printf("------\n");
    printf("|    |\n");
    // Prints the hangman's head if at least one incorrect guess
    // has been made
    if (numStrikes >= 1)
    {
        printf("|    O\n");
    }
    else
    {
        printf("|     \n");
    }
    // Prints left arm if at least three incorrect guesses have
    // been made
    if (numStrikes >= 3)
    {
        printf("|   /|\\\n");
    }
    // Prints the right arm if at least two incorrect guesses have
    // been made
    else if (numStrikes >= 2)
    {
        printf("|   /|\n");
    }
    else
    {
        printf("|     \n");
    }
    // prints the left leg if five incorrect guesses have been made
    // (max amount)
    if (numStrikes >= 5)
    {
        printf("|   / \\\n");
    }
    // Prints the right leg if at least four incorrect guesses have
    // been made
    else if (numStrikes >= 4)
    {
        printf("|   / \n");
    }
    else
    {
        printf("|    \n");
    }
    // Prints the base of the gallows pole
    printf("|\n");
    printf("|__________\n");
}

// Prints the title screen
void print_title()
{
    // Prints the title's header text
    printf("##### HANGMAN #####\n");
    // Prints the full hangman
    print_hangman(5);
    // Prints the possible commands for the player to enter
    printf("ENTER \"START\" TO BEGIN!\n");
    printf("ENTER \"QUIT\" TO EXIT.\n\n");
    printf(">");
}

// Clears all the content from the open terminal window
// (only works in Windows)
void clear_screen()
{
    // This only works on Windows. Calls the command "cls" on the command line to clear
    // the screen.
    system("cls");

    // The reason this function exists is not to save space and avoid repetition of code
    // (it only consists of one line, after all),but rather to provide clarity for the reader
    // as to what the code is actually doing.
}

int main()
{
    // Initialize variables

    // File variable referencing the file wordbank.txt
    // which has contains all the possible words that the
    // game may ask the player to spell (currently over 100!
    FILE *wordbank = fopen("wordbank.txt", "r");

    // String variable storing the player's input
    char s[1];
    
    // Runs the game loop until the player decides to quit
    while (1)
    {
        clear_screen();

        print_title();

        scanf("%s", s);

        printf("%s\n", s);

        while ( strncmp(s, "START", strlen(s)) && strncmp(s, "QUIT", strlen(s)) )
        {
            printf("INVALID INPUT\n");
            scanf("%s", s);
        }

        if (!strncmp(s, "START", strlen(s)))
        {
            printf("YAY!\n");
            return 0;
        }

        if (!strncmp(s, "QUIT", strlen(s)))
        {
            return 0;
        }

        if (strlen(s) > 1)
        {
            printf("Too long!\n");
        }
    }
}
