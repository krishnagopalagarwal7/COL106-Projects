#include "stack_b.h"
#include <iostream>
#include <stdexcept>
using namespace std;
Stack_B::Stack_B()
{
    size = 0;
    capacity = 1024;
}
Stack_B::~Stack_B()
{
    delete [] stk ;
}
void Stack_B::push(int data)
{
    if (size >= capacity)
    {
        capacity = capacity * 2;

        int *newarray = new int[capacity];
        for (int i = 0; i < size; i++)
        {
            newarray[i] = stk[i];
        }
        delete[] stk;
        stk = newarray;
        stk[size] = data;
        size++;
    }
    else
    {
        stk[size]=data;
        size++;
    }
}
int Stack_B::pop(){
        if(size == 0){
            throw runtime_error("Empty Stack");
        }
        else if(capacity>1024 && size <= capacity/4-1){
            capacity /= 2;
            int* newarray = new int[capacity];
            for (int i = 0; i < size; i++){
                newarray[i] = stk[i];
            }
            delete[] stk;
            stk = newarray;
        }
        size--;
        return stk[size];
    }
int Stack_B::get_element_from_top(int idx)
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
int Stack_B::get_element_from_bottom(int idx)
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
void Stack_B::print_stack(bool top_or_bottom)
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
int Stack_B::add()
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
int Stack_B::subtract()
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
int Stack_B::multiply()
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
int Stack_B::divide()
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
int *Stack_B::get_stack()
{
    return stk;
}
int Stack_B::get_size()
{
    return size;
}