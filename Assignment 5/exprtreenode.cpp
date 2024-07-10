/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

// Write your code below this line
bool variable(string &krishna)
{
    if (!(krishna[0] == '-' || (krishna[0] >= 48 && krishna[0] <= 57)))
    {
        return true;
    }
    for (int i = 1; i < krishna.size(); i++)
    {
        if (!(krishna[i] >= 48 && krishna[i] <= 57))
        {
            return true;
        }
    }
    return false;
}

ExprTreeNode::ExprTreeNode()
{
    left = NULL;
    right = NULL;
}

ExprTreeNode::ExprTreeNode(string t, int v)
{
    left = NULL;
    right = NULL;
    if (t == "+")
    {
        type = "ADD";
        num = v;
    }
    
    else if (t == "*")
    {
        type = "MUL";
        num = v;
    }
    else if (t == "-")
    {
        type = "SUB";
        num = v;
    }
    else if (t == "/")
    {
        type = "DIV";
        num = v;
    }
    
    else if (t == "ret")
    {
        type = "RET";
        num = v;
    }
    else if (t == "del")
    {
        type = "DEL";
        num = v;
    }
    
    else if (variable(t))
    {
        type = "VAR";
        id = t;
        num = v;
    }
    else
    {
        type = "VAL";
        num = stoi(t);
    }
}

ExprTreeNode::~ExprTreeNode()
{
    left = NULL;
    right = NULL;
    delete left;
    delete right;
}