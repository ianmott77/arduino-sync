#ifndef OPERATION_H
#define OPERATION_H

#include <Arduino.h>

class Operation{
    public:
        virtual void init() = 0;
        virtual void exec() = 0;
        int id = 0;
};

#endif