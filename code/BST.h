#ifndef BST_H__
#define BST_H__

#include <string>
#include <memory>
#include <vector>

using namespace std;

  // bt_node is the binary search tree node structure.
  struct bt_node {
    int data;
    shared_ptr<bt_node> left;
    shared_ptr<bt_node> right;
  };

  // Binary search tree:
  //
  // From any subtree node t, the left subtree's data values must be
  // less than t's data value. The right subtree's data values must be
  // greater than or equal to t's data value.
class BST {
public:
  // constructor, initialize class variables and pointers here if need.
  // Initially set top pointer to a null shared_ptr of node
  BST();

  //deconstructor, if you are using shared_pointers you don't need to keep track of
  // freeing memory and you can leave this blank
  ~BST();

  // init_node initializes a new bt_node from the heap using the given
  // data, and two NULL children, and returns a pointer to it.
  shared_ptr<bt_node> InitNode(int data);

  // insert places the new_node in a proper location in the tree
  // indicated by top, while obeying the invariant. On return, *top
  // points to the root of the tree.
  void Insert(shared_ptr<bt_node> new_node);

  // insert_data creates a new node with the given data value and
  // inserts it similarly to insert().
  void Insert_data(int data);

  // remove removes a node from the tree whose data value matches the
  // input. On return, *top points to the root of the tree. If no node
  // in the tree contains the given data, this function has no effect.
  void Remove(int data);

  // contains returns true if any node in the subtree pointed to by t
  // contains the given data value, false otherwise.
  bool Contains(shared_ptr<bt_node> t, int data);

  // get_node searches through the subtree pointed to by t for a node that
  // contains the given data value. If such a node is found, a pointer
  // to it is returned. Otherwise this function returns NULL.
  shared_ptr<bt_node> GetNode(shared_ptr<bt_node> t, int data);

  // size returns the number of nodes in the subtree pointed to by t. If
  // the tree is empty (t is NULL), it returns zero.
  int Size(shared_ptr<bt_node> t);

  // to_array fills an integer array to reflect the contents of the
  // subtree pointed to by t. The filled array will be the same as the
  // subtree's size (found with the size() function), and the order of
  // the array elements are the same that is found during an inorder
  // traversal of the subtree.
  //
  // Note: the array is created and sized before this function is
  // called. You will have at least size(top) elements available, so you
  // may safely index [0..size(t)-1].
  void ToArray(shared_ptr<bt_node> t, int arr[]);

private:
  shared_ptr<bt_node> top_ptr_;
  // you can add add more private member variables and member functions here if you need
};

#endif  // BST_H__