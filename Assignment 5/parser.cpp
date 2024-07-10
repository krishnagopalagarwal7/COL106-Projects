/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

// Write your code below this line

Parser::Parser()
{
    symtable = new SymbolTable();
}

ExprTreeNode *parseToken(string token, vector<ExprTreeNode *> &stk, int &i)
{
    // If the token is an opening parenthesis,
    // create a new node and push_back it onto the stack.
    if (token == "(")
    {
        return NULL;
    }

    // If the token is a closing parenthesis,
    // pop_back the top two nodes off the stack
    // make the top node the right child of the second node.
    else if (token == ")")
    {
        ExprTreeNode *rightNode = stk[stk.size() - 1];
        stk.pop_back();
        ExprTreeNode *node = stk[stk.size() - 1];
        stk.pop_back();
        node->right = rightNode;
        return node;
    }

    // If the token is an operator,
    // pop_back the top node off the stack and make it the left child
    // of a new node with the current token as its type.
    // Then push_back the new node onto the stack.
    else if (token == "+" || token == "-" || token == "*" || token == "/")
    {
        ExprTreeNode *node = new ExprTreeNode(token, 0);
        ExprTreeNode *leftNode = stk[stk.size() - 1];
        stk.pop_back();
        node->left = leftNode;
        stk.push_back(node);
        return NULL;
    }

    // If the token does not fall into any of the above categories,
    // check if it is a number.
    // if not a number, it is a variable.
    else
    {
        ExprTreeNode *node = new ExprTreeNode(token, 0);
        return node;
    }
}

void Parser::parse(vector<string> expression)
{
    // Create a stack to store the expression tree nodes.
    vector<ExprTreeNode *> stk;

    // Create the root node of the expression tree.
    ExprTreeNode *root = new ExprTreeNode(expression[1], 0);
    root->left = new ExprTreeNode(expression[0], 0);

    // push_back the root node onto the stack.
    stk.push_back(root);

    // Iterate over the expression, starting at index 2.
    for (int i = 2; i < expression.size(); i++)
    {
        // Parse the current token.
        ExprTreeNode *node = parseToken(expression[i], stk, i);

        // If the current node is not null,
        // push_back it onto the stack.
        if (node != NULL)
        {
            stk.push_back(node);
        }
    }

    // finally we will be left with two nodes in the stack.
    // pop_back the top two nodes off the stack
    // make the top node the right child of the second node.
    ExprTreeNode *rightNode = stk[stk.size() - 1];
    stk.pop_back();
    ExprTreeNode *rootNode = stk[stk.size() - 1];
    stk.pop_back();
    rootNode->right = rightNode;

    if (rootNode->left->type == "VAR")
    {
        symtable->insert(rootNode->left->id);
    }

    // Add the root node to the list of expression trees.
    expr_trees.push_back(rootNode);
}

Parser::~Parser()
{
    for (int i = 0; i < expr_trees.size(); i++)
    {
        delete expr_trees[i];
        expr_trees[i] = NULL;
    }
    expr_trees.clear();
    delete symtable;
}