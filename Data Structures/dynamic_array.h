#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>

#define _IGNORE(x) ((void)(x))

#define _DARR_DEFINE_TYPE(type) \
    typedef struct DARR_##type {\
        int size;\
        int capacity;\
        type *values;\
        void (*add)(DARR_##type*, type);\
        void (*remove)(DARR_##type*, int);\
        void (*free)(DARR_##type*);\
    } DARR_##type;\
    
#define _DARR_DEFINE_FREE(...) _DARR_DEFINE_FREE_IMPL(__VA_ARGS__, _IGNORE)

#define _DARR_DEFINE_FREE_IMPL(type, free_function, ...) \
    void DARR_##type##_free(DARR_##type *arr) {\
        if (!arr) return;\
        for (int i = 0; i < arr->size; i++) {\
            free_function(arr->values[i]);\
        }\
        free(arr->values);\
        free(arr);\
    }\

#define _DARR_DEFINE_ADD(type) \
    void DARR_##type##_add(DARR_##type *arr, type value) {\
        if (!arr) return;\
        if (arr->capacity < arr->size + 1) {\
            type *temp = (type *) realloc(arr->values, arr->capacity * 2 * sizeof(type));\
            if (!temp) return;\
            arr->values = temp;\
            arr->capacity *= 2;\
        }\
        arr->values[arr->size] = value;\
        arr->size += 1;\
    }\

#define _DARR_DEFINE_REMOVE(...) _DARR_DEFINE_REMOVE_IMPL(__VA_ARGS__, _IGNORE)

#define _DARR_DEFINE_REMOVE_IMPL(type, free_function, ...) \
    void DARR_##type##_remove(DARR_##type *arr, int index) {\
        if (index >= arr->size) return;\
        free_function(arr->values[index]);\
        for (int i = index; i < arr->size - 1; i ++) {\
            arr->values[i] = arr->values[i + 1];\
        }\
    }\

#define DARR_DEFINE(...) _DARR_DEFINE_IMPL(__VA_ARGS__, _IGNORE)

#define _DARR_DEFINE_INIT(type) \
    DARR_##type *DARR_##type##_init(int capacity) {\
        DARR_##type *arr = (DARR_##type*) malloc(sizeof(DARR_##type));\
        arr->size = 0;\
        arr->capacity = capacity;\
        arr->values = (type*) malloc(sizeof(type) * capacity);\
        arr->add = DARR_##type##_add;\
        arr->free = DARR_##type##_free;\
        arr->remove = DARR_##type##_remove;\
        return arr;\
    }\

#define _DARR_DEFINE_IMPL(type, free_function, ...) \
    _DARR_DEFINE_TYPE(type)\
    _DARR_DEFINE_INIT(type)\
    _DARR_DEFINE_FREE(type, free_function)\
    _DARR_DEFINE_ADD(type)\
    _DARR_DEFINE_REMOVE(type, free_function)\

#endif