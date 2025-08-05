#pragma once

#include "Node.h"

template<typename T>
struct SinglyLinkedList
{
    Node<T>* head;
    size_t count;

    SinglyLinkedList();
    ~SinglyLinkedList();

    void push_front(const T& value);
    void clear();
    void pop_front();
    void push_back(const T& value);
};

#include "SinglyLinkedList.tpp"