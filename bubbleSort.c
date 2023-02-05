#include "bubbleSort.h"


void bubble_sort(float arr[], int n) {
    
    int i = 0;
    while(i < n) {
        for (int j = 0; j < n; j++) {
            if (keycomp(arr[j+1], arr[j])) {
                swap(arr[j+1], arr[j]);
            }
        }
        i++;
    }       
}

int count_assign;
int count_comp;

// The function below assigns the value at the address `b` to the storage with address `a`
void keyassign(float *a, float *b) {
    
    // We are using pointers here to change the values at the memory locations
    count_assign++;
    *a = *b;        // value at a = value at b
    return;
}

// The function below compares two floats, and returns true if and only if a <= b
bool keycomp(float a, float b) {
    
    count_comp++;
    if (a < b || a == b) {
        return true;
    }
    
    return false;
}

void swap(float a, float b) {
    float temp;
    keyassign(&temp, &a);
    keyassign(&a, &b);
    keyassign(&b, &temp);
    return;
}