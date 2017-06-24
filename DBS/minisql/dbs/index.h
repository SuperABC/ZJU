#ifndef INDEX_H
#define INDEX_H

#include "table.h"
#include "btree.h"

class Index {
private:
	Table *objTable;
	std::vector<elementNode *> content;
	stx::btree<elementNode, int, std::pair<elementNode, int>,
		std::less<elementNode>, stx::btree_default_map_traits<elementNode, int>,
		true>tree;
public:
	std::string name;
	attribColumn objAttrib;

	Index(char *name, Table* obj, attribColumn *objAttrib);
	~Index();

	void insert(elementNode node);
	void del(elementNode *node, int pos);
	std::vector<int> find(queryNode *q);
};

#endif
