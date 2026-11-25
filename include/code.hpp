#ifndef CODE_HPP
#define CODE_HPP

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

// ============================================================
// GIVEN: exception and file-format constants
// ============================================================

/// Thrown when a tree file cannot be opened, written or read, or when its content
/// is not a valid tree file. The message always says WHAT went wrong and mentions
/// the file name whenever the problem is about opening a file.
class TreeFileError : public std::runtime_error
{
   public: explicit TreeFileError(const std::string &message) : std::runtime_error(message) {}
};

/// FILE FORMAT of a saved tree (binary, native byte order):
///
///   header:   the 4 bytes of kMagic ("BTR1"), then an std::int32_t with the number of nodes
///   body:     the tree in PREORDER. For every position:
///               - a missing child is ONE byte with the value 0
///               - a node is ONE byte with the value 1, then its value as std::int32_t,
///                 then the whole left subtree, then the whole right subtree
///
/// Example: the tree  1 (left child 2)  is stored as these 21 bytes:
///   'B' 'T' 'R' '1' | 2 (int32) | 1 | 1 (int32) | 1 | 2 (int32) | 0 | 0 | 0
///
/// A tree with n nodes always occupies exactly 6n + 9 bytes. Only VALUES and SHAPE are
/// stored: never a node, never a pointer (a pointer is meaningless in another program run).
inline constexpr char         kMagic[4] = {'B', 'T', 'R', '1'};

/// The reader refuses a header that announces more nodes than this (a corrupt file must
/// not make the program allocate without limit).
inline constexpr std::int32_t kMaxNodes = 1000000;

// ============================================================
// GIVEN: TreeNode (Lecture 18)
// ============================================================

class BinaryTree;

class TreeNode
{
   private: int       value;
   private: TreeNode *parentPtr;
   private: TreeNode *leftPtr;
   private: TreeNode *rightPtr;

   private: friend class BinaryTree;

   public:  explicit TreeNode(int newValue)
                : value(newValue), parentPtr(nullptr), leftPtr(nullptr), rightPtr(nullptr) {}

   public:  int              getValue()  const { return value; }
   public:  const TreeNode *getParent() const { return parentPtr; }
   public:  const TreeNode *getLeft()   const { return leftPtr; }
   public:  const TreeNode *getRight()  const { return rightPtr; }

   // given: a node is never copied
   public:  TreeNode(const TreeNode &) = delete;
   public:  TreeNode &operator=(const TreeNode &) = delete;
};

// ============================================================
// BinaryTree: the tree owns its nodes (Lecture 18)
// ============================================================

class BinaryTree
{
   private: TreeNode   *rootPtr;
   private: std::size_t count;

   // ---------------- GIVEN (Lecture 18): do not change ----------------

   public:  BinaryTree() : rootPtr(nullptr), count(0) {}
   public:  ~BinaryTree() { destroy(rootPtr); }

   public:  bool        empty()   const { return rootPtr == nullptr; }
   public:  std::size_t size()    const { return count; }
   public:  TreeNode   *getRoot() const { return rootPtr; }

   public:  TreeNode *setRoot(int value)
   {
       if (rootPtr != nullptr) throw std::logic_error("setRoot: the tree already has a root");
       rootPtr = new TreeNode(value);
       count   = 1;
       return rootPtr;
   }

   public:  TreeNode *addLeft(TreeNode *parent, int value)
   {
       if (parent == nullptr)            throw std::invalid_argument("addLeft: parent is nullptr");
       if (parent->leftPtr != nullptr)   throw std::logic_error("addLeft: the left child already exists");
       TreeNode *node  = new TreeNode(value);
       node->parentPtr = parent;
       parent->leftPtr = node;
       count++;
       return node;
   }

   public:  TreeNode *addRight(TreeNode *parent, int value)
   {
       if (parent == nullptr)            throw std::invalid_argument("addRight: parent is nullptr");
       if (parent->rightPtr != nullptr)  throw std::logic_error("addRight: the right child already exists");
       TreeNode *node   = new TreeNode(value);
       node->parentPtr  = parent;
       parent->rightPtr = node;
       count++;
       return node;
   }

   /// Number of edges from the root to the node (the root has depth 0).
   public:  int depthOf(const TreeNode *node) const
   {
       int depth = 0;
       while (node != nullptr && node->parentPtr != nullptr)
       {
           node = node->parentPtr;
           depth++;
       }
       return depth;
   }

   public:  std::vector<int> preorder() const  { std::vector<int> out; preorderFrom(rootPtr, out);  return out; }
   public:  std::vector<int> inorder() const   { std::vector<int> out; inorderFrom(rootPtr, out);   return out; }
   public:  std::vector<int> postorder() const { std::vector<int> out; postorderFrom(rootPtr, out); return out; }

   // given: copying a tree would create two owners of the same nodes
   public:  BinaryTree(const BinaryTree &) = delete;
   public:  BinaryTree &operator=(const BinaryTree &) = delete;

   private: static void destroy(TreeNode *node)
   {
       if (node == nullptr) return;
       destroy(node->leftPtr);
       destroy(node->rightPtr);
       delete node;
   }

   private: static void preorderFrom(const TreeNode *node, std::vector<int> &out)
   {
       if (node == nullptr) return;
       out.push_back(node->value);
       preorderFrom(node->leftPtr, out);
       preorderFrom(node->rightPtr, out);
   }

   private: static void inorderFrom(const TreeNode *node, std::vector<int> &out)
   {
       if (node == nullptr) return;
       inorderFrom(node->leftPtr, out);
       out.push_back(node->value);
       inorderFrom(node->rightPtr, out);
   }

   private: static void postorderFrom(const TreeNode *node, std::vector<int> &out)
   {
       if (node == nullptr) return;
       postorderFrom(node->leftPtr, out);
       postorderFrom(node->rightPtr, out);
       out.push_back(node->value);
   }

   // ============================================================
   // PART 1 - YOUR TASK: three text views of the tree (src/code.cpp)
   // ============================================================
   //
   // All three methods RETURN a std::string. They never print: the caller prints.
   // Build the text with std::format, std::to_string and +=. Do not use <<.
   // None of them may modify the tree. For an EMPTY tree all three return "".
   //
   // Take the tree  10 (left 5 (left 3, right 7), right 20)  as the example:
   //
   //    formatSideways()          formatLevelOrder()     formatDfs()
   //           --> 20             10                     10 5 3 7 20
   //    --> 10                    5 20
   //                  --> 7       3 7
   //           --> 5
   //                  --> 3
   //
   // Every line ends with '\n'. Values are separated by ONE space, with NO space at the end of a line.

   /// The tree turned 90 degrees to the left: the root is at the left edge, the right
   /// subtree is ABOVE the node and the left subtree BELOW it. A node at depth d is printed as
   ///        (d * indent spaces) + "--> " + value + "\n".
   /// Recursion: first the right subtree, then the node itself, then the left subtree.
   /// Throws std::invalid_argument if indent is negative.
   public:  std::string formatSideways(int indent = 7) const;

   /// Level by level (breadth-first): one line per depth, from the root down, the nodes of a
   /// level from left to right. NO recursion: use std::queue<const TreeNode *>.
   /// Trick: at the start of a level, q.size() is the number of nodes on that level.
   public:  std::string formatLevelOrder() const;

   /// Preorder (depth-first), all values in ONE line. NO recursion: use
   /// std::stack<const TreeNode *>. The stack is LIFO, so push the RIGHT child first
   /// and the LEFT child second: then the left one is taken out first.
   public:  std::string formatDfs() const;

   private: static void sidewaysFrom(const TreeNode *node, int depth, int indent, std::string &out);

   // ============================================================
   // PART 2 - YOUR TASK: binary serialization (src/code.cpp)
   // ============================================================
   //
   // Use std::ofstream / std::ifstream opened with std::ios::binary and their write() and
   // read() methods (reinterpret_cast<const char *>(&x), sizeof x). Do not use << or >>.
   // Write every field separately: never write a whole TreeNode.

   /// Writes the tree to the file in the format described at kMagic. An existing file is
   /// REPLACED. An empty tree is valid: the file holds the header (count 0) and one 0 byte.
   /// Throws TreeFileError if the file cannot be opened for writing, or if writing fails
   /// (flush the stream and check it before you return). The tree is not modified.
   public:  void save(const std::string &filename) const;

   /// Writes ONE position of the tree (a node with both subtrees, or the 0 byte of a
   /// missing child). Recursive, in preorder.
   private: static void writeNode(const TreeNode *node, std::ofstream &out);

   /// RESTORING constructor: builds the tree from a file written by save().
   /// It throws TreeFileError if
   ///   - the file cannot be opened (the message contains the file name),
   ///   - the first 4 bytes are not kMagic,
   ///   - the announced count is negative or larger than kMaxNodes,
   ///   - the file ends too early (any read fails),
   ///   - a position byte is neither 0 nor 1,
   ///   - the body holds more nodes than announced, or fewer.
   /// IMPORTANT: when a constructor throws, the object never exists and its destructor does
   /// NOT run. Every node created so far must be deleted by the constructor itself, so that a
   /// bad file leaks nothing: wrap the reading in try { ... } catch (...) { destroy(...); throw; }.
   /// Set rootPtr and count only when everything has been read successfully.
   public:  explicit BinaryTree(const std::string &filename);

   /// Reads ONE position (see writeNode) and stores the result in 'slot' (a reference to the
   /// pointer that must receive the new node: the root variable, or a child pointer of
   /// 'parentPtr'). Link the new node into the tree IMMEDIATELY after creating it and BEFORE
   /// you read its children: then a half-built tree is always reachable from the root, and one
   /// destroy() cleans it up. Set the node's parentPtr to 'parentPtr' (the file does not
   /// contain parent pointers: they are rebuilt here). nodesRead counts the nodes created so far.
   private: static void readNode(std::ifstream &in, TreeNode *parentPtr, TreeNode *&slot,
                                 std::int32_t &nodesRead, std::int32_t expectedCount);
};

#endif
