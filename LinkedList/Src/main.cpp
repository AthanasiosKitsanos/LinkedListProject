#include "headers.h"
#include "SinglyLinkedList.h"

int main()
{
    void* rawMemory = _aligned_malloc(sizeof(SinglyLinkedList<int>), alignof(SinglyLinkedList<int>));
    SinglyLinkedList<int>* intList = new(rawMemory) SinglyLinkedList<int>();

    intList->push_front(5);
    intList->push_front(9);
    intList->push_back(8);
    
    std::cout << *intList << std::endl;

    std::cin.get();

    intList->insert_after(1, 10);

    std::cout << "Insert After index 1 number 10" << std::endl;
    std::cout << *intList << std::endl;
    std::cin.get();


    std::cout << "Target bigger than count: " << (intList->count < 10 ? "true" : "false") << std::endl;
    intList->insert_before(10, 3);
    std::cout << "Insert Before index 10 number 3" << std::endl;
    std::cout << *intList << std::endl;
    std::cin.get();

    intList->replace_at(1, 25);
    std::cout << "Replaced index 1 (10) with the number 25" << std::endl;
    std::cout << *intList << std::endl;
    std::cin.get();

    int value = 9;
    std::cout << "Index of number " << value << ": "  << intList->find(value) << std::endl;
    
    std::cout << "Count: " <<intList->count <<std::endl;

    intList->~SinglyLinkedList();

    _aligned_free(rawMemory);
    rawMemory = nullptr;
    intList = nullptr;

    std::cout << "Press any key to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    return 0;
}