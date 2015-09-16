#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <time.h>

// prototypes
bool validate(int argc, string argv[]);
void fill_array(int arr[], int len);
void sort_array(int arr[], int len);
void print_data(int arr[], int len, int active, int done, int pauses);
void delay(int milliseconds);

// printf ANSI colors
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

// constant
#define PAUSE_DUR 500

int main(int argc, string argv[])
{       
    // failure
    if (validate(argc, argv) == false)
    {
        return 1;
    }

    // create array
    int data_len = atoi(argv[1]);
    int data[data_len]; 
        
    fill_array(data, data_len);
    sort_array(data, data_len);
    
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
    if (argc != 2)
    {
        valid = false;
    }
    
    int len = atoi(argv[1]);
    // argument must be positive int up to 200
    if (len < 1 || len > 200)
    {
        valid = false;
    }
    
    if (valid == false)
    {
        printf(COLOR_RED);
        printf("Usage: bubblesort <array length 1 - 200>\n");
        printf(COLOR_RESET);
    }
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
void sort_array(int arr[], int len)
{   
    //draw the unsorted values
    print_data(arr, len, -10, 0, 1);    
    
    // main passes through the array
    for (int i = 0; i < len - 1; i++)
    {      
        // items that must be correct this pass
        int confirmed = i;
        
        //draw the results of the previous pass
        print_data(arr, len, -10, confirmed, 4);
        
        // don't loop through any confirmed values
        int max = len - confirmed - 1;
        
        // compare each unconfirmed pair
        for (int j = 0; j < max; j++)
        {
            // draw the numbers being compared
            print_data(arr, len, j, confirmed, 1);

            // compare each number and swap if neccesary
            if (arr[j + 1] < arr[j])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                
            }
            // draw the comparison results (swapped or not)
            print_data(arr, len, j, confirmed, 1);
            
        }
    }
    // draw the final results
    print_data(arr, len, -10, 0, 1);
    printf(COLOR_GREEN);
    printf("\n DONE! \n");
    printf(COLOR_RESET);
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

/*
 * Print out all the elements in the array
 */
void print_data(int arr[], int len, int active, int done, int pauses)
{
    // clear line
    //printf("\r");
    //fflush(stdout);
    
    // loop one higher than normal, to add ) after last
    for (int i = 0; i <= len; i++)
    {
        int relative_pos = i - active;
        printf(COLOR_GREEN);
        switch (relative_pos)
        {
            // highlight the current values being compared
            case 0:
                printf(COLOR_CYAN);
                printf("(");
                printf(COLOR_YELLOW);
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
            default:
                printf(" ");
                break;
        }
        printf(COLOR_RESET);
        // leave off the last number
        if (i < len)
        {
            // green for values guaranteed done
            if (i >= len - done)
            {
                printf(COLOR_GREEN);
            }
            // actually print the current value
            printf("%i", arr[i]);
            printf(COLOR_RESET);
        }
    }
    printf("\n");
    delay(PAUSE_DUR * pauses);
}
