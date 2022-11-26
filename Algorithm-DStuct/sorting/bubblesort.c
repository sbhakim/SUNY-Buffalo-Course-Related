#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH  20

uint8_t fNumbers[LENGTH];
uint8_t *fNumRefs[LENGTH];

void init(){
    srand(time(NULL));
    printf("Numbers: \n");
    for (size_t i = 0; i < LENGTH; i++){
        fNumbers[i] = rand() %256;
        fNumRefs[i] = &fNumbers[i];
        printf("%hhu   ", fNumbers[i]);
    }
}

void swap(uint8_t** pointer1, uint8_t** pointer2){
    *pointer1 = (uintptr_t) (*pointer1)^(uintptr_t) (*pointer2);
    *pointer2 = (uintptr_t) (*pointer1)^(uintptr_t) (*pointer2);
    *pointer1 = (uintptr_t) (*pointer1)^(uintptr_t) (*pointer2);
}

void bsort(){
    for(size_t i = 0; i < LENGTH; i++){
        for (size_t j = 0; j < LENGTH-1 -i; j++){
            if (*fNumRefs[j] > *fNumRefs[j +1 ]){
                swap(&fNumRefs[j], &fNumRefs[j+1]);
            }
        }
    }
}


int main() {
    init();
    bsort();
    printf("\nSorted : \n");
    for (size_t i = 0; i < LENGTH; i++)
        printf("%hhu   ", *fNumRefs[i]);
    printf("\n");
    return 0;

