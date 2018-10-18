#pragma once
#include <iostream>
#include <cmath>
using namespace std;

template <typename T>
struct Node
{
    T data;
    Node *next;
    Node *prev;
    Node(const T& _data, Node* _next, Node* _prev);
};

template <typename T>
class DLList
{
private:
    Node<T> *first;
    Node<T> *last;
    size_t size;

    Node<T> *lastFound;
    size_t lastFoundIndex;

    void copy(const DLList<T>& other);
    void erase();
public:
    DLList();
    DLList(const DLList<T>& other);
    DLList& operator=(const DLList<T>& other);
    ~DLList();

    size_t getSize()const;

    T& operator[](size_t index);

    void push(const T& dt);
    void pop();
    T& top()const;
};



template <typename T>
Node<T>::Node(const T& _data, Node<T>* _next, Node<T>* _prev)
:data(_data),next(_next),prev(_prev){}

template <typename T>
void DLList<T>::copy(const DLList<T>& other)
{
    if(other.first == nullptr)
    {
        this->first = nullptr;
        this->last = nullptr;
        this->size == 0;
        return;
    }
    this->first = new Node<T>(other.first->data, nullptr, nullptr);
    Node<T>* pointerToThis = this->first;
    Node<T>* pointerToOther = other.first->next;
    while(pointerToOther != nullptr)
    {
        pointerToThis->next = new Node<T>(pointerToOther->data, nullptr, pointerToThis);
        pointerToThis = pointerToThis->next;
        pointerToOther = pointerToOther->next;
    }
    this->size = other.size;
    this->last = pointerToThis;
    lastFoundIndex = -1;
    lastFound = nullptr;
}

template <typename T>
void DLList<T>::erase()
{
    Node<T>* save;
    while(this->first != nullptr)
    {
        save = this->first->next;
        delete this->first;
        first = save;
    }
    this->size = 0;
    this->last = nullptr;
    this->lastFound = nullptr;
    this->lastFoundIndex = -1;
}

template <typename T>
DLList<T>::DLList()
{
    this->first = nullptr;
    this->last = nullptr;
    this->size = 0;
    this->lastFound = nullptr;
    this->lastFoundIndex = -1;
}

template <typename T>
DLList<T>::DLList(const DLList<T>& other)
{
    this->copy(other);
}

template <typename T>
DLList<T>& DLList<T>::operator=(const DLList<T>& other)
{
    if(this != &other)
    {
        this->erase();
        this->copy(other);
    }
    return *this;
}

template <typename T>
DLList<T>::~DLList()
{
    this->erase();
}

template <typename T>
size_t DLList<T>::getSize()const
{
    return this->size;
}

template <typename T>
T& DLList<T>::operator[](size_t index)
{
    if(index < 0 || index >= this->size)
        throw out_of_range("Invalid index");
    if((abs(index - this->lastFoundIndex) < abs(index - this->size))
        && lastFoundIndex != -1)
    {
        if(index > this->lastFoundIndex)
        {
            while(lastFoundIndex != index)
            {
                lastFound = lastFound->next;
                lastFoundIndex++;
            }
        }
        else if (index < this->lastFoundIndex)
        {
            while(lastFoundIndex != index)
            {
                lastFound = lastFound->prev;
                lastFoundIndex--;
            }
        }
    }
    else
    {
        this->lastFound = this->first;
        this->lastFoundIndex = 0;
        while(lastFoundIndex != index)
        {
            lastFound = lastFound->next;
            lastFoundIndex++;
        }
    }
    return lastFound->data;
}

template <typename T>
void DLList<T>::push(const T& dt)
{
    if(first == nullptr)
    {
        first = new Node<T>(dt, nullptr, nullptr);
        last = new Node<T>(dt, nullptr, nullptr);
    }
    else
    {
        Node<T>* newNode = new Node<T>(dt, first, nullptr);
        first->prev = newNode;
        first = newNode;
    }
    size++;
    lastFound = nullptr;
    lastFoundIndex = -1;
}

template <typename T>
void DLList<T>::pop()
{
    if(first == nullptr)
        throw length_error("You can't pop out of an empty list");
    Node<T>* save = first->next;
    delete first;
    first = save;
    size--;
    if(first == nullptr)
        last = nullptr;
    lastFound = nullptr;
    lastFoundIndex = -1;
}

template <typename T>
T& DLList<T>::top()const
{
    if(first == nullptr)
        throw logic_error("Empty list");
    return first->data;
}
