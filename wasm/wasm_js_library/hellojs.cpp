#include<iostream>

extern "C" {
    extern void print_numbers(float a, float b, float c);
}

int main(){
    print_numbers(5, 3, 1);
    return 0;
}