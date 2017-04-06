#ifndef HEAP_H
#define HEAP_H

#include <vector>

#define MAX_SIZE 300000
#define INFINITY 1000000000

template<class T>
void swap(T *a, T *b) {
    T tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

// Since the heap is essentially priority queue, it shound not allow random
// access to the elements. The implementation of a heap is varied, and these are
// the private matters.
// The very basic methods that a heap should provide are as follows (Wikipedia):
// - Basic
//		- find-min									get_top
//		- insert 		(Special case of meld)		push
//		- extract-min	(Aka pop)					pop
//		- delete-min								pop
//		- replace									replace_top
// - Creation
//		- create-heap								Constructor
//		- heapify									heapify
//		- merge	(Return a new heap)					merge/operator+
//		- meld	(Join but destruct original)		meld/operator+=
// - Inspection
//		- size										size
//		- is-empty									is_empty
// - Internal (varied by implementation, keep them private)
//		- increase/decrease-key
//		- delete
//		- percolate-up
//		- percolate-down
template<class Type>
class MinHeap {
    public:
        // Rule of three
        MinHeap() {n_element = 0;}
        MinHeap(MinHeap<Type> &src) {n_element = src.n_element;}
        virtual ~MinHeap() = 0;
        virtual MinHeap<Type>& operator=(MinHeap<Type> &src)
            {n_element = src.n_element;}
        // find-min/get-top
        virtual Type get_top() const = 0;
        Type find_min() const {return get_top();}
        // merge/operator+
        // The merge method MUST return A NEW INSTANCE
        // ** Don't forget to evaluate new SIZE **
        virtual MinHeap<Type> merge(const MinHeap<Type>&) const = 0;
        MinHeap<Type> operator+(const MinHeap<Type> &another_heap) const
            {return merge(another_heap);}
        // meld/operator+=, return *this
        // The meld method MUST NOT return a new instance, its behavior should
        // be to merge the argument into this heap
        // ** Don't forget to evaluate new SIZE **
        virtual MinHeap<Type> meld(const MinHeap<Type> &src) {return *this;}
        MinHeap<Type> operator+=(const MinHeap<Type> &another_heap)
            {return meld(another_heap);}
        // push
        // Return value is the new top.
        // ** Don't forget to evaluate new SIZE **
        virtual Type push(const Type&);
        // pop
        // Return value is the new top.
        // ** Don't forget to evaluate new SIZE **
        virtual Type pop() = 0;
        // replace_top
        // Return value is the new top.
        // Note that the implementation of the replace method should not be a
        // simple combination of push and pop. There are usually more efficiency
        // algorithms (only one percolation is required).
        virtual Type replace_top(Type&) = 0;
        Type replace(Type& replacing) {return replace_top(replacing);}
        Type replace_min(Type& replacing) {return replace_top(replacing);}
        // size
        unsigned size() const {return n_element;}
        unsigned length() const {return n_element;}
        // is-empty
        bool is_empty() const {return !!n_element;}
    protected:
        // Number of the elements
        unsigned n_element;
};

struct HeapNode {
    int index;
    int distance;
    HeapNode(int i = 0) : index(i), distance(INFINITY) {};
    ~HeapNode() {};
    HeapNode operator=(HeapNode h) {
        index = h.index;
        distance = h.distance;
        return *this;
    }
};

class Heap {
public:
    Heap();
    virtual ~Heap();
    virtual int get() = 0;
    virtual void decrease(int index, int distance) = 0;
protected:
    HeapNode *queue[MAX_SIZE];
    HeapNode *dynQueue[MAX_SIZE];
    int identifier[MAX_SIZE];
    int nodeNum, tmpNum;
};

#endif
