#include <iostream> 
#include "interval_tree.h"
using namespace std;


// Constructor for initializing an Interval Tree
IntervalTree::IntervalTree()
{
    _root = NULL;
}

// A utility function to insert a new Interval Search Tree Node 
// This is similar to BST Insert.  Here the low value of interval 
// is used tomaintain BST property 
void IntervalTree::insert(ITNode *root, Interval data)
{ 
    // Base case: Tree is empty, new node becomes root 
    if (root == NULL) {
        root = new ITNode(data);
        _root = root;
    }
    else {
        // Get low value of interval at root 
        int l = root->data->low; 
    
        // If root's low value is smaller, then new interval goes to 
        // left subtree 
        if (data.low < l){
            if(!root->left)
            {
                ITNode *tmpNode = new ITNode(data);
                root->left = tmpNode;
            }
            else
            {
                insert(root->left, data);
            }
        }
        else
        {
            if(!root->right)
            {
                ITNode *tmpNode = new ITNode(data);
                root->right = tmpNode;
            }
            else
            {
                insert(root->right, data);
                
            }
        }
    }
    // update max value of ancestor node
    if(root->max < data.high)
        root->max = data.high;
}

  
// A utility function to check if given two intervals overlap 
bool doOverlap(Interval i1, Interval i2) 
{ 
    if (i1.low <= i2.low && i1.high >= i2.high) 
        return true; 
    return false; 
} 


// The main function that searches an interval i in a given 
// Interval Tree. 
bool IntervalTree::overlapSearch(ITNode *root, Interval i) 
{ 
    // Base Case, tree is empty 
    if (root == NULL) return false; 
  
    // If given interval overlaps with root 
    if (doOverlap(*(root->data), i)) 
        return true; 
  
    // If left child of root is present and max of left child is 
    // greater than or equal to given interval, then i may 
    // overlap with an interval in left subtree 
    if (root->left != NULL && root->left->max >= i.low) 
        return overlapSearch(root->left, i); 
  
    // Else interval can only overlap with right subtree 
    return overlapSearch(root->right, i);
}


void IntervalTree::inOrder(ITNode *root) 
{ 
    if (root == NULL) return; 
  
    inOrder(root->left); 
  
    cout << "[" << root->data->low << ", " << root->data->high << "]"
         << " max = " << root->max << endl; 
  
    inOrder(root->right); 
} 



/*
// Simple access functions to retrieve node's interval data
Interval ITNode::getData()const{
    return data;
}

// Simple access functions to retrieve node's left child
ITNode ITNode::getLeft()const{
    return left;
}

// Simple access functions to retrieve node's right child
ITNode ITNode::getRight()const{
    return right;
}


// Simple access functions to set node's left child
void ITNode::setLeft(ITNode *node){
    left = node;
}

// Simple access functions to set node's right child
void ITNode::setRight(ITNode *node){
    right = node;
}
*/

int main()
{
Interval ints[6] = {Interval(15, 20), Interval(30, 10), Interval(17, 19), Interval(5, 20), Interval(12, 15), Interval(30, 40)};
int n = sizeof(ints) / sizeof(ints[0]);
IntervalTree tree = IntervalTree();
cout << "Hello World" << endl;
// populate interval tree
for (int i = 0; i < n; i++)
{
    tree.insert(ints[i]);
}

tree.inOrder();
Interval queries[4] = {Interval(15, 20), Interval(9, 30), Interval(31, 38), Interval(7, 22)};
int num_tests = sizeof(queries) / sizeof(queries[0]);
for (int i = 0; i < num_tests; i++)
{
    cout << "Does " << queries[i].low << ":" << queries[i].high << " Overlap? " << tree.overlapSearch(queries[i]) << endl;
}
return 0;
}