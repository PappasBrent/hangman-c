#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Number of words in wordbank.txt.
// I would prefer a way to dynamically update this,
// but for now it is required to harcode the number of words
// in the wordbank into the top of the program
#define NUM_WORDS 123
// Maximum string length
#define MAX_STRING_LENGTH 100
// The number of letter in the alphabet
// (for all the possible letters the player can guess)
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
    printf("-----HANGMAN-----\n");
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

// Prints the game over screen. Takes on parameter, a string
// called correctWord that is the solution which the user
// failed to guess
void print_game_over(char *correctWord)
{
    // When the game is over, the screen is cleared,
    // "GAME OVER" is printed, the final state of the hangman
    // is displayed, and the player is prompted to return to the
    // title screen
    clear_screen();
    printf("GAME OVER\n");
    print_hangman(5);
    printf("THE CORRECT ANSWER WAS:\n%s\n", correctWord);
    printf("PRESS ENTER TO RETURN TO THE TITLE SCREEN\n");
}

// Checks if a character c is in a string s.
// Returns a 1 if so, or a 0 if not.
// I am aware that this could be achieved using the built-in
// function strchr instead of making my own; however
// I wanted to try and create that function myself
// using what we learned in class about loops.
// Also, my function differs in that it is optionally
// case sensitive
int char_in_string(char c, char *s, int caseSensitive)
{
    // Iterator variable
    int i;
    // Length of string to check
    int sLength = strlen(s);

    // If the characters are not case sensitive
    // (as denoted by caseSensitive being 0), then
    // c and s will both be made uppercase first before checking
    if (!caseSensitive)
    {
        c = toupper(c);
        strcpy(s, strupr(s));
    }

    // Iterates through the input string s
    for (i = 0; i < sLength; i++)
    {
        // Returns a 1 as soon as a character matching c
        // is found
        if (s[i] == c)
        {
            return 1;
        }
    }

    // If no character matching c is found, then
    // 0 is returned instead
    return 0;
}

// Appends a character to c to the end of a string s
void append_char_to_string(char c, char *s)
{
    // Length of string to append c to
    int sLength = strlen(s);

    // Assigns what was previously the terminating string character
    // to be the character c.
    s[sLength] = c;
    // Then, the terminating string character is shifted forward one place
    // to accommodate for the new size of the string
    s[sLength + 1] = '\0';
}

// Assigns player input to a global variable, and capitalizes it
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

        // Print the title
        print_title();

        // Get player input
        assign_string_input_to(s);

        // Prints "INVALID INPUT" if the player did not
        // enter "START" or "QUIT"
        if (strcmp(s, "START") || strcmp(s, "QUIT"))
        {
            clear_screen();
            printf("INVALID INPUT\n");
        }

        // If the player entered "START", then the game begins
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
                // Prints the correct answer under the hangman (used for testing)
                printf("%s\n", currentWord);
                
                // Iterates through the string, and checks if each
                // of its letters have already been guessed
                for (i = 0; i < strlen(currentWord); i++)
                {
                    // If the current letter that is being checked is in
                    // the guessedLetters string, then it must have already
                    // been guessed, and is printed
                    if (char_in_string(currentWord[i], guessedLetters, 0))
                    {
                        printf("%c ", currentWord[i]);
                    }
                    // If note, then a blank line (underscore) is printed
                    // instead so that the player knows how many letters there
                    // are in the word
                    else
                    {
                        printf("_ ");
                    }
                }
                // Prints a new line afterward
                printf("\n");
                // Prints the current phrase that the console should
                // be displaying
                printf("%s\n", currentConsolePhrase);
                // Prints the last letter that the player entered
                printf("%c\n", c);
                // Assigns the first character input to the value of c.
                // Notice the leading white space before %c. THIS IS IMPORTANT!
                // Also note that due to just how scanning for chars works in C,
                // the player can enter multiple letters at once, and then their
                // results will each be computed almost instantly. This allows
                // a player to take a guess at the entire word, but if they have gotten any
                // letters wrong in their guess, then their number of incorrect guesses
                // will be incremented almost instantly as well. So a wrong guess may
                // cause a player to instantly win or instantly lose
                scanf(" %c", &c);

                // First checks to see if the entered letter has already been guessed.
                // If so, the loop is immediately restarted.
                if (char_in_string(c, guessedLetters, 0))
                {
                    strcpy(currentConsolePhrase, "LETTER ALREADY GUESSED!");
                    continue;
                }

                // Checks if the entered letter is in the word that
                // the player is guessing
                // if (strchr(currentWord, c))
                if (char_in_string(c, currentWord, 0))
                {
                    // If so, then the console phrase is made positive
                    // and numIncorrect is not incremented
                    strcpy(currentConsolePhrase, "CORRECT");
                }
                else
                {
                    // If not, then the console phrase is made negative
                    // and numIncorrect is incremented by 1
                    strcpy(currentConsolePhrase, "WRONG");
                    numIncorrect++;
                }

                // Adds the entered letter to the guessedLetters array
                append_char_to_string(c, guessedLetters);
            }

            print_game_over(currentWord);

            // This little do while loop allows the player to simply
            // press enter to return to the title screen, without
            // having to enter a value first
            do
            {
                getchar();
            } while (getchar() == ' ');
            clear_screen();
        }

        // If the player entered "QUIT", then the
        // game returns 0 and ends
        if (!strcmp(s, "QUIT"))
        {
            clear_screen();
            printf("GOOD BYE\n");
            return 0;
        }
    }
}
