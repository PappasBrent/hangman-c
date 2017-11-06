#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_hangman(int numStrikes)
{
    printf("|    |\n");
    if (numStrikes >= 1)
    {
        printf("|    O\n");
    }
    else
    {
        printf("|     \n");
    }
    if (numStrikes >= 3)
    {
        printf("|   /|\\\n");
    }
    else if (numStrikes >= 2)
    {
        printf("|   /|\n");
    }
    else
    {
        printf("|     \n");
    }
    if (numStrikes >= 5)
    {
        printf("|   / \\\n");
    }
    else if (numStrikes >= 4)
    {
        printf("|   / \n");
    }
    else
    {
        printf("|    \n");
    }
    printf("|\n");
    printf("|__________\n");
}

void print_title()
{
    printf("##### HANGMAN #####\n");
    printf("------\n");
    print_hangman(5);
    printf("ENTER \"START\" TO BEGIN!\n");
    printf("ENTER \"QUIT\" TO EXIT.\n\n");
    printf(">");
}

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
    char s[1];

    while (1)
    {
        clear_screen();

        print_title();

        scanf("%s", s);

        printf("%s\n", s);

        if (!strncmp(s, "START", strlen(s)))
        {
            printf("YAY!\n");
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
