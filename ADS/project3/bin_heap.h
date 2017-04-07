#include "heap.h"

#ifndef BIN_MIN_HEAP_H
#define BIN_MIN_HEAP_H

template<class Type>
class BinMinHeap: public MinHeap {
    public:
        BinMinHeap();
        BinMinHeap(const MinHeap<Type> &src);
        ~BinMinHeap();
        MinHeap<Type>& operator=(MinHeap<Type> &src);

        Type& get_top();
        Type& push(const Type&);
        Type& pop();
        Type& replace_top(const Type&);
        MinHeap<Type>& merge(const MinHeap<Type>&) const;
        MinHeap<Type>& meld(const MinHeap<Type>&);
        HeapType heap_type() {return BIN_HEAP;}
        std::vector<Type> get_raw();
        static BinMinHeap<Type>* heapify(const std::vector<Type>&);
    private:
        // Internal storage
        std::vector<Type> array;
        bool percolate_up(unsigned);
        bool percolate_down(unsigned);
        // inherited from the base class
        // unsigned n_element;
};

template<class Type>
BinMinHeap<Type>::BinMinHeap()
{
    n_element = 0;
    return;
}

template<class Type>
BinMinHeap<Type>::BinMinHeap(const MinHeap<Type> &src)
{
    n_element = 0;
    if(src.heap_type() == BIN_HEAP)
    {
        BinMinHeap<Type> *ptr = &src;
        this->array = src->array;
        this->n_element = src->n_element;
    }
    else
    {
        BinMinHeap<Type> *temp_heap = heapify(src.get_raw());
        this->array = temp_heap->array;
        this->n_element = src->n_element;
        delete temp_heap;
    }
    return;
}

template<class Type>
BinMinHeap<Type>::~BinMinHeap()
{return;}

template<class Type>
Type& BinMinHeap<Type>::get_top()
{return array[1];}

template<class Type>
Type& BinMinHeap<Type>::push(const Type& element)
{
    unsigned len = array.size();
    array.push_back(element);
    percolate_up(len);
    n_element++;
    return array[1];
}

template<class Type>
Type& BinMinHeap<Type>::pop()
{
    if(this->size() == 1)
    {
        Type temp = array[1];
        array.pop_back();
        n_element--;
        return temp;
    }
    if(this->size() == 0)
    {
        Type temp;
        return temp;
    }
    unsigned len = array.size();
    Type result = array[1];
    array[1] = array[len];
    array.pop_back();
    percolate_down(1);
    n_element--;
    return result;
}

template<class Type>
Type& BinMinHeap<Type>::replace_top(const Type& element)
{
    array[1] = element;
    percolate_down(1);
    return array[1];
}

template<class Type>
MinHeap<Type>& BinMinHeap<Type>::merge(const MinHeap<Type>& another_heap) const
{
    std::vector<Type> raw_vector;
    std::vector<Type> this_raw = this->get_raw();
    std::vector<Type> another_raw = another_heap->get_raw();
    raw_vector.insert(raw_vector.begin(),
        this_raw.begin(), this_raw.end());
    raw_vector.insert(raw_vector.end(),
        another_raw.begin(), another_raw.end());
    return *heapify(raw_vector);
}

template<class Type>
MinHeap<Type>& BinMinHeap<Type>::meld(const MinHeap<Type>& another_heap)
{
    std::vector<Type> raw_vector;
    std::vector<Type> this_raw = this->get_raw();
    std::vector<Type> another_raw = another_heap->get_raw();
    raw_vector.insert(raw_vector.begin(),
        this_raw.begin(), this_raw.end());
    raw_vector.insert(raw_vector.end(),
        another_raw.begin(), another_raw.end());
    BinMinHeap<Type>* temp_heap = heapify(raw_vector);
    this->array = temp_heap->array;
    this->n_element = temp_heap->n_element;
    return MinHeap<Type>*(*this);
}

#endif