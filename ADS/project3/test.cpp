#include "bin_heap.h"
#include <iostream>

int main(void)
{
    BinMinHeap<int> heap;
    while(1)
    {
        heap.print();
        int input;
        std::cin >> input;
        if(input == -1)
        {
            heap.pop();
            continue;
        }
        heap.push(input);
    }
    return 0;
}