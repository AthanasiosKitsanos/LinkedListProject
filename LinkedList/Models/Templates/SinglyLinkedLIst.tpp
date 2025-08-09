#include "headers.h"
#include "SinglyLinkedList.h"


template<typename T>
std::ostream& operator<<(std::ostream& os, const SinglyLinkedList<T>& list)
{
    Node<T>* current = list.head;
    os << "Likned List: [";
    while(current != nullptr)
    {
        const T* value = reinterpret_cast<const T*>(&current->data);
        os << *value;
        if(current->next)
        {
            os << ", ";
        }

        current = current->next;
    }

    os << "]" << std::endl;

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
    Node<T>* newNode = create_node(value);
    if(!newNode)
    {
        return;
    }

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

    currentNode->next = create_node(value);
    if(!currentNode->next)
    {
        return;
    }

    currentNode->next->next = nullptr;

    count++;
}

template<typename T>
void SinglyLinkedList<T>::insert_after(const size_t& target, const T& value)
{
    if(count == 0 || head == nullptr)
    {
        push_front(value);
        return;
    }

    if(target == 0 || target == 1)
    {
        Node<T>* newNode = create_node(value);
        if(!newNode)
        {
            return;
        }

        newNode->next = head->next;
        head->next = newNode;
        return;
    }

    if(target >= count)
    {
        push_back(value);
        return;
    }

    Node<T>* current = head;
    for(size_t i = 0; i < target - 1; i++)
    {
        current = current->next;
    }

    Node<T>* newNode = create_node(value);
    if(!newNode)
    {
        return;
    }

    newNode->next = current->next;
    
    current->next = newNode;

    count++;
}

template<typename T>
void SinglyLinkedList<T>::insert_before(const size_t& target, const T& value)
{

    if(count == 0 || head == nullptr)
    {
        push_front(value);
        return;
    }

    if(target == 0 || target == 1)
    {
        push_front(value);
        return;
    }

    Node<T>* current = head;

    if(target >= count)
    {
        for(size_t i = 0; i < count - 1; i++)
        {
            current = current->next;
        }

        Node<T>* newNode = create_node(value);
        if(!newNode)
        {
            return;
        }

        newNode->next = current->next;
        current->next = newNode;
        count++;

        return;
    }
    
    for(size_t i = 0; i < target - 1; i++)
    {
        current = current->next;
    }

    Node<T>* newNode = create_node(value);
    if(!newNode)
    {
        return;
    }

    newNode->next = current->next;
    current->next = newNode;

    count++;
}

template<typename T>
void SinglyLinkedList<T>::replace_at(const size_t& index, const T& value)
{
    if(count == 0 || !head)
    {
        std::cout << "The list is empty, there is nothing to replace" << std::endl;
        return;
    }

    if(index >= count)
    {
        std::cout << "Out of range exception" << std::endl;
        return;
    }

    Node<T>* current = head;
    for(size_t i = 0; i < index; i++)
    {
        current = current->next;
    }

    T* dataPtr = reinterpret_cast<T*>(&(current->data));

    *dataPtr = value;
}

template<typename T>
int SinglyLinkedList<T>::find(const T& value)
{
    if(count == 0 || !head)
    {
        std::cout << "The list is empty, there is nothing to find" << std::endl;
        return -1;
    }

    Node<T>* current = head;
    // int index = 0;
    // while(current && *reinterpret_cast<T*>(current->data) != value)
    // {
    //     current = current->next;
    //     index++;

    //     if(index >= count)
    //     {
    //         return -1;
    //     }
    // }

    // return index;

    for(int i = 0; i < count; i++)
    {
        if(current && *reinterpret_cast<T*>(current->data) == value)
        {
            return static_cast<int>(i);
        }

        current = current->next;
    }

    return -1;
}

template<typename T>
Node<T>* SinglyLinkedList<T>::create_node(const T& element)
{
    void* rawMemory = _aligned_malloc(sizeof(Node<T>), alignof(Node<T>));
    if(!rawMemory)
    {
        std::cout << "Failed to insert new element" << std::endl;
        return nullptr;
    }

    Node<T>* newNode = new(rawMemory) Node<T>();

    newNode->next = nullptr;

    new(newNode->data) T(element);

    return newNode;
}