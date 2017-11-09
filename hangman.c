#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NUM_WORDS 123
#define MAX_STRING_LENGTH 100
#define NUM_LETTERS_IN_ALPHA 26

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
    printf("ENTER \"QUIT\" TO EXIT.\n");
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

// Assigns user input to a global variable, and capitalizes it
// for easier comparison
void assign_string_input_to(char s[])
{
    // Temporary string storing input
    char inputBuffer[1];
    // Assigns input to the temporary string
    scanf("%s", inputBuffer);
    // Assigns the capitalized version of the temporary string
    // to the global string specified
    strcpy(s, strupr(inputBuffer));
}

// Returns a random integer from within the range min to max
int random_int_in_range(int min, int max)
{
    // Integer storing random number
    int r;
    // Randomizes computer's seed based on the current time
    srand(time(NULL));
    r = (rand() % (max + 1)) + min;
    return r;
}

int main()
{
    // Initialize variables

    // Integer iterator variables
    int i, j, k;

    // Integer storing random number
    int r;

    // Integer storing the number of incorrect guesses
    // the player has made
    int numIncorrect;

    // String storing the current word that the player is
    // trying to guess
    char currentWord[MAX_STRING_LENGTH];

    // String storing the phrase that the console should currently
    // be outputting
    char currentConsolePhrase[MAX_STRING_LENGTH];

    // String storing the player's string input
    char s[MAX_STRING_LENGTH];

    // Char array storing the already guessed letters
    char guessedLetters[NUM_LETTERS_IN_ALPHA];

    // Character storing the player's char input
    char c;

    // File variable referencing the file wordbank.txt
    // which has contains all the possible words that the
    // game may ask the player to spell (currently over 100!)
    FILE *wordbankFile = fopen("wordbank.txt", "r");

    // String array storing words from the wordbank file
    char wordbank[NUM_WORDS][MAX_STRING_LENGTH];

    // Adds the words from the wordbank file to wordbank array
    // and converts them to uppercase
    for (i = 0; i < NUM_WORDS; i++)
    {
        fscanf(wordbankFile, "%s", wordbank[i]);
        strcpy(wordbank[i], strupr(wordbank[i]));
    }

    // for (i = 0; i < NUM_WORDS; i++)
    // {
    //     printf("%d: %s\n", i, wordbank[i]);
    // }

    // Runs the game loop until the player decides to quit
    while (1)
    {

        print_title();

        assign_string_input_to(s);

        if (strcmp(s, "START") || strcmp(s, "QUIT"))
        {
            clear_screen();
            printf("INVALID INPUT\n");
        }

        if (!strcmp(s, "START"))
        {
            clear_screen();
            // Resets the number of incorrect guesses the player has made
            numIncorrect = 0;
            // Assigns r to a random value within the range 0 to the NUM_WORDS - 1
            // so that a random string from wordbank can be obtained
            r = random_int_in_range(0, NUM_WORDS - 1);
            // Sets the value of currentWord to a random value from wordbank
            strcpy(currentWord, wordbank[r]);
            // printf("%d\n", random_int_in_range(0, NUM_WORDS - 1));
            // printf("%s\n", currentWord);
            // printf("%d\n", r);
            strcpy(currentConsolePhrase, "GUESS A LETTER");
            while (numIncorrect < 5)
            {
                clear_screen();
                print_hangman(numIncorrect);
                printf("%s\n", currentWord);
                printf("%s\n", currentConsolePhrase);
                printf("%c\n", c);
                scanf(" %c", &c);
                if (strchr(currentWord, c))
                {
                    strcpy(currentConsolePhrase, "CORRECT");
                }
                else
                {
                    strcpy(currentConsolePhrase, "WRONG");
                    numIncorrect++;
                }
            }
            clear_screen();
            printf("GAME OVER\n");
            print_hangman(numIncorrect);
            printf("PRESS ENTER TO RETURN TO THE TITLE SCREEN\n");
            do {
                getchar();
            }
            while (getchar() == ' ');
            clear_screen();
        }

        if (!strcmp(s, "QUIT"))
        {
            clear_screen();
            printf("GOOD BYE\n");
            return 0;
        }
    }
}
