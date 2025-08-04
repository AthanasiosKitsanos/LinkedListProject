#pragma once

template<typename T>
struct Node
{
    Node* next;
    alignas(alignof(T)) unsigned char data[sizeof(T)];
};
