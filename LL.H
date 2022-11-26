#ifndef LL_H
#define LL_H
#include "STUDENT.H"
#include <iostream>
using namespace std;

struct LLnode
{
    LLnode *fwdPtr;
    Student theData;
};

template <class T>
class LL
{
private:
    LLnode *header;

public:
    void push_front(T s);

    void push_back(T s);

    void display_list();

    int list_length();

    T retrieve_front(T s);

    T retrieve_back(T s);

    T search_list(int);

    void destroy_list();
    int list_length_recursive(LLnode *temp);
    bool delete_node(int a);
    void destroy_recursive(LLnode *temp, LLnode *next);
    bool delete_node_recursion(int a, LLnode *previous, LLnode *current, LLnode *next, LLnode *header);

    void push_back_Recursive(LLnode *newNode, LLnode *temp);

    LL()
    {
        header = nullptr;
    }
};

template <class T>
void LL<T>::push_front(T s)
{
    LLnode *newNode = new LLnode();
    LLnode *temp;
    newNode->theData = s;
    newNode->theData.data = s.data;
    newNode->theData.key = s.key;
    temp = header;
    header = newNode;
    newNode->fwdPtr = temp;
}

template <class T>
void LL<T>::push_back_Recursive(LLnode *newNode, LLnode *temp)
{
    if (temp == nullptr)
    {
        temp = newNode;
        return;
    }
    if (temp->fwdPtr == nullptr)
    {
        temp->fwdPtr = newNode;
        return;
    }
    return push_back_Recursive(newNode, temp->fwdPtr);
}

template <class T>
void LL<T>::push_back(T s)
{
    LLnode *newNode = new LLnode();
    LLnode *temp = header;
    newNode->theData.key = s.key;
    newNode->theData.data = s.data;
    newNode->fwdPtr = nullptr;
    return push_back_Recursive(newNode, temp);
}
template <class T>
void LL<T>::display_list()
{
    LLnode *tempp = header;

    int counter = 0;
    if (tempp == nullptr)
    {
        std::cout << "node " << counter << " address -> " << &tempp << "Empty List" << std::endl;
    }
    else
    {
        while (tempp != nullptr)
        {
            std::cout << "node " << counter << " address -> " << &tempp->fwdPtr << " data " << tempp->theData.data << " " << tempp->theData.key << std::endl;
            tempp = tempp->fwdPtr;
            counter++;
        }
    }
}
template <class T>
int LL<T>::list_length_recursive(LLnode *temp)
{
    if (temp == nullptr)
    {
        return 0;
    }
    return 1 + list_length_recursive(temp->fwdPtr);
}
template <class T>
int LL<T>::list_length()
{
    LLnode *temp = header;
    return list_length_recursive(temp);
}

template <class T>
T LL<T>::retrieve_front(T s)
{
    LLnode *temp = header;
    if (temp != nullptr)
    {
        return temp->theData;
    }
    else
        throw std::invalid_argument("empty list");
}

template <class T>
T LL<T>::retrieve_back(T s)
{
    LLnode *temp = header;
    if (temp != nullptr)
    {
        for (int i = 0; i < list_length() + 1; i++)
        {
            temp = temp->fwdPtr;
        }
    }
    else
        throw std::invalid_argument("empty list");
    return temp->theData;
}

template <class T>
void LL<T>::destroy_recursive(LLnode *temp, LLnode *next)
{
    if (temp->fwdPtr == nullptr)
    {
        temp = nullptr;
        header = nullptr;
        return;
    }

    delete temp;

    temp = next;

    return destroy_recursive(temp, next->fwdPtr);
}
template <class T>
void LL<T>::destroy_list()
{
    LLnode *next = new LLnode();
    LLnode *temp = new LLnode();
    temp = header;
    next = header->fwdPtr;
    return destroy_recursive(temp, next);
}

template <class T>
T LL<T>::search_list(int a)
{
    LLnode *temp = new LLnode();
    LLnode *dummy = new LLnode();
    temp = header;
    bool found = false;
    while (temp->fwdPtr != nullptr)
    {
        if (temp->theData.key == a)
        {
            found = true;
            return temp->theData;
        }
        temp = temp->fwdPtr;
    }
    if (found == false)
    {

        dummy->theData.data = "";
        dummy->theData.key = 0;
    }
    return dummy->theData;
}
template <class T>
bool LL<T>::delete_node_recursion(int a, LLnode *previous, LLnode *current, LLnode *next, LLnode *header)

{
    if (header->theData.key == a) // checks if header key is = a
    {

        delete previous;
        previous = current;
        return true;
    }
    if (current->theData.key == a) // current starts after header since header doesnt match.
    {

        delete current;
        previous->fwdPtr = next;
        return true;
    }
    if (current->fwdPtr == nullptr) // checks if the end is reached.
    {

        return false;
    }

    return delete_node_recursion(a, previous->fwdPtr, current->fwdPtr, next->fwdPtr, header);
}
template <class T>
bool LL<T>::delete_node(int a)
{

    LLnode *previous = header;
    LLnode *current = header->fwdPtr;
    LLnode *next = current->fwdPtr;
    return delete_node_recursion(a, previous, current, next, header);
}
#endif
