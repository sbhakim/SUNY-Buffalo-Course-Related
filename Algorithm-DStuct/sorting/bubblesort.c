#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#define LENGTH 10

uint8_t numbers[LENGTH];
uint8_t *num_ptr[LENGTH];
void swap (uint8_t** pointer1, uint8_t** pointer2);
void bsort();
void init();

void init(){
    srand(time(NULL));
    printf ("Numbers: \n");
    for (size_t i = 0; i < LENGTH; i++){
        numbers[i] = rand()%256;
        num_ptr[i] = &numbers[i];
        printf ("%hhu   ", *num_ptr[i]);
    }
    printf ("\n");
}

 void bsort(){
        for (size_t i=0; i<LENGTH; i++){
            for (size_t j=0; j<LENGTH-1; j++){
                if(*num_ptr[j] > *num_ptr[j+1]){
                    swap(&num_ptr[j], &num_ptr[j+1]);
                }
            }
        }
}

void printArray(){
    printf("The sorted array is: \n");
    for (size_t i =0; i < LENGTH; i++){
        printf ("%hhu   ", *num_ptr[i]);
    }
    printf ("\n");
}


void swap (uint8_t** pointer1, uint8_t** pointer2){
    *pointer1 = (uintptr_t) (*pointer1)^(uintptr_t) (*pointer2);
    *pointer2 = (uintptr_t) (*pointer1)^(uintptr_t) (*pointer2);
    *pointer1 = (uintptr_t) (*pointer1)^(uintptr_t) (*pointer2);
}


int main(){
    double time_spent = 0.0;
    clock_t begin = clock();
    init();
    bsort();
    printArray();
    clock_t end= clock();
    printf("Number of clock cycles to compute : %hhu\n", end - begin);
    return 0;
}
