#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "array_list.h"

#define ALLOC_ERROR "Unsuccessful memory allocation:"

/* Helper functions declarations */
static int check_allocation(void *p, array_list *working_array_list, char *message);
static int update_capacity(array_list *v, float change_factor);
static int resize_for_size(array_list *v, unsigned int size);
static int check_index(array_list *v, unsigned int i, bool stretching);
static int swap(array_list *v, unsigned int i, unsigned int j, bool stretching);

/* Header implementation */
array_list *array_list_create(unsigned int capacity, unsigned int element_size)
{
    array_list *v = malloc(sizeof(array_list));
    if (check_allocation(v, v, "Failed to allocate memory for the array_list structure.")) 
    {
        free(v);
        return NULL;
    }

    v->size = 0;
    v->capacity = capacity;
    v->element_size = element_size;
    v->data = calloc((size_t)capacity, (size_t)element_size);
    if (check_allocation(v->data, v, "Failed to allocate memory for the array_list's data."))
    {
        array_list_destroy(v);
        return NULL;
    }

    return v;
}

void *array_list_at(array_list *v, unsigned int i)
{
    if (check_index(v, i, false)) 
    {
        return NULL;
    }
    void *ret = v->data + (v->size * (v->element_size - 1));
    memcpy(ret, (v->data + (i * v->element_size)), v->element_size);
    return ret;
}

int array_list_append(array_list *v, void *p)
{
    return array_list_insert(v, p, (int)v->size);
}

int array_list_prepend(array_list *v, void *p)
{
    return array_list_insert(v, p, 0);
}

int array_list_insert(array_list *v, void *p, unsigned int i)
{
    if (check_index(v, i, true)) {
        return -1;
    }

    unsigned int new_size = (v->size + 1);
    resize_for_size(v, new_size);
    for (int j = v->size - 1; j >= (int)i; --j)
    {      
        swap(v, j, j + 1, true);
    }

    memcpy((v->data + (i * v->element_size)), // new index to copy data to (destination)
           p,                                 // element (source)
           v->element_size);                  // element size

    v->size = new_size;
    return 0;
}

int array_list_set(array_list *v, void *p, unsigned int i) 
{
    if(check_index(v, i, false))
    {
        return -1;
    }
    memcpy((v->data + (i * v->element_size)),
           p,
           v->element_size);
    return 0;
}

int array_list_remove(array_list *v, unsigned int i) {
    if (check_index(v, i, false)) 
    {
        return -1;
    }

    for (int j = i; j < (int)(v->size) - 1; j++) 
    {
        if (swap(v, j + 1, j, false)) 
        {
            return -1;
        }
    }
    unsigned int new_size = (v->size - 1);
    resize_for_size(v, new_size);
    v->size = new_size;
    return 1;
}

int array_list_destroy(array_list *v)
{
    free(v->data);
    free(v);
    return 0;
}

/* Helper functions definitions */

// Checks whether the given pointer p points to a correctly allocated memory address.
// If not, prints the given message to the standard error output.
static int check_allocation(void *p, array_list *working_array_list, char *message)
{
    if (p == NULL)
    {
        fprintf(stderr, "%s: %s\n", ALLOC_ERROR, message);
        array_list_destroy(working_array_list);
        return -1;
    }
    return 0;
}

// Resize given array_list for desired size
static int resize_for_size(array_list *v, unsigned int size)
{
    if (size > v->capacity)
    { // if desired size is greater than current capacity
        update_capacity(v, STRETCH_FACTOR);
    }
    else if (size < v->size && v->size < ((v->capacity / SHRINK_FACTOR) + 1))
    { // will we be OK after shrink?
        update_capacity(v, SHRINK_FACTOR);
    } // else - no need to do anything
    return 0;
}

// Updates capacity of the given array list by a change factor
static int update_capacity(array_list *v, float change_factor)
{
    size_t new_capacity = (size_t)((v->capacity * change_factor) + 1); // using size_t instead of unsigned int to prevent warning in realloc
    void *new_data = realloc(v->data, (size_t)(new_capacity * v->element_size));
    
    if (check_allocation(new_data, v, "Failed to reallocate memory for data when resizing array_list.")) 
    {
        return -1;
    }

    v->data = new_data;
    v->capacity = (unsigned int)new_capacity;

    return 0;
}

// Checks whether the given index is valid index within the array list.
static int check_index(array_list *v, unsigned int i, bool stretching)
{
    if (i > v->size || (!stretching && i == v->size )) 
    {
        fprintf(stderr,
                "Index %u is out of range of the current array list size for the attempted operation. Current array_list size is: %u\n",
                i, v->size);
        return -1;
    }
    return 0;
}

// Swaps positions of elements at the given indeces.
static int swap(array_list *v, unsigned int i, unsigned int j, bool stretching) 
{
    if (check_index(v, i, stretching) != 0 || check_index(v, j, stretching) != 0)
    {
        return -1;
    }

    void *j_placeholder = v->data + (j * v->element_size);

    // copy i to j
    memcpy((v->data + (j * v->element_size)),
           (v->data + (i * v->element_size)),
           v->element_size);
    // place j to i
    memcpy((v->data + (i * v->element_size)),
            j_placeholder,
            v->element_size);

    return 0;
}
