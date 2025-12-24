#include "dArray.h"

void da_init(DynamicArray *arr, size_t element_size) {
    arr->element_size = element_size;
    arr->size = 0;
    arr->capacity = 4; // initial capacity
    arr->data = malloc(arr->capacity * element_size);

    if (!arr->data) {
        printf("Memory allocation failed\n");
        exit(1);
    }
}

void da_resize(DynamicArray *arr, size_t new_capacity) {
    void *new_data = realloc(arr->data, new_capacity * arr->element_size);
    if (!new_data) {
        printf("Memory reallocation failed\n");
        exit(1);
    }
    arr->data = new_data;
    arr->capacity = new_capacity;
}

void da_push(DynamicArray *arr, void *element) {
    if (arr->size == arr->capacity) {
        da_resize(arr, arr->capacity * 2);
    }

    memcpy(
        (char *)arr->data + arr->size * arr->element_size,
        element,
        arr->element_size
    );

    arr->size++;
}

void *da_get(DynamicArray *arr, size_t index) {
    if (index >= arr->size) {
        printf("Index out of bounds\n");
        exit(1);
    }
    return (char *)arr->data + index * arr->element_size;
}

void da_pop(DynamicArray *arr) {
    if (arr->size == 0) return;
    arr->size--;

    if (arr->size > 0 && arr->size <= arr->capacity / 4) {
        da_resize(arr, arr->capacity / 2);
    }
}

void da_free(DynamicArray *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}
