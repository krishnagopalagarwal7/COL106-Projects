/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

// Write your code below this line

SymNode::SymNode()
{
    par = NULL;
    left = NULL;
    right = NULL;
    height = 0;
}

SymNode::SymNode(string k)
{
    par = NULL;
    left = NULL;
    right = NULL;
    key = k;
    height = 0;
}

int height_of_tree(SymNode *node)
{
    if (node == NULL)
    {
        return 0; // Height of a null node is 0
    }
    return node->height;
}

SymNode *SymNode::LeftLeftRotation() // same as right rot
{
    SymNode *newRoot = this->left;
    this->left = newRoot->right;
    newRoot->right = this;

    this->height = 1 + max(height_of_tree(this->left), height_of_tree(this->right));
    newRoot->height = 1 + max(height_of_tree(newRoot->left), this->height);

    return newRoot;
}

SymNode *SymNode::RightRightRotation() // same as left rot
{
    SymNode *newRoot = this->right;
    this->right = newRoot->left;
    newRoot->left = this;

    // Update heights
    this->height = 1 + max(height_of_tree(this->left), height_of_tree(this->right));
    newRoot->height = 1 + max(this->height, height_of_tree(newRoot->right));

    return newRoot;
}

SymNode* SymNode::LeftRightRotation()
{
    if (this == NULL || this->left == NULL)
    {
        return this; // Rotation not possible
    }

    // Perform a left rotation on the left child
    this->left = this->left->RightRightRotation();

    // Perform a right rotation on the current node
    return this->LeftLeftRotation();
}

SymNode *SymNode::RightLeftRotation()
{
    if (this == NULL || this->right == NULL)
    {
        return this; // Rotation not possible
    }

    // Perform a right rotation on the right child
    this->right = this->right->LeftLeftRotation();

    // Perform a left rotation on the current node
    return this->RightRightRotation();
}

SymNode::~SymNode()
{
    left=NULL;
    right=NULL;
    delete left;
    delete right;
}