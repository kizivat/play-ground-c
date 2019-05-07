#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "array_list_tests.h"
#include "array_list.h"

void run_all_tests()
{
    test_create_basic();
    test_create_large();
    test_create_complex();

    test_append_empty();
    test_append_non_empty();
    test_append_large();

    test_prepend_empty();
    test_prepend_non_empty();
    test_prepend_large();

    test_insert_empty_i0();
    test_insert_empty_i1();
    test_insert_i0();
    test_insert_mid();
    test_insert_iN();
    test_insert_large();
    test_insert_igtN();
    test_insert_complex();
    
    test_set_empty();
    test_set_first();
    test_set_mid();
    test_set_last();
    test_set_out_of_range();
    test_set_complex();

    test_remove_first();
    test_remove_last();
    test_remove_middle();
    test_remove_empty();
    test_remove_out_of_range();
    test_remove_large();

    printf("All array_list tests passed.\n");
}

/* Create tests */
void test_create_basic()
{
    array_list *v = array_list_create(1, sizeof(int));
    assert(v != NULL);
    assert(v->size == 0);
    assert(v->capacity == 1);
    array_list_destroy(v);
}

void test_create_large()
{
    unsigned int large_int = 10000;
    array_list *v = array_list_create(large_int, sizeof(int));
    assert(v != NULL);
    assert(v->size == 0);
    assert(v->capacity == large_int);
    array_list_destroy(v);
}

void test_create_complex()
{
    array_list *v = array_list_create(3, sizeof(char[8]));
    assert(v != NULL);
    assert(v->size == 0);
    assert(v->capacity == 3);
    array_list_destroy(v);
}

/* Append tests */
void test_append_empty()
{
    array_list *v = array_list_create(0, sizeof(int));
    int x = 123;
    assert(array_list_append(v, &x) == 0);
    assert(v->size == 1);
    assert(*(int*)array_list_at(v, 0) == 123);
}

void test_append_non_empty()
{
    array_list *v = array_list_create(1, sizeof(int));
    int a = 0, b = 1;
    array_list_insert(v, &a, 0);
    assert(array_list_append(v, &b) == 0);
    assert(v->size == 2);
    assert(*(int*)array_list_at(v, 1) == 1);
}

void test_append_large()
{
    array_list *v = array_list_create(1000, sizeof(int));
    for (int i = 0; i < v->capacity; i++) {
        array_list_append(v, &i);
    }
    int x = 1234;
    assert(array_list_append(v, &x) == 0);
    assert(v->size == 1001);
    assert(*(int*)array_list_at(v, v->size - 1) == 1234);
}

/* Prepend tests */
void test_prepend_empty()
{
    array_list *v = array_list_create(0, sizeof(int));
    int x = 123;
    assert(array_list_prepend(v, &x) == 0);
    assert(v->size == 1);
    assert(*(int*)array_list_at(v, 0) == 123);
}

void test_prepend_non_empty()
{
    array_list *v = array_list_create(1, sizeof(int));
    int a = 0, b = 1;
    array_list_insert(v, &a, 0);
    assert(array_list_prepend(v, &b) == 0);
    assert(v->size == 2);
    assert(*(int*)array_list_at(v, 0) == 1);
}

void test_prepend_large()
{
    array_list *v = array_list_create(1000, sizeof(int));
    for (int i = 0; i < v->capacity; i++) {
        array_list_append(v, &i);
    }
    int x = -1;
    assert(array_list_prepend(v, &x) == 0);
    assert(v->size == 1001);
    assert(*(int*)array_list_at(v, 0) == -1);
    assert(*(int*)array_list_at(v, v->size - 1) == 999);
}

/* Insert tests */
void test_insert_empty_i0()
{
    array_list *v = array_list_create(0, sizeof(int));
    int x = 123;
    assert(array_list_insert(v, &x, 0) == 0);
    assert(v->size == 1);
    assert(*(int*)array_list_at(v, 0) == 123);
}

void test_insert_empty_i1()
{
    array_list *v = array_list_create(0, sizeof(int));
    int x = 123;
    assert(array_list_insert(v, &x, 1) == -1);
}

void test_insert_i0()
{
    array_list *v = array_list_create(0, sizeof(int));
    int a = 0, b = 1;
    array_list_append(v, &b);
    assert(array_list_insert(v, &a, 0) == 0);
    assert(v->size == 2);
    assert(*(int*)array_list_at(v, 0) == 0);
}

void test_insert_mid()
{
    array_list *v = array_list_create(0, sizeof(int));
    int a = 0, b = 1, c = 2;
    array_list_append(v, &a);
    array_list_append(v, &c);
    assert(array_list_insert(v, &b, 1) == 0);
    assert(v->size == 3);
    assert(*(int*)array_list_at(v, 1) == 1);
}

void test_insert_iN()
{
    array_list *v = array_list_create(0, sizeof(int));
    int a = 0, b = 1, c = 2;
    array_list_append(v, &a);
    array_list_append(v, &b);
    assert(array_list_insert(v, &c, 2) == 0);
    assert(v->size == 3);
    assert(*(int*)array_list_at(v, 2) == 2);
}

void test_insert_large()
{
    array_list *v = array_list_create(1000, sizeof(int));
    for (int i = 0; i < v->capacity; i++) {
        array_list_append(v, &i);
    }
    int x = -1;
    assert(array_list_insert(v, &x, 500) == 0);
    assert(v->size == 1001);
    assert(*(int*)array_list_at(v, 0) == 0);
    assert(*(int*)array_list_at(v, v->size - 1) == 999);
    assert(*(int*)array_list_at(v, 500) == -1);
}

void test_insert_igtN()
{
    array_list *v = array_list_create(0, sizeof(int));
    int a = 0, b = 1;
    array_list_append(v, &a);
    assert(array_list_insert(v, &b, 2) == -1);
}

void test_insert_complex()
{
    array_list *v = array_list_create(3, sizeof(char[3]));
    char *a = "123", *b = "456", *c = "789";
    array_list_append(v, a);
    array_list_append(v, c);
    assert(array_list_insert(v, b, 1) == 0);
    assert(strcmp((char*)array_list_at(v, 1), "456") == 0);
}

/* Set tests */
void test_set_empty()
{
    array_list *v = array_list_create(0, sizeof(int));
    int x = 0;
    assert(array_list_set(v, &x, 0) == -1);
}
void test_set_first()
{
    array_list *v = array_list_create(2, sizeof(int));
    int a = 0, b = 1;
    array_list_append(v, &a);
    array_list_append(v, &b);
    int x = -1;
    assert(array_list_set(v, &x, 0) == 0);
    assert(*(int *)array_list_at(v, 0) == -1);
}
void test_set_mid()
{
    array_list *v = array_list_create(3, sizeof(int));
    int a = 0, b = 1, c = 2;
    array_list_append(v, &a);
    array_list_append(v, &b);
    array_list_append(v, &c);
    int x = -1;
    assert(array_list_set(v, &x, 1) == 0);
    assert(*(int *)array_list_at(v, 1) == -1);
}
void test_set_last()
{
    array_list *v = array_list_create(3, sizeof(int));
    int a = 0, b = 1, c = 2;
    array_list_append(v, &a);
    array_list_append(v, &b);
    array_list_append(v, &c);
    int x = -1;
    assert(array_list_set(v, &x, v->size - 1) == 0);
    assert(*(int *)array_list_at(v, v->size - 1) == -1);
}

void test_set_out_of_range()
{
    array_list *v = array_list_create(3, sizeof(int));
    int a = 0, b = 1;
    array_list_append(v, &a);
    array_list_append(v, &b);
    int x = -1;
    assert(array_list_set(v, &x, 2) == -1);
}

void test_set_complex()
{
    array_list *v = array_list_create(3, sizeof(char[3]));
    char *a = "123", *b = "456", *c = "789";
    array_list_append(v, a);
    array_list_append(v, b);
    array_list_append(v, c);
    char *x = "abc";
    assert(array_list_set(v, x, 1) == 0);
    assert(strcmp((char*)array_list_at(v, 1), "abc") == 0);
}

/* Remove tests */
array_list *before_remove_tests() 
{
    array_list *v = array_list_create(3, sizeof(int));
    int a = 0, b = 1, c = 2;
    array_list_append(v, &a);
    array_list_append(v, &b);
    array_list_append(v, &c);
    assert(v->size == 3);
    return v;
}

void test_remove_first() 
{
    array_list *v = before_remove_tests();
    array_list_remove(v, 0);
    assert(v->size == 2);
    assert(*(int *)array_list_at(v, 0) == 1);
    array_list_destroy(v);
}

void test_remove_last()
{
    array_list *v = before_remove_tests();
    array_list_remove(v, v->size - 1);
    assert(v->size == 2);
    assert(*(int *)array_list_at(v, v->size - 1) == 1);
    array_list_destroy(v);
}

void test_remove_middle()
{
    array_list *v = before_remove_tests();
    array_list_remove(v, 1);
    assert(v->size == 2);
    assert(*(int *)array_list_at(v, 0) == 0);
    assert(*(int *)array_list_at(v, v->size - 1) == 2);
    array_list_destroy(v);
}

void test_remove_empty()
{
    array_list *v = array_list_create(0, sizeof(int));
    assert(array_list_remove(v, 0) == -1);
}
void test_remove_out_of_range()
{
    array_list *v = array_list_create(1, sizeof(int));
    int x = 0;
    array_list_append(v, &x);
    assert(array_list_remove(v, 1) == -1);
}
void test_remove_large()
{
    array_list *v = array_list_create(1000, sizeof(int));
    for (int i = 0; i < v->capacity; i++) {
        array_list_append(v, &i);
    }
    assert(array_list_remove(v, 500) == 1);
    assert(v->size == 999);
    assert(*(int*)array_list_at(v, 0) == 0);
    assert(*(int*)array_list_at(v, v->size - 1) == 999);
    assert(*(int*)array_list_at(v, 500) == 501);
}
