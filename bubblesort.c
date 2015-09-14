#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <time.h>

// prototypes
void fill_array(int arr[], int len);
void sort_array(int arr[], int len);
void print_array(int arr[], int len);
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
        // arr[i] = len - i; // reverse order        
    }
}

/*
 * Print out all the elements in the array
 */
void print_array(int arr[], int len)
{
    printf("[");
    for (int i = 0; i < len; i++)
    {
        printf("%i", arr[i]);
        if (i < len - 1)
        {
            printf(",");
        }
    }
    printf("]");
}

/*
 * Delay for one second
 */
void delay_1_sec()
{
    // delay test
    int wake = time(0) + 0;
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
    print_array(arr, len);
    printf("\n\n");
    
    // optimize loop to get smaller each time
    for (int i = len - 1; i >= 0; i--)
    {        
        // compare each pair
        for (int j = 0; j < i; j++)
        {
            //printf("compare [%i] and [%i] \n", j, j + 1);
            string status = "";
            delay_1_sec(); 
            // compare each number and swap if neccesary
            if (arr[j + 1] < arr[j])
            {
                status = " - swap!";
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            print_array(arr, len);
            printf("%s \n", status);
        }
    }
    delay_1_sec();
    printf("DONE! \n");
    delay_1_sec();
}
