#include <stdio.h>

#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

// ============================================================
// Test Declarations — implemented in tests.cpp
// ============================================================

// PART 1: text views
void test_format_empty_tree_is_empty_string(void);
void test_format_sideways_single_node(void);
void test_format_level_order_levels(void);
void test_format_dfs_preorder(void);

// PART 2: binary files
void test_save_and_load_roundtrip(void);
void test_save_and_load_empty_tree(void);
void test_load_missing_file_throws(void);
void test_load_wrong_magic_throws(void);

// ============================================================
// Required by Unity Framework
// ============================================================
void setUp(void)    {}
void tearDown(void) {}

// ============================================================
// Main Test Runner
// ============================================================
int main(void)
{
    UNITY_BEGIN();

    // ========== PART 1 ==========
    RUN_TEST(test_format_empty_tree_is_empty_string);
    RUN_TEST(test_format_sideways_single_node);
    RUN_TEST(test_format_level_order_levels);
    RUN_TEST(test_format_dfs_preorder);

    // ========== PART 2 ==========
    RUN_TEST(test_save_and_load_roundtrip);
    RUN_TEST(test_save_and_load_empty_tree);
    RUN_TEST(test_load_missing_file_throws);
    RUN_TEST(test_load_wrong_magic_throws);

    int result = UNITY_END();
    return result;
}
