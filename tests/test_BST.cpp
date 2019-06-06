// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code/BST.h"

#include <fstream>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

class test_BST : public ::testing::Test {
protected:
	static void SetUpTestCase(){
	}

	// This function runs only once before any TEST_F function
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open())
		outgrade.clear();

		outgrade << (int)std::ceil(100*total_grade/max_grade);
		outgrade.close();

		std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
	}

	// This function runs after all TEST_F functions have been executed
	void add_points_to_grade(int points){
		max_grade += points;
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after ever TEST_F function
	void TearDown() override {}
	
	static int total_grade;
	static int max_grade;
};

int test_BST::total_grade = 0;
int test_BST::max_grade = 0;

shared_ptr<bst_node> HandBuildNode( int data )
{
  shared_ptr<bst_node> top(new bst_node());
  top->data = data;
  top->left = NULL;
  top->right = NULL;
  
  return top;
}

shared_ptr<bst_node> HandBuildTree ( )
{
	// Hand build an unbalanced tree with 0, 1, 2, 3, 4, 5 in it. Looks
	// like this:
	//
	//    1
	//   / \
	//  0   4
	//     /  \
	//    3    5
	//   /
	//  2
	//
	shared_ptr<bst_node> top = HandBuildNode(1);
	top->left = HandBuildNode(0);
	top->right = HandBuildNode(4);
	top->right->left = HandBuildNode(3);
	top->right->left->left = HandBuildNode(2);
	top->right->right = HandBuildNode(5);
	
	return top;
}

void _inOrderWalk( shared_ptr<bst_node> top, vector<int>& arr, int& index ) {
	if (!top) return;
	// first make an array out of the left side
	if (top->left) _inOrderWalk(top->left, arr, index);

	// add our current node
	arr[index] = top->data;
	index++;

	// and make one from the right
	if (top->right) _inOrderWalk(top->right, arr, index);
}

void inOrderWalk( shared_ptr<bst_node> top, vector<int>& arr) {
	// check for empty tree
	if (!top) return;

	int index = 0;

	// call our helper, with the added index field
	// to keep track of our position in the array
	_inOrderWalk(top, arr, index);
}

int treeSize( shared_ptr<bst_node> top) {
	if (!top) return 0; 

	int left = 0; 
	int right = 0; 

	if (top->left)  left =  treeSize(top->left); 
	if (top->right) right = treeSize(top->right); 

	return left + right + 1; 
}

bool ArrayContains ( vector<int>& arr, int size, int value )
{
	for(int i = 0; i < size; i++){
    	if (arr[i] == value)
		return true;
    }
  return false;
}

TEST_F(test_BST, TestConstructor){
	BST mybst;
	// expect root to be NULL when BST object constructed
	EXPECT_FALSE(mybst.GetRoot());
}


TEST_F(test_BST, TestInit){
	BST mybst;
	shared_ptr<bst_node> nodeptr = mybst.InitNode(4);  
	EXPECT_TRUE(nodeptr);
	EXPECT_EQ(4,nodeptr->data);
	EXPECT_FALSE(nodeptr->left);
	EXPECT_FALSE(nodeptr->right);
}

TEST_F(test_BST, TestInsert){
	// hand build four nodes
	shared_ptr<bst_node> top(new bst_node());
  	top->data = 2;
  	top->left = NULL;
  	top->right = NULL;
	shared_ptr<bst_node> one(new bst_node());
  	one->data = 1;
  	one->left = NULL;
  	one->right = NULL;
	shared_ptr<bst_node> three(new bst_node());
  	three->data = 3;
  	three->left = NULL;
  	three->right = NULL;
	shared_ptr<bst_node> four(new bst_node());
  	four->data = 4;
  	four->left = NULL;
  	four->right = NULL;

	// insert them
	BST mybst;
	mybst.Insert(top);
	mybst.Insert(one);
	mybst.Insert(three);
	mybst.Insert(four);
 
	// expect pointer addresses to be same
	EXPECT_EQ(one.get(),top->left.get());
	EXPECT_EQ(three.get(),top->right.get());
	EXPECT_EQ(four.get(),top->right->right.get());
}

TEST_F(test_BST, TestInsertData){
	// hand build four nodes
	shared_ptr<bst_node> top(new bst_node());
  	top->data = 2;
  	top->left = NULL;
  	top->right = NULL;
	shared_ptr<bst_node> one(new bst_node());
  	one->data = 1;
  	one->left = NULL;
  	one->right = NULL;
	shared_ptr<bst_node> three(new bst_node());
  	three->data = 3;
  	three->left = NULL;
  	three->right = NULL;
	shared_ptr<bst_node> four(new bst_node());
  	four->data = 4;
  	four->left = NULL;
  	four->right = NULL;

	// insert them
	BST mybst;
	mybst.InsertData(2);
	mybst.InsertData(1);
	mybst.InsertData(3);
	mybst.InsertData(4);
 
	// root shouldn't be null
	EXPECT_TRUE(mybst.GetRoot());

	// check for values in the nodes
	EXPECT_EQ(2,mybst.GetRoot()->data);
	EXPECT_EQ(1,mybst.GetRoot()->left->data);
	EXPECT_EQ(3,mybst.GetRoot()->right->data);
	EXPECT_EQ(4,mybst.GetRoot()->right->right->data);

	// check for NULLs in the leafs
	EXPECT_FALSE(mybst.GetRoot()->left->left);
	EXPECT_FALSE(mybst.GetRoot()->left->right);
	EXPECT_FALSE(mybst.GetRoot()->right->left);
	EXPECT_FALSE(mybst.GetRoot()->right->right->left);
	EXPECT_FALSE(mybst.GetRoot()->right->right->right);

}

TEST_F(test_BST, TestSize){
	// hand build a tree of size 6
	shared_ptr<bst_node> top = HandBuildTree();

	BST mybst;
	EXPECT_EQ(6,mybst.Size(top));
}

TEST_F(test_BST, TestContains){
	// hand build a tree, check HandBuildTree() function in this file 
	// for how the tree will look like
  	shared_ptr<bst_node> top = HandBuildTree();
	
	BST mybst;

	EXPECT_TRUE(mybst.Contains(top, 0));
	EXPECT_TRUE(mybst.Contains(top, 1));
	EXPECT_TRUE(mybst.Contains(top, 2));
	EXPECT_TRUE(mybst.Contains(top, 3));
	EXPECT_TRUE(mybst.Contains(top, 4));
	EXPECT_TRUE(mybst.Contains(top, 5));
	

	EXPECT_FALSE(mybst.Contains(top, 22));
	EXPECT_FALSE(mybst.Contains(top, -1));
	EXPECT_FALSE(mybst.Contains(top, 10));
	EXPECT_FALSE(mybst.Contains(top, 6));
	EXPECT_FALSE(mybst.Contains(top, 78));
}

TEST_F(test_BST, TestGetNode){

	// test getting a node from empty tree
	{
		BST mybst;
		shared_ptr<bst_node> empty(NULL);
		shared_ptr<bst_node> result = mybst.GetNode(empty,50);
		// result should be NULL
		EXPECT_FALSE(result);
	}
	// tests getting nodes that we know are NOT there.
	{
		BST mybst;
		shared_ptr<bst_node> top = HandBuildTree();
		EXPECT_FALSE(mybst.GetNode(top,42));
		EXPECT_FALSE(mybst.GetNode(top,-1));
	}
	// tests getting nodes that we know are there.
	{
		BST mybst;
		shared_ptr<bst_node> top = HandBuildTree();
		EXPECT_EQ(mybst.GetNode(top,0),top->left);
		EXPECT_EQ(mybst.GetNode(top,1),top);
		EXPECT_EQ(mybst.GetNode(top,2),top->right->left->left);
		EXPECT_EQ(mybst.GetNode(top,3),top->right->left);
		EXPECT_EQ(mybst.GetNode(top,4),top->right);
		EXPECT_EQ(mybst.GetNode(top,5),top->right->right);
	}
}


TEST_F(test_BST, TestRemove){
	// Create separate scopes for this test.
  {
		// Hand build a node with 0, 1, 2, 3, 4, 5 in it.
		shared_ptr<bst_node> top = HandBuildTree();
		
		// remove the leaf node 5
		BST mybst;
		mybst.SetRoot(top);

		// try removing a leaf
		mybst.Remove(5);
		EXPECT_FALSE(top->right->right);
	}	
	{
		// Tests removing a branch with one child.
				// Hand build a node with 0, 1, 2, 3, 4, 5 in it.
			shared_ptr<bst_node> top = HandBuildTree();
			
			// remove the leaf node 5
			BST mybst;
			mybst.SetRoot(top);

			// try removing a leaf
			mybst.Remove(5);
			EXPECT_FALSE(top->right->right);



    int size = treeSize(top);
    int contents[size];
    int expected[5] = {0, 1, 2, 3, 4};

    inOrderWalk(top, contents);
   
    bool result = true;

    for (int i = 0; i < 5; i++) {
      if (contents[i] != expected[i]) {
        result = false;
        break;
      }
    }
    result = result && size == 5;
    
    REQUIRE(result); // tests removing a leaf
  }
  {
    // Hand build a node with 0, 1, 2, 3, 4, 5 in it.
    bt_node* top = HandBuildTree();
    
    // remove the branch node 3
    remove( &top, 3 );

    int size = treeSize(top);
    int contents[size];
    int expected[5] = {0, 1, 2, 4, 5};

    inOrderWalk(top, contents);
   
    bool result = true;

    for (int i = 0; i < 5; i++) {
      if (contents[i] != expected[i]) {
        result = false;
        break;
      }
    }
    result = result && size == 5;
    
    REQUIRE(result); // Tests removing a branch with one child.
  }
}
/*



TEST_CASE("bst: remove", "[remove]") {
  // Create separate scopes for this test.
  {
    // Hand build a node with 0, 1, 2, 3, 4, 5 in it.
    bt_node* top = HandBuildTree();
    
    // remove the leaf node 5
    remove( &top, 5 );

    int size = treeSize(top);
    int contents[size];
    int expected[5] = {0, 1, 2, 3, 4};

    inOrderWalk(top, contents);
   
    bool result = true;

    for (int i = 0; i < 5; i++) {
      if (contents[i] != expected[i]) {
        result = false;
        break;
      }
    }
    result = result && size == 5;
    
    REQUIRE(result); // tests removing a leaf
  }
  {
    // Hand build a node with 0, 1, 2, 3, 4, 5 in it.
    bt_node* top = HandBuildTree();
    
    // remove the branch node 3
    remove( &top, 3 );

    int size = treeSize(top);
    int contents[size];
    int expected[5] = {0, 1, 2, 4, 5};

    inOrderWalk(top, contents);
   
    bool result = true;

    for (int i = 0; i < 5; i++) {
      if (contents[i] != expected[i]) {
        result = false;
        break;
      }
    }
    result = result && size == 5;
    
    REQUIRE(result); // Tests removing a branch with one child.
  }
}

TEST_CASE("bst: remove with 2 children", "[remove fork]") {
  // Hand build a node with 0, 1, 2, 3, 4 in it.
  bt_node* top = HandBuildTree();
  
  // remove the trunk node 1
  // Note that there are two possible results for this depending on
  // what bias the tree is.
  remove( &top, 1 );
  
  int size = treeSize(top);
  REQUIRE(size == 5);
  int contents[size];
  int expected[5] = {0, 2, 3, 4, 5};
  
  inOrderWalk(top, contents);
  
  bool result = true;
  
  for (int i = 0; i < 5; i++) {
    cout << "expecting " << expected[i] << ", actual " << contents[i] << endl;
    REQUIRE(contents[i] == expected[i]);
  }
}

TEST_CASE("bst: to array", "[to array]") {
  bt_node* top = HandBuildTree();
  
  int results[6] = {-1, -1, -1, -1, -1, -1};
  to_array(top, results);
  
  REQUIRE(results[0] != -1);
  REQUIRE(results[1] != -1);
  REQUIRE(results[2] != -1);
  REQUIRE(results[3] != -1);
  REQUIRE(results[4] != -1);
  REQUIRE(results[5] != -1);
  
  REQUIRE(ArrayContains(results, 6, 0));
  REQUIRE(ArrayContains(results, 6, 1));
  REQUIRE(ArrayContains(results, 6, 2));
  REQUIRE(ArrayContains(results, 6, 3));
  REQUIRE(ArrayContains(results, 6, 4));
  REQUIRE(ArrayContains(results, 6, 5));
  
  REQUIRE(results[0] == 0);
  REQUIRE(results[1] == 1);
  REQUIRE(results[2] == 2);
  REQUIRE(results[3] == 3);
  REQUIRE(results[4] == 4);
  REQUIRE(results[5] == 5); 
}

bt_node* HandBuildNode ( int data )
{
  bt_node* top = new bt_node();
  top->data = data;
  top->left = NULL;
  top->right = NULL;
  
  return top;
}

bt_node* HandBuildTree ( )
{
  // Hand build an unbalanced tree with 0, 1, 2, 3, 4, 5 in it. Looks
  // like this:
  //
  //    1
  //   / \
  //  0   4
  //     /  \
  //    3    5
  //   /
  //  2
  //
  bt_node* top = HandBuildNode(1);
  top->left = HandBuildNode(0);
  top->right = HandBuildNode(4);
  top->right->left = HandBuildNode(3);
  top->right->left->left = HandBuildNode(2);
  top->right->right = HandBuildNode(5);
  
  return top;
}

static void _inOrderWalk( bt_node* top, int arr[], int * index ) {
  if (!top) return;
  // first make an array out of the left side
  if (top->left) _inOrderWalk(top->left, arr, index);

  // add our current node
  arr[*index] = top->data;
  (*index)++;

  // and make one from the right
  if (top->right) _inOrderWalk(top->right, arr, index);
}

void inOrderWalk( bt_node* top, int arr[]) {
  // check for empty tree
  if (!top) return;

  int index = 0;

  // call our helper, with the added index field
  // to keep track of our position in the array
  _inOrderWalk(top, arr, &index);
}

int treeSize( bt_node* top) {
  if (!top) return 0; 

  int left = 0; 
  int right = 0; 

  if (top->left)  left =  treeSize(top->left); 
  if (top->right) right = treeSize(top->right); 

  return left + right + 1; 
}

bool ArrayContains ( int arr[], int size, int value )
{
  for ( int i = 0; i < size; i++ )
    {
      if ( arr[i] == value )
	return true;
    }
  
  return false;
}
*/