/**
 * @file vector.h
 * @brief api for using the vector struct.
 * @author Nathan Orwick
 * @date July 30, 2023
 */
#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>

/**
 * @brief struct vector - dynamic-sizing array-type container.
 * 
 * This is a lightweight vector implementation that will grow
 * as needed. It is implemented to store pointers.
 */
struct vector;

/**
 * @brief vec_new() - allocate a new vector.
 * 
 * A new vector should be instantiated through this function.
 * There is no init function to pass a vector into. This will
 * return NULL on failure.
 * 
 * @return struct vector *.
 */
struct vector *vec_new(void);

/**
 * @brief vew_free() - free a vector *.
 * 
 * This will free the memory being used for the vector
 * container. Beware that the pointer will not be set to NULL.
 * 
 * @param v struct vector *.
 */
void vec_free(struct vector *v);

/**
 * @brief vew_push_back() - append a value to the vector.
 * 
 * This will append a pointer to the end of the vector &
 * take care of any necessary resizing.
 * 
 * @param v struct vector *.
 * @param value void *.
 * @return bool success status.
 */
bool vec_push_back(struct vector *v, void *value);

/**
 * @brief vec_length() - get the length of the vector.
 * 
 * @param v struct vector *.
 * @return int length.
 */
int vec_length(const struct vector *v);

/**
 * @brief vec_at() - access the specified index of the vector.
 * 
 * If the index exists, the associated pointer will be returned
 * (cast the result if necessary). If the index doesn't exist,
 * NULL will be returned & an error message will be directed to
 * stderr.
 * 
 * @param v struct vector *.
 * @param index int.
 * @return entry pointer or NULL.
 */
void *vec_at(const struct vector *v, const int index);

/**
 * @brief vec_empty() - check if the vector is empty.
 * 
 * @param v struct vector *.
 * @return bool empty status.
 */
bool vec_empty(const struct vector *v);

/**
 * @brief vec_clear() - clear the values in the vector.
 * 
 * @param v struct vector *.
 * @return bool sucess status.
 */
bool vec_clear(struct vector *v);

#endif
