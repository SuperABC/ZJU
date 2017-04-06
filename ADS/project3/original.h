#include "heap.h"

#ifndef ORIGINAL_H
#define ORIGINAL_H

class Original : public Heap {
public:
	Original(int num) { nodeNum = num; tmpNum = num; };
	virtual ~Original() {};
	virtual int get();
	virtual void decrease(int index, int distance);
};

template<class Type>
class BinMinHeap:public MinHeap<Type> {
	public:
		BinMinHeap();
		BinMinHeap(const BinMinHeap<Type> &src);
		~BinMinHeap();
		BinMinHeap<Type>& operator=(BinMinHeap<Type> &src);
		Type& get_top() const;
		BinMinHeap<Type>& merge(const BinMinHeap<Type>&) const;
		BinMinHeap<Type>& meld(const BinMinHeap<Type>&);
		Type& push(const Type&);
		Type& pop(const Type&);
		Type& replace_top(Type&);
};

#endif 