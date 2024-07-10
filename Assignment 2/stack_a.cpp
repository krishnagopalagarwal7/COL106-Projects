#include "stack_a.h"
#include <iostream>
#include <stdexcept>
using namespace std;
Stack_A::Stack_A()
    {
        size = 0;
    }
void Stack_A::push(int data)
{
    if (size == 1024)
    {
        throw runtime_error("Stack Full");
    }
    else
    {
        stk[size] = data;
        size++;
    }
}
int Stack_A::pop()
{
    if (size == 0)
    {
        throw runtime_error("Empty Stack");
    }
    else
    {
        size--;
        return stk[size];
    }
}
int Stack_A::get_element_from_top(int idx)
{
    if (size - idx - 1 < 0)
    {
        throw runtime_error("Index out of range");
    }
    else
    {
        return stk[size - idx - 1];
    }
}
int Stack_A::get_element_from_bottom(int idx)
{
    if (idx > size - 1)
    {
        throw runtime_error("Index out of range");
    }
    else
    {
        return stk[idx];
    }
}
void Stack_A::print_stack(bool top_or_bottom)
{
    if (top_or_bottom == 1)
    {
        for (int i = 0; i < size; i++)
        {
            cout << stk[size - i - 1] << endl;
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            cout << stk[i] << endl;
        }
    }
}
int Stack_A::add()
{
    if (size < 2)
    {
        throw runtime_error("Not Enough Arguments");
    }
    else
    {
        int p = pop() + pop();
        push(p);
        return p;
    }
}
int Stack_A::subtract()
{
    if (size < 2)
    {
        throw runtime_error("Not Enough Arguments");
    }
    else
    {
        int p = pop();
        int q = pop();
        push(q - p);
        return (q - p);
    }
}
int Stack_A::multiply()
{
    if (size < 2)
    {
        throw runtime_error("Not Enough Arguments");
    }
    else
    {
        int p = pop() * pop();
        push(p);
        return p;
    }
}
int Stack_A::divide()
{
    if (size < 2)
    {
        throw runtime_error("Not Enough Arguments");
    }
    int a = pop();
    int b = pop();
    if (a == 0)
    {
        throw runtime_error("Divide by Zero Error");
    }
    if ((a > 0 && b < 0) || (a < 0 && b > 0))
    {
        if (b % a == 0)
        {
            push(b / a);
        }
        else
        {
            push(b / a - 1);
        }
    }
    else
    {
        push(b / a);
    }
    return stk[size - 1];
}
int *Stack_A::get_stack()
{
    return stk;
}
int Stack_A::get_size()
{
    return size;
}