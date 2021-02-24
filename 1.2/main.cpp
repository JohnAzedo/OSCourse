#include <iostream>
#include "pthread.h"
#include <math.h>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

//x0 = 0 and x = 2pi
float f2(float x){
    return sin(2*x) + cos(5*x);
}

// x0 = 0 and x = 10
float f1(float x){
    return 5.0;
}

void split_in_box(int num_trapezoids, int num_threads, int * array){
    int index = 0;
    for(int i=0; i<num_trapezoids; i++){
        if(index==num_threads){
            index = 0;
        }
        array[index] += 1;
        index++;
    }
}

float sum = 0;

struct Arguments {
    int id;
    int tpt;
    float a;
    float b;
    pid_t process;
};


void * in_thread(void* arguments){
    auto *args = (Arguments *) arguments;
    fprintf(stdout, "Rum thread %i in process %i\n", args->id, getpid());


    float h, a, b;
    h = (args->b - args->a)/(float) args->tpt;
    a = args->a; b = h;

    for(int i=0; i<args->tpt; i++){
        if(args->process > 0){
            sum += (h/2)*(f1(a)+f1(b));
        }

        if(args->process == 0){
            sum += (h/2)*(f2(a)+f2(b));
        }
        a = b;
        b += h;
    }

    pthread_exit(nullptr);
}


int main(int argc, char *argv[]) {
    float x, x0;
    const int NTHREADS = atoi(argv[1]);
    const int NTRAPEZOIDS = atoi(argv[2]);

    pid_t pid = fork();
    pthread_t threads[NTHREADS];
    void* thread_return;
    int status;

    // Func 1
    if(pid>0){
        x = 10; x0 = 0;
    }

    // Func 2
    if(pid == 0){
        x = 2*M_PI; x0 = 0;
    }

    float unit = (x-x0)/NTRAPEZOIDS;
    vector<int> tpt(NTHREADS, 0);
    split_in_box(NTRAPEZOIDS, NTHREADS, tpt.data());

    Arguments args{
            0,0,0,0, pid
    };

    vector<Arguments> args_array(NTHREADS);
    for(int i=0; i<NTHREADS; i++){
        args.id = i;
        args.tpt = tpt[i];
        args.b += unit*tpt[i];
        args_array[i] = args;
        args.a = args.b;
    }

    for(int i=0; i<NTHREADS; i++){
        status = pthread_create(&threads[i], nullptr, in_thread, (void*) &args_array[i]);

        if(status!=0){
            fprintf(stdout, "Error");
            return 1;
        }
    }

    for(int i=0; i<NTHREADS; i++){
        pthread_join(threads[i], &thread_return);
    }

    if(pid>0){
        fprintf(stdout, "Func1 area: %.2f\n", sum);
    }else{
        fprintf(stdout, "Func2 area: %.2f\n", sum);
    }
    return 0;
}
