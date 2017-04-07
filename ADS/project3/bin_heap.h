#ifndef BIN_MIN_HEAP_H
#define BIN_MIN_HEAP_H

#include "heap.h"

template<class Type>
class BinMinHeap: public MinHeap<Type> {
    using MinHeap<Type>::n_element;
    public:
        BinMinHeap();
        BinMinHeap(const MinHeap<Type>&);
        ~BinMinHeap();
        MinHeap<Type>& operator=(MinHeap<Type>&);

        Type& get_top();
        Type& push(const Type&);
        Type& pop();
        Type& replace_top(const Type&);
        MinHeap<Type>& merge(const MinHeap<Type>&) const;
        MinHeap<Type>& meld(const MinHeap<Type>&);
        HeapType heap_type() {return BIN_HEAP;}
        // Return a vector containing the data...
        std::vector<Type> get_raw() const;
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
MinHeap<Type>& operator=(MinHeap<Type> &src)
{
    if(src.heap_type() == BIN_HEAP)
    {
        this->array = src.array;
        this->n_element = src.n_element;
    }
    else
    {
        std::vector<Type> source_raw = src.get_raw();
        BinMinHeap *temp = heapify(source_raw);
        this->array = temp->array;
        this->n_element = temp->n_element;
        delete temp;
    }
    return *this;
}

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
        Type *temp = new Type(array[1]);
        array.pop_back();
        n_element--;
        return *temp;
    }
    if(this->size() == 0)
    {
        Type *temp = new Type;
        return *temp;
    }
    unsigned len = array.size();
    Type *result = new Type(array[1]);
    array[1] = array[len];
    array.pop_back();
    percolate_down(1);
    n_element--;
    return *result;
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
    std::vector<Type> another_raw = another_heap.get_raw();
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
    std::vector<Type> another_raw = another_heap.get_raw();
    raw_vector.insert(raw_vector.begin(),
        this_raw.begin(), this_raw.end());
    raw_vector.insert(raw_vector.end(),
        another_raw.begin(), another_raw.end());
    BinMinHeap<Type>* temp_heap = heapify(raw_vector);
    this->array = temp_heap->array;
    this->n_element = temp_heap->n_element;
    return *this;
}

template<class Type>
std::vector<Type> BinMinHeap<Type>::get_raw() const
{
    std::vector<Type> *result = new std::vector<Type>;
    if(!n_element) return *result;
    result->insert(result->begin(), array.begin() + 1, array.end());
    return *result;
}

#endif
