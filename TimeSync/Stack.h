#ifndef STACK_H
#define STACK_H
#include <stdlib.h>

template <typename T> 
class Stack{
    private:
        int resizeSize = 4;
        volatile T * stack;
        volatile int capacity;
        void resize(int);
        volatile int length;
        int initial;
    public:
        Stack(int capacity = 1);
        ~Stack();
        void add(T);
        T get(int);
        T remove(int);
        int size();

};

#endif

template <typename T> 
Stack<T>::Stack(int capacity){
    this->length = 0;
    this->capacity = capacity;
    this->stack = (T*) malloc(sizeof(T) * this->capacity);
    this->initial = capacity;
}

template <typename T> 
Stack<T>::~Stack(){
    for(int i = 0; i < this->length; i++){
        delete this->stack[i];
    }
    delete this->stack;
}

template <typename T> 
void Stack<T>::resize(int size){
    T temp[size];
    
    for(int i = 0; i < this->length; i++){
        temp[i] = this->stack[i];
    }
    
    delete this->stack;
    
    this->stack = (T*) malloc(sizeof(T) * size);

    for(int i = 0; i < this->length; i++){
        this->stack[i] = temp[i];
    }
    
    this->capacity = size;
}

template <typename T> 
void Stack<T>::add(T node){
    if(this->length + 1 > this->capacity){
        this->resize(this->length + this->resizeSize);
    }
    this->stack[this->length] = node;
    this->length++;
}

template <typename T> 
T Stack<T>::remove(int index){
    if(index < 0 || index >= length)
        return NULL;
    T item = this->stack[index];
    for(int i = index; i < this->length - 1; i++){
        this->stack[i] = this->stack[i + 1];
    }
    this->stack[this->length] = NULL;
    this->length--;
    if(this->capacity - this->resizeSize > this->length && this->capacity - this->resizeSize > this->initial){
        this->resize(this->capacity - this->resizeSize);
    }
    return item;
}

template <typename T> 
T Stack<T>::get(int index){
    if(index < 0 || index >= length)
        return NULL;
    return this->stack[index];
}

template <typename T> 
int Stack<T>::size(){
    return this->length;
}