#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <time.h>
#include <string.h>

// prototypes
bool validate(int argc, string argv[]);
void fill_array(int arr[], int len);
void sort_array(int arr[], int len, int wait_ms);
void print_data(int arr[], int len, int active, int done, string status, int wait_ms);
void delay(int milliseconds);

// printf ANSI colors
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

// strings
#define STR_START   "START"
#define STR_SWAP    "SWAP!"
#define STR_NO_SWAP " OK!"
#define STR_END     "DONE"

// constant
#define MIN_WAIT_FOR_VERBOSE 125;

int main(int argc, string argv[])
{
    // failure
    if (validate(argc, argv) == false)
    {
        printf(COLOR_RED);
        printf("Usage: bubblesort <length 2 - 100> <delay 5 - 1000>\n");
        printf(COLOR_RESET);
        return 1;
    }

    // create array
    int data_len = atoi(argv[1]);
    int data[data_len];
    int wait_ms = atoi(argv[2]);

    fill_array(data, data_len);
    sort_array(data, data_len, wait_ms);

    // success
    return 0;
}

/*
 * Validate the inputs to the file and return validity
 */
bool validate(int argc, string argv[])
{
    bool valid = true;

    // accept exactly one argument
    if (argc != 3)
    {
        valid = false;
        return valid;
    }

    int len = atoi(argv[1]);
    // array length must be positive int 2 - 100
    if (len < 2 || len > 100)
    {
        valid = false;
        return valid;
    }

    int delay = atoi(argv[2]);
    // delay ms must be positive int 5 - 1000
    if (delay < 5 || delay > 1000)
    {
        valid = false;
        return valid;
    }

    // success
    return valid;
}

/*
 * Fill the array with random ints
 */
void fill_array(int arr[], int len)
{
    // random seed based on current time
    srand(time(NULL));

    for (int i = 0; i < len; i++)
    {
        // len * 5 reduces duplicate numbers
        arr[i] = rand() % (len * 5);
    }
}

/*
 * Sort the array
 */
void sort_array(int arr[], int len, int wait_ms)
{
    //draw the unsorted values
    print_data(arr, len, -10, 0, STR_START, wait_ms);

    // main passes through the array
    for (int i = 0; i < len - 1; i++)
    {
        // items that must be correct this pass
        int confirmed = i;

        //draw the results of the previous pass
        print_data(arr, len, -10, confirmed, "", wait_ms * 2);

        // don't loop through any confirmed values
        int max = len - confirmed - 1;

        // compare each unconfirmed pair
        for (int j = 0; j < max; j++)
        {
            // draw the numbers being compared
            print_data(arr, len, j, confirmed, "", wait_ms);

            // compare each number and swap if neccesary
            if (arr[j + 1] < arr[j])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                // draw the swapped results
                print_data(arr, len, j, confirmed, STR_SWAP, wait_ms);
            }
            else
            {
                // draw the unswapped results
                print_data(arr, len, j, confirmed, STR_NO_SWAP, wait_ms);
            }
        }
    }
    // draw all values green
    print_data(arr, len, -10, len, "", wait_ms * 1.5);
    // draw the final results
    print_data(arr, len, -10, 0, STR_END, wait_ms * 0.5);
}

/*
 * Print out all the elements in the array
 */
void print_data(int arr[], int len, int active, int done, string status, int wait_ms)
{
    // empty the screen
    system("clear");

    bool verbose = wait_ms >= MIN_WAIT_FOR_VERBOSE;

    // loop one higher than normal, to add ) after last
    for (int i = 0; i <= len; i++)
    {
        // position used for bracketing etc
        int relative_pos = i - active;

        // comparison graphics disabled at fast speeds
        if (verbose)
        {
            // figure out how to prefix the value
            switch (relative_pos)
            {
                // highlight the current values being compared
                case 0:
                    printf(COLOR_CYAN);
                    printf("(");
                    printf(COLOR_RESET);
                    break;
                case 1:
                    // draw the comparison
                    if (arr[active] > arr[active + 1])
                    {
                        printf(COLOR_RED);
                        printf(">");
                        printf(COLOR_RESET);
                    }
                    else if (arr[active] < arr[active + 1])
                    {
                        printf(COLOR_GREEN);
                        printf("<");
                        printf(COLOR_RESET);
                    }
                    // values must be equal
                    else
                    {
                        printf(COLOR_GREEN);
                        printf("=");
                        printf(COLOR_RESET);
                    }
                    break;
                case 2:
                    printf(COLOR_CYAN);
                    printf(")");
                    printf(COLOR_RESET);
                    break;
                // when not active comparison, just leave a space
                default:
                    printf(" ");
                    break;
            }
        }
        // not verbose, all values preceeded with spaces
        else
        {
            printf(" ");
        }
        // leave off the last number [so ) can end the line]
        if (i < len)
        {
            // green for values guaranteed done
            if (i >= len - done)
            {
                printf(COLOR_GREEN);
            }
            // yellow for current comparison
            if (!verbose && (relative_pos == 0 || relative_pos == 1))
            {
                printf(COLOR_MAGENTA);
            }
            // finally print the current value
            printf("%i", arr[i]);
            printf(COLOR_RESET);
        }
    }
    // draw status in the correct color
    if (strcmp(status, STR_START) == 0)
    {
        printf(COLOR_YELLOW);
    }
    else if (strcmp(status, STR_NO_SWAP) == 0 || strcmp(status, STR_END) == 0)
    {
        printf(COLOR_GREEN);
    }
    else if (strcmp(status, STR_SWAP) == 0)
    {
        printf(COLOR_RED);
    }
    else
    {
        printf(COLOR_RESET);
    }
    // status disabled at high speeds except for "done"
    if (!verbose && strcmp(status, STR_END) != 0)
    {
        status = "";
        printf(COLOR_RESET);
    }

    printf("\n  %s", status);
    printf(COLOR_RESET);
    printf("\n");
    // wait
    delay(wait_ms);
}

/*
 * Delay for a given amount of milliseconds
 */
void delay(int milliseconds)
{
    // type "clock_t" is ticks
    clock_t start = clock();
    clock_t now = clock();
    long delay = milliseconds * (CLOCKS_PER_SEC / 1000);

    // still waiting
    while (now < start + delay)
    {
        // update the current time
        now = clock();
    }
}
