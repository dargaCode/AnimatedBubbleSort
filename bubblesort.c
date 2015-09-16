#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <time.h>

// prototypes
bool validate(int argc, string argv[]);
void fill_array(int arr[], int len);
void sort_array(int arr[], int len);
void print_data(int arr[], int len, int active, int done);
void delay(int milliseconds);

// printf ANSI colors
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

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
    // argument must be positive int
    else if (atoi(argv[1]) < 1)
    {
        valid = false;
    }
    
    if (valid == false)
    {
        printf(COLOR_RED);
        printf("Usage: bubblesort <array length>\n");
        printf(COLOR_RESET);
    }
    return valid;
}

/*
 * Fill the array with random ints 
 */ 
void fill_array(int arr[], int len)
{
    // random seed
    srand(time(NULL));   
    
    for (int i = 0; i < len; i++)
    {
        arr[i] = rand() % (len * 4); // randomized  
        //todo change 4 to 1
        // arr[i] = len - i; // reverse order        
    }
}

/*
 * Print out all the elements in the array
 */
void print_data(int arr[], int len, int active, int done)
{
    // clear line
    printf("\r");
    fflush(stdout);
    
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
                // show the comparison
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
    //printf("\n");
}

/*
 * Delay for a given amount of milliseconds
 */
void delay(int milliseconds)
{
    clock_t start = clock();
    clock_t now = clock();
    long delay = milliseconds * (CLOCKS_PER_SEC / 1000);
        
    while (now < start + delay)
    {
        now = clock();
    }
}

/*
 * Sort the array
 */
void sort_array(int arr[], int len)
{   
    print_data(arr, len, -10, 0);    
    
    // optimize loop to get smaller each time
    for (int i = len - 1; i >0; i--)
    {      
        // items that must be correct
        int confirmed = len - 1 - i;
        
        if (i < len - 1)
        {
            print_data(arr, len, -10, confirmed);
            delay(750);    
        }  
                
        // compare each pair
        for (int j = 0; j < i; j++)
        {
            delay(500); 
            
            print_data(arr, len, j, confirmed);
            // compare each number and swap if neccesary
            if (arr[j + 1] < arr[j])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                
                // show the swapped results
                if (j < i -1)
                {
                    delay(500);
                }
                print_data(arr, len, j, confirmed);
            }
        }
        delay(500);
    }
    delay(500);
    print_data(arr, len, -10, 0);
    delay(500);
    printf(COLOR_GREEN);
    printf("DONE! \n");
    printf(COLOR_RESET);
}
