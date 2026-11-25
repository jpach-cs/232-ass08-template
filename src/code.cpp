// ============================================================
// CSCI 232 Assignment 08 – Binary Tree: Text Views and Binary Files
// Student Implementation
// ============================================================

#include "code.hpp"
#include <format>
#include <queue>
#include <stack>

// Uncomment the author block below and fill in your name:

// std::string AUTHOR_NAME       = "Your Name";
// std::string AUTHOR_AUTHORSHIP = "I acknowledge that I have worked on this "
// "assignment independently, except where explicitly noted and referenced. "
// "Any collaboration or use of external resources has been properly cited. "
// "I am fully aware of the consequences of academic dishonesty and agree "
// "to abide by the university's academic integrity policy.";

// ===== BEGIN PART 1 (do not remove this marker) =====
// ============================================================
// PART 1: Text views of the tree
// ============================================================
// Return std::string, never print. Build text with std::format, std::to_string and +=.

/// Public entry point: check indent, create the result string, call sidewaysFrom.
/// Throws std::invalid_argument if indent is negative.
std::string BinaryTree::formatSideways(int indent) const
{
    // TODO: implement
    return "";
}

/// Recursive helper: right subtree first, then the node, then the left subtree.
/// A node at depth 'depth' is printed as  (depth * indent spaces) + "--> " + value + "\n".
void BinaryTree::sidewaysFrom(const TreeNode *node, int depth, int indent, std::string &out)
{
    // TODO: implement
}

/// One line per level, values separated by ONE space. Use std::queue<const TreeNode *>.
/// Hint: at the start of every level, q.size() is the number of nodes on that level.
/// Skeleton:  push the root; while the queue is not empty: levelSize = q.size();
///            repeat levelSize times: take the front, pop it, append its value to the line,
///            push its left and right child (when they exist); then append the line and '\n'.
std::string BinaryTree::formatLevelOrder() const
{
    // TODO: implement
    return "";
}

/// Preorder in ONE line, values separated by ONE space. Use std::stack<const TreeNode *>.
/// Skeleton: the same loop as the level order, with a stack: take the top, pop it, append its
/// value, push the RIGHT child, then push the LEFT child (LIFO: the left one comes out first).
std::string BinaryTree::formatDfs() const
{
    // TODO: implement
    return "";
}
// ===== END PART 1 (do not remove this marker) =====

// ===== BEGIN PART 2 (do not remove this marker) =====
// ============================================================
// PART 2: Binary serialization (write / read, no << and no >>)
// ============================================================

/// Writes ONE position: a 0 byte for a missing child, or a 1 byte + the value (std::int32_t)
/// + the left subtree + the right subtree. Recursive, preorder.
void BinaryTree::writeNode(const TreeNode *node, std::ofstream &out)
{
    // TODO: implement
}

/// Opens the file (std::ios::binary), writes kMagic, the count as std::int32_t, then the body.
/// Throws TreeFileError if the file cannot be opened or if writing fails (flush, then check the stream).
void BinaryTree::save(const std::string &filename) const
{
    // TODO: implement
}

/// Reads ONE position into 'slot'. Check the stream after EVERY read. Reject a marker that is
/// neither 0 nor 1 and a body with more nodes than announced. Link the new node into the tree
/// (slot = node) BEFORE reading its children, and set its parentPtr.
void BinaryTree::readNode(std::ifstream &in, TreeNode *parentPtr, TreeNode *&slot,
                          std::int32_t &nodesRead, std::int32_t expectedCount)
{
    // TODO: implement
}

/// Restoring constructor. Open the file, check the magic and the count, read the body with
/// readNode, check that nodesRead equals the announced count. Any problem: throw TreeFileError.
/// A half-built tree must be destroyed (try / catch (...) { destroy(newRoot); throw; }).
BinaryTree::BinaryTree(const std::string &filename) : rootPtr(nullptr), count(0)
{
    // TODO: implement
}
// ===== END PART 2 (do not remove this marker) =====
