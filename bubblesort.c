#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <time.h>

// prototypes
void randomize_array(int arr[], int len);
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
    
    randomize_array(data, data_len);
    print_array(data, data_len);
    sort_array(data, data_len);
    
    // success
    return 0;
}

/*
 * Fill the array with random ints 
 */ 
void randomize_array(int arr[], int len)
{
    // random seed
    srand(time(NULL));   
    
    for (int i = 0; i < len; i++)
    {
        arr[i] = rand() % len;        
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
    printf("]\n");
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
    printf("sort array! \n");
    
    int loop_max = len;
    
    // optimize loop to get smaller each time
    for (int i = loop_max; i > 0; i--)
    {
        delay_1_sec();
        printf("sort from 0 to %i \n", i);
        // compare each pair
        for (int j = 0; j < i; j++)
        {
            delay_1_sec();
            printf("    compare [%i] and [%i] \n", j, j + 1); 


            
           
        }
    }
}
