#ifndef array_list_TESTS_H
#define array_list_TESTS_H

void run_all_tests();

void test_create_basic();
void test_create_large();
void test_create_complex();

void test_append_empty();
void test_append_non_empty();
void test_append_large();

void test_prepend_empty();
void test_prepend_non_empty();
void test_prepend_large();

void test_insert_empty_i0();
void test_insert_empty_i1();
void test_insert_i0();
void test_insert_mid();
void test_insert_iN();
void test_insert_large();
void test_insert_igtN();
void test_insert_complex();

void test_set_empty();
void test_set_first();
void test_set_mid();
void test_set_last();
void test_set_out_of_range();
void test_set_complex();

void test_remove_first();
void test_remove_last();
void test_remove_middle();
void test_remove_empty();
void test_remove_out_of_range();
void test_remove_large();

#endif //array_list_TESTS_H
