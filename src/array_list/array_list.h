/**
 * @author David Kizivat <david.kizivat@gmail.com>
 *
 * Array list data structure. Created for practice purposes.
 */

#ifndef array_list_H
#define array_list_H

// Factor by which the array list will stretch when needed
#define STRETCH_FACTOR 1.5

// Factor by which the array list will shrink when needed
#define SHRINK_FACTOR 0.5

/**
 * Array list data structure. Dynamically resizing array of data.
 */
typedef struct array_list
{
    unsigned int size;
    unsigned int capacity;
    unsigned int element_size;
    void *data;

} array_list;

/**
 * Creates a new array list of given capacity.
 * @param capacity number of elements the array list will be initially able to hold
 * @param element_size size of a single element
 * @return pointer to the newly created array list, NULL if unsuccessful
 */
array_list *array_list_create(unsigned int capacity, unsigned int element_size);

/**
 * Gets a value of the element of the given array list at the specified index.
 * @param v pointer to the array list
 * @param i index of the element to return
 * @return pointer to the element at the index i, NULL if operation unseccessful
 */
void *array_list_at(array_list *v, unsigned int i);

/**
 * Appends an element to the end of the given array list.
 * @param v pointer to the array list to append the element to
 * @param p pointer to the element to be appended to the array list
 * @return 0 if successful
 */
int array_list_append(array_list *v, void *p);

/**
 * Prepends an element to the very beginning (index 0) of the given array list.
 * @param v pointer to the array list to prepend the element to
 * @param p pointer to the element to be prepended to the array list
 * @return 0 if successful
 */
int array_list_prepend(array_list *v, void *p);

/**
 * Inserts an element into the given array list at specific location pushing the later elements
 * to the higher positions in the array list.
 * @param v pointer to the array list to insert into
 * @param p pointer to the element to be inserted into the array list
 * @param i index in the array list to insert the element at
 * @return 0 if successful
 */
int array_list_insert(array_list *v, void *p, unsigned int i);

/**
 * Sets value of an element in the given array list and at the given index overriding current value.
 * @param v pointer to the array list to work on
 * @param p pointer to the memory location containing the data to be set as the new element of the array list
 * @param i index in the array list to set to the given value
 * @return 0 if successful
 */
int array_list_set(array_list *v, void *p, unsigned int i);

/**
 * Removes an element at the given index from the given array list, decreasing all the following
 * elements' ideces by 1.
 * @param v pointer to the array list to remove from
 * @param i index of the the element to remove
 * @return number of removed elements, -1 if an error occured
 */
int array_list_remove(array_list *v, unsigned int i);

/**
 * Frees up all the memory used by the given array list.
 * @param v pointer to the array list to be destroyed
 * @return 0 if successfull
 */
int array_list_destroy(array_list *v);

#endif //array_list_H
