# Array List
**Array List** (a. k. a. dynamic array or "array_list") is a random-accessed, variable sized data structure. It allows elements to be added,removed, or accessed at any place within the data structure.

It's represented by the following C `struct`:

```c
typedef struct ArrayList
{
    unsigned int size;
    unsigned int capacity;
    unsigned int element_size;
    void *data;

} array_list;
```

## Create
To create new array list `a` with initial capacity `capacity` and size of  `element_size` bytes, use

```c
array_list *a = array_list_create(capacity, element_size)
```

## Adding elements
### Prepend
To insert an element at address `el` to the front of the array list `a`, use
```c
array_list_prepend(a, el);
```
This prepends element while pushing all the existing elements one position higher. This puts this operation in **O(n)**.

### Append
To append element at the end of the array list, use
```c
array_list_append(a, el_address);
```
Appending element can be costly when there is not enough space allocated for the array list. In such case we need to allocate new memory of size `array_list.size * STRETCH_FACTOR` and copy the original array into the new allocated memory in **O(n)**. However, until the memory is full again, we are appending in a constant time. That way we're "amortize" time for the next array copy, thus, for the series of *append* operations we get [amortized](https://en.wikipedia.org/wiki/Amortized_analysis) complexity of **O(1)**.

### Insert
To insert element at index `i` within the array list, use
```c
array_list_insert(a, el_address, i);
```
The the original element at this index is moved one position up as well as all the following elemnts. Worst case scenario for this operation is equivalent to *prepend* operation as all *n* current elements need to be pushed up, rendering this operation to be in **O(n)**.

**NOTE:** Prefering *append* operation on the array list data structure to add elements whenever possible is recomended.

## Retrieving elements
Getting an element at index `i` can be done by the following line of code:
```c
void *el = array_list_at(a, i);
```
This returns a pointer to the memory containing a copy od the element at the given index. This is done in constant time (**O(1)**) as we are able to access the memory location containg the requested element directly via it's index at the array list.

## Update array list
To change what's stored under an index `i` in the array list, use
```c
array_list_set(a, el, i);
```
This replaces the current element with the new one in a constant time, as, again, we can access memory location to put the data to in **O(n)**.

## Removing elements
To remove an element at index `i` from the list, use
```c
array_list_remove(a, i);
```
This removes the element from the array and pushes the following elements down by 1 position. Similarly to the *prepend* operation, this will happen in *O(n)*.

## Cleanup
When finished using the array list `a`, make sure to free the memory containing the `array_list.data` as well as the rest of the `array_list` structure:
```c
array_list_destroy(a);
```
