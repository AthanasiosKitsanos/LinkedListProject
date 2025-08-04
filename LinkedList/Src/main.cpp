#include "headers.h"
#include "SinglyLinkedList.h"

int main()
{
    void* rawMemory = _aligned_malloc(sizeof(SinglyLinkedList<int>), alignof(SinglyLinkedList<int>));
    SinglyLinkedList<int>* intList = new(rawMemory) SinglyLinkedList<int>();

    intList->push_front(5);
    intList->push_front(9);

    std::cout << *intList << std::endl;    

    intList->pop_front();

    std::cout << *intList << std::endl;

    intList->pop_front();

    std::cout << *intList << std::endl;
    intList->pop_front();

    //intList->clear();

    intList->~SinglyLinkedList();

    _aligned_free(rawMemory);
    rawMemory = nullptr;
    intList = nullptr;

    std::cout << "Press any key to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    return 0;
}