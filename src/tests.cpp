#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

#include "code.hpp"
#include <cstdio>
#include <fstream>
#include <string>

// The sample tree used in many tests:  10 (left 5 (left 3, right 7), right 20)
// Build it with setRoot / addLeft / addRight.
// Temporary files: choose a file name, and remove it at the end with std::remove(name).

// ============================================================
// PART 1 Tests: text views
// ============================================================

/// Create an EMPTY BinaryTree.
/// Verify that formatSideways(), formatLevelOrder() and formatDfs() all return "".
void test_format_empty_tree_is_empty_string(void)
{
    TEST_ASSERT_TRUE_MESSAGE(0, "TODO: Implement this test");
}

/// A tree with ONLY the root 42.
/// Verify formatSideways() returns "--> 42\n".
void test_format_sideways_single_node(void)
{
    TEST_ASSERT_TRUE_MESSAGE(0, "TODO: Implement this test");
}

/// Build the sample tree.
/// Verify formatLevelOrder() returns "10\n5 20\n3 7\n".
void test_format_level_order_levels(void)
{
    TEST_ASSERT_TRUE_MESSAGE(0, "TODO: Implement this test");
}

/// Build the sample tree.
/// Verify formatDfs() returns "10 5 3 7 20\n".
void test_format_dfs_preorder(void)
{
    TEST_ASSERT_TRUE_MESSAGE(0, "TODO: Implement this test");
}

// ============================================================
// PART 2 Tests: binary files
// ============================================================

/// Build the sample tree. save() it to a file, then restore it with BinaryTree loaded(filename).
/// Verify loaded.size() is 5 and loaded.preorder() and loaded.inorder() equal those of the original.
/// Remove the file at the end.
void test_save_and_load_roundtrip(void)
{
    TEST_ASSERT_TRUE_MESSAGE(0, "TODO: Implement this test");
}

/// Save an EMPTY tree and load it back.
/// Verify the loaded tree is empty() and its size() is 0. Remove the file.
void test_save_and_load_empty_tree(void)
{
    TEST_ASSERT_TRUE_MESSAGE(0, "TODO: Implement this test");
}

/// Try to construct a BinaryTree from a file that does not exist.
/// Verify that TreeFileError is thrown (use try / catch and a bool flag).
void test_load_missing_file_throws(void)
{
    TEST_ASSERT_TRUE_MESSAGE(0, "TODO: Implement this test");
}

/// Create a file with std::ofstream (binary) that holds the 4 bytes "XXXX", then a std::int32_t 0
/// and a 0 byte (use write(), not <<). Try to construct a BinaryTree from it.
/// Verify that TreeFileError is thrown. Remove the file.
void test_load_wrong_magic_throws(void)
{
    TEST_ASSERT_TRUE_MESSAGE(0, "TODO: Implement this test");
}
