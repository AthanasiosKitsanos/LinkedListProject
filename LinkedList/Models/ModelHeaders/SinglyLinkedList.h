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
    void insert_after(const size_t& target, const T& value);
    void insert_before(const size_t& target, const T& value);
    Node<T>* create_node(const T& element);
    void replace_at(const size_t& index, const T& value);
    int find(const T& value);
    void remove(const T& value);
};

#include "SinglyLinkedList.tpp"