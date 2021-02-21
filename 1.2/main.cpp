#include <iostream>
#include <math.h>
#define PI 3.14159265358979323846

// First function -> f(x) = 5, x0 = 0 and x = 10
// Second function -> f(x) = sin(2x) + cos(5x), x0 = 0 and x = 2pi


float area_trapezoid(float B, float b, float h){
    return (h/2)*(B+b);
}

float f1(float x){
    return 5.0;
}

float f2(float x){
    return sin(2*x) + cos(5*x);
}

int main() {
    int amount_threads = 6;
    int number_trapezoids = 120;

    // First Function
    float x0 = 0.0;
    float x = 10.0;
    float h = x - x0;
    float B = f1(x);
    float b = f1(x0);
    float result = area_trapezoid(B, b, h);
    fprintf(stdout, "%.2f\n", result);


    // Second function
    x = 2*PI;
    h = (x-x0)/20;
    float sum = 0;

    float temp_x = h;
    for(int i=1; i<=20; i++){
        B = f2(temp_x);
        b = f2(x0);
        sum += area_trapezoid(B, b, h);
        x0 = temp_x;
        temp_x += h;
    }
    fprintf(stdout, "%.2f\n", sum);

    return 0;
}
