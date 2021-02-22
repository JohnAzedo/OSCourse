#include <iostream>
#include "pthread.h"
#include <math.h>
#define PI 3.14159265358979323846

// Temp vars
#define NTHREADS 6
#define NTRAPEZOIDS 120

float area_trapezoid(float B, float b, float h){
    return (h/2)*(B+b);
}

//x0 = 0 and x = 2pi
float f2(float x){
    return sin(2*x) + cos(5*x);
}

// x0 = 0 and x = 10
float f1(float x){
    return 5.0;
}

float calc(int trapezoids_per_thread, float x, float x0){
    float h, sum, B, b;
    h = (x-x0)/(float)trapezoids_per_thread; sum = 0; B = x0; b = h;

    for(int j=0; j<trapezoids_per_thread; j++){
        sum += (h/2)*(f1(B)+f1(b));
        b = B;
        B += h;
    }
    return sum;
}

int main() {
    pthread_t threads[NTHREADS];
    void* return_thread;

    int trapezoids_per_thread = floor(NTRAPEZOIDS/NTHREADS);
    int x = ceil(10/6);

    fprintf(stdout, "Test: %i", x);

    for(int i=0; i<NTHREADS; i++){

    }

    return 0;
}
