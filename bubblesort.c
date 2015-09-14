#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <time.h>

// prototypes
void fill_array(int arr[], int len);
void sort_array(int arr[], int len);
void print_data(int arr[], int len, int active);
void delay_1_sec();

int main(int argc, string argv[])
{   
    int data_len = atoi(argv[1]);
    int data[data_len]; 
    
    // only accepts one argument, a positive int
    if (argc != 2 || data_len < 1)
    {
        printf("Usage: bubblesort <array length int>\n");
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
void print_data(int arr[], int len, int active)
{
    // loop one higher than normal, to add ) after last
    for (int i = 0; i <= len; i++)
    {
        int relative_pos = i - active;
        switch (relative_pos)
        {
            case 0:
                printf("(");
                break;
            case 1:
                // show the comparison
                if (arr[active] < arr[active + 1])
                {
                    printf("<");
                }
                else if (arr[active] > arr[active + 1])
                {
                    printf(">");
                }
                else
                {
                    printf("=");
                }
                break;
            case 2:
                printf(")");
                break;
            default:
                printf(" ");
                break;
        }
        // leave off the last number
        if (i < len)
        {
            printf("%i", arr[i]);
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
    print_data(arr, len, -10);
    printf("- START! \n");
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
            print_data(arr, len, j);
            // compare each number and swap if neccesary
            if (arr[j + 1] < arr[j])
            {
                status = "- SWAP!";
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }

            printf("%s \n", status);
        }
        if (i > 0)
        {
            delay_1_sec();
            printf("\n");
        }  
    }
    delay_1_sec();
    print_data(arr, len, -10);
    printf("- DONE! \n");
    delay_1_sec();
}
