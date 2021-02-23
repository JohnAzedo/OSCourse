#include <iostream>
#include "pthread.h"
#include <math.h>
#include <string>
#include <vector>
#include <unistd.h>

#define PI 3.14159265358979323846

// Temp vars
#define NTHREADS 7
#define NTRAPEZOIDS 200

using namespace std;

//x0 = 0 and x = 2pi
float f2(float x){
    return sin(2*x) + cos(5*x);
}

// x0 = 0 and x = 10
float f1(float x){
    return 5.0;
}

void split_in_box(int h, int num_threads, int * array){
    int index = 0;
    for(int i=0; i<h; i++){
        if(index==num_threads){
            index = 0;
        }
        array[index] += 1;
        index++;
    }
}

float f1_sum = 0;
float f2_sum = 0;

struct Arguments {
    int id;
    // Trapezoids per thread
    int tpt;
    float a;
    float b;
};


void * f1_in_thread(void* arguments){
    auto *args = (Arguments *) arguments;

    float h, a, b;
    h = (args->b - args->a)/(float) args->tpt;
    a = args->a; b = h;

    for(int i=0; i<args->tpt; i++){
        f1_sum += (h/2)*(f1(a)+f1(b));
        a = b;
        b += h;
    }

    pthread_exit(nullptr);
}


int main() {
    float x, x0; x = 10; x0 = 0;

    pthread_t threads[NTHREADS];
    void* thread_return;
    int status;

    int trapezoids_per_unit = floor(NTRAPEZOIDS/(x-x0));
    vector<int> array(NTHREADS, 0);
    split_in_box(10, NTHREADS, array.data());

    Arguments args{
            0,0,0,0
    };

    vector<Arguments> args_array(NTHREADS);
    for(int i=0; i<NTHREADS; i++){
        args.id = i;
        args.tpt = array[i]*trapezoids_per_unit;
        args.b += array[i];
        args_array[i] = args;
        args.a = args.b;
    }

    for(int i=0; i<NTHREADS; i++){
        status = pthread_create(&threads[i], nullptr, f1_in_thread, (void*) &args_array[i]);

        if(status!=0){
            fprintf(stdout, "Error");
            return status;
        }

    }

    for(int i=0; i<NTHREADS; i++){
        pthread_join(threads[i], &thread_return);
        fprintf(stdout,"Finish thread %i\n", i);
    }

    fprintf(stdout, "Soma: %.2f", f1_sum);

    return 0;
}
