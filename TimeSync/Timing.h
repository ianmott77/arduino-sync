#ifndef TIMING_H
#define TIMING_H

#define DELAY_ARR 10

#include <Arduino.h>

#ifndef STACK_H
    #include "Stack.h"
#endif

class Timing
{
public:
    Timing(bool logging = false);
    unsigned long now();
    float delay();
    float elapsed();
    unsigned long startMils;
    unsigned long endMils;
    unsigned long adjusted;
    unsigned long first;
    long dif;
    float factor;
    bool logging;
    float avgDelay;
    unsigned long mils;
    int drift;
    Stack<int> * delays;
};

#endif