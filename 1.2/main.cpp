#include <iostream>
#include "pthread.h"
#include <math.h>
#include <string>
#include <vector>

#define PI 3.14159265358979323846

// Temp vars
#define NTHREADS 6
#define NTRAPEZOIDS 120

using namespace std;

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

void split_in_box(int h, int num_threads, int * array){
    int index = 0;
    for(int i=0; i<h; i++){
        if(index==6){
            index = 0;
        }
        array[index] += 1;
        index++;
    }
}

int main() {
    float x, x0; x = 10; x0 = 0;
    float sum = 0;
    float a, b = 0;

    pthread_t threads[NTHREADS];
    void* return_thread;

    int trapezoids_per_thread;
    int trapezoids_per_unit = floor(NTRAPEZOIDS/(x-x0));
    vector<int> array(NTHREADS, 0);
    split_in_box(10, NTHREADS, array.data());

    // TODO: Adapt this to pthreads
    for(int i=0; i<NTHREADS; i++){
        b += array[i];
        trapezoids_per_thread = array[i]*trapezoids_per_unit;
        sum += calc(trapezoids_per_thread, b, a);
        a = b;
    }

    fprintf(stdout, "Soma: %.2f", sum);

    return 0;
}
