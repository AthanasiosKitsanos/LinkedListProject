#include "headers.h"
#include "SinglyLinkedList.h"


template<typename T>
std::ostream& operator<<(std::ostream& os, const SinglyLinkedList<T>& list)
{
    Node<T>* current = list.head;
    os << "Likned List:" << std::endl;
    while(current != nullptr)
    {
        const T* value = reinterpret_cast<const T*>(&current->data);
        os << *value << std::endl;
        current = current->next;
    }

    return os;
}

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList():head(nullptr), count(0)
{
    
}

template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
    clear();
}

template<typename T>
void SinglyLinkedList<T>::push_front(const T& value)
{
    size_t bytes = (sizeof(Node<T>) + alignof(Node<T>) - 1) & ~(alignof(Node<T>) - 1);
    void* rawMemory = _aligned_malloc(bytes, alignof(Node<T>));

    Node<T>* newNode = new(rawMemory) Node<T>();

    new(newNode->data) T(value);

    newNode->next = head;

    head = newNode;

    count++;
}

template<typename T>
void SinglyLinkedList<T>::clear()
{
    if(count == 0)
    {
        return;
    }

    Node<T>* current = head;

    while(current != nullptr)
    {
        T* dataPtr = reinterpret_cast<T*>(&current->data);

        dataPtr->~T();

        Node<T>* next = current->next;
        _aligned_free(current);
        dataPtr = nullptr;

        current = next;
    }

    head = nullptr;

    count = 0;

    std::cout << "The list is empty" << std::endl;
}

template<typename T>
void SinglyLinkedList<T>::pop_front()
{
    if(count == 0 || head == nullptr)
    {
        std::cout << "pop_front: There is nothing to delete" << std::endl;
        return;
    }

    Node<T>* toDelete = head;

    T* dataPtr = reinterpret_cast<T*>(&toDelete->data);

    dataPtr->~T();
    
    head = toDelete->next;

    _aligned_free(toDelete);
    dataPtr = nullptr;
    toDelete = nullptr;

    count--;
}

template<typename T>
void SinglyLinkedList<T>::push_back(const T& value)
{
    if(count == 0 || head == nullptr)
    {
        push_front(value);
        return;
    }

    Node<T>* currentNode = head;
    while(currentNode->next)
    {
        currentNode = currentNode->next;
    }

    size_t bytes = (sizeof(Node<T>) + alignof(Node<T>) - 1) & ~(alignof(Node<T>) - 1);
    void* rawMemory = _aligned_malloc(bytes, alignof(Node<T>));

    currentNode->next = new(rawMemory) Node<T>();

    new(currentNode->next->data) T(value);

    count++;
    
}