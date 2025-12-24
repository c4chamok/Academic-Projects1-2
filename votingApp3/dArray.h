#ifndef DARRAY_H
#define DARRAY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void *data;
    size_t element_size;
    size_t size;
    size_t capacity;
} DynamicArray;

void da_init(DynamicArray *arr, size_t element_size) ;

void da_resize(DynamicArray *arr, size_t new_capacity) ;

void da_push(DynamicArray *arr, void *element) ;

void *da_get(DynamicArray *arr, size_t index) ;

void da_pop(DynamicArray *arr) ;
void da_free(DynamicArray *arr);


#endif



