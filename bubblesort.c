#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <time.h>

// prototypes
void fill_array(int arr[], int len);
void sort_array(int arr[], int len);
void print_data(int arr[], int len, int active, int done);
void delay_1_sec();

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
    int data_len = atoi(argv[1]);
    int data[data_len]; 
    
    // only accepts one argument, a positive int
    if (argc != 2 || data_len < 1)
    {   
        printf(COLOR_RED);
        printf("Usage: ./bubblesort <array length int>\n");
        printf(COLOR_RESET);
        // failure
        return 1;
    }
    
    fill_array(data, data_len);
    sort_array(data, data_len);
    
    // success
    return 0;
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
}

/*
 * Delay for one second
 */
void delay_1_sec()
{
    // delay test
    int wake = time(0) + 1;
    while (time(0) < wake)
    {
    }
}

/*
 * Sort the array
 */
void sort_array(int arr[], int len)
{   
    delay_1_sec();
    print_data(arr, len, -10, 0);
    printf(COLOR_GREEN);
    printf(" START! \n");
    printf(COLOR_RESET);
    delay_1_sec();
    printf("\n");
    
    // optimize loop to get smaller each time
    for (int i = len - 1; i >= 0; i--)
    {      
        // compare each pair
        for (int j = 0; j < i; j++)
        {
            string status = "";
            delay_1_sec(); 
            int confirmed = len - 1 - i;
            print_data(arr, len, j, confirmed);
            // compare each number and swap if neccesary
            if (arr[j + 1] < arr[j])
            {
                status = " SWAP!";
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            printf(COLOR_RED);
            printf("%s \n", status);
            printf(COLOR_RESET);
        }
        if (i > 0)
        {
            delay_1_sec();
            printf("\n");
        }  
    }
    delay_1_sec();
    print_data(arr, len, -10, len);
    printf(COLOR_GREEN);
    printf(" DONE! \n");
    printf(COLOR_RESET);
    delay_1_sec();
}
