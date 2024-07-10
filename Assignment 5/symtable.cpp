/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

// Write your code below this line

SymbolTable::SymbolTable()
{
    size = 0;
    root = NULL;
}
//checked
int height_of_tree_1(SymNode *node)
{
    if (node == NULL)
    {
        return -1; // Height of a null node is 0
    }
    return node->height;
}
//cheched
int getBalanceFactor(SymNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return height_of_tree_1(node->left) - height_of_tree_1(node->right);
}
//checked
SymNode *insert_help(SymNode *root1, string key)
{
    if (root1 == NULL)
    {
        return new SymNode(key);
    }

    if (key < root1->key)
    {
        root1->left = insert_help(root1->left, key);
    }
    else if (key > root1->key)
    {
        root1->right = insert_help(root1->right, key);
    }
    else
    {
        return root1;
    }

    // Update the height of the current node
    root1->height = 1 + max(height_of_tree_1(root1->left), height_of_tree_1(root1->right));

    // Get the balance factor and perform rotations if needed
    int balance = getBalanceFactor(root1);

    // Left heavy
    if (balance > 1)
    {
        if (key < root1->left->key)
        {
            return root1->LeftLeftRotation();
        }
        else
        {
            return root1->LeftRightRotation();
        }
    }
    // Right heavy
    if (balance < -1)
    {
        if (key > root1->right->key)
        {
            return root1->RightRightRotation();
        }
        else
        {
            return root1->RightLeftRotation();
        }
    }
    return root1;
}
//checked
void SymbolTable::insert(string k)
{
    size++;
    root = insert_help(root, k);
}
// Correct upto insert function;
SymNode *minValueNode(SymNode *root)
{
    SymNode *curr1 = root;
    while (curr1->left != NULL)
    {
        curr1 = curr1->left;
    }
    return curr1;
}
//checked
SymNode *helperdelete(SymNode *root, string k)
{
    if (root == NULL)
    {
        return root;
    }
    if (k < root->key)
    {
        root->left = helperdelete(root->left, k);
    }
    else if (k > root->key)
    {
        root->right = helperdelete(root->right, k);
    }
    else
    {
        if (root->left == NULL || root->right == NULL)
        {
            SymNode *temp;
            if(root->left == NULL) temp = root->right;
            else temp = root->left;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            {
                *root = *temp;
                delete temp;
            }
        }
        else
        {
            SymNode *temp = minValueNode(root->right);
            root->key = temp->key;
            root->address = temp->address;

            root->right = helperdelete(root->right, temp->key);
        }
    }
    if (root == NULL)
        return root;
    root->height = 1 + max(height_of_tree_1(root->left), height_of_tree_1(root->right));
    int balance = getBalanceFactor(root);
    // Left Left Case
    if (balance > 1 && getBalanceFactor(root->left) >= 0)
    {
        return root->LeftLeftRotation();
    }
    // Left Right Case
    if (balance > 1 && getBalanceFactor(root->left) < 0)
    {
        return root->LeftRightRotation();
    }
    // Right Right Case
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
    {
        return root->RightRightRotation();
    }
    // Right Left Case
    if (balance < -1 && getBalanceFactor(root->right) > 0)
    {
        return root->RightLeftRotation();
    }
    return root;
}

void SymbolTable::remove(string k)
{
    root = helperdelete(root, k);
    size--;
}

SymNode *search_helper(SymNode *node, string key)
{
    if (node == NULL || node->key == key)
    {
        return node;
    }

    if (key < node->key)
    {
        return search_helper(node->left, key);
    }
    else
    {
        return search_helper(node->right, key);
    }
}

int SymbolTable::search(string k)
{
    SymNode *curr = root;
    curr = search_helper(curr, k);
    if (curr != NULL)
    {
        return curr->address;
    }
    else
    {
        return -2;
    }
}

void SymbolTable::assign_address(string k, int idx)
{
    SymNode *curr = root;
    while (curr != NULL)
    {
        if (k > curr->key)
        {
            curr = curr->right;
        }
        else if (k < curr->key)
        {
            curr = curr->left;
        }
        else
        {
            curr->address = idx;
            return;
        }
    }
}
//checked
int SymbolTable::get_size()
{
    return size;
}
//checked
SymNode *SymbolTable::get_root()
{
    return root;
}

SymbolTable::~SymbolTable()
{
    delete root;
}