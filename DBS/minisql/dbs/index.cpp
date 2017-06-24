#include "index.h"

std::vector<int> conj(std::vector<int> &v1, std::vector<int> &v2) {
	if (v1.size() == 0)return v2;
	else if (v2.size() == 0)return v1;
	else {
		std::vector<int> rt;
		std::sort(v1.begin(), v1.end());
		std::sort(v2.begin(), v2.end());
		auto i1 = v1.begin(), i2 = v2.begin();
		while (true) {
			if (i1 == v1.end() && i2 == v2.end())break;
			else if (i1 == v1.end())rt.push_back(*(i2++));
			else if (i2 == v2.end())rt.push_back(*(i1++));
			else if (*i1 == *i2) {
				rt.push_back(*i1);
				i1++;
				i2++;
			}
			else if (*i1 < *i2) {
				rt.push_back(*(i1++));
			}
			else if (*i1 > *i2) {
				rt.push_back(*(i2++));
			}
		}
		return rt;
	}
	return *new std::vector<int>();
}
std::vector<int> join(std::vector<int> &v1, std::vector<int> &v2) {
	if (v1.size() == 0)return v2;
	else if (v2.size() == 0)return v1;
	else {
		std::vector<int> rt;
		std::sort(v1.begin(), v1.end());
		std::sort(v2.begin(), v2.end());
		auto i1 = v1.begin(), i2 = v2.begin();
		while (true) {
			if (i1 == v1.end() && i2 == v2.end())break;
			else if (i1 == v1.end())rt.push_back(*(i2++));
			else if (i2 == v2.end())rt.push_back(*(i1++));
			else if (*i1 == *i2) {
				rt.push_back(*i1);
				i1++;
				i2++;
			}
			else if (*i1 < *i2)i1++;
			else if (*i1 > *i2)i2++;
		}
		return rt;
	}
	return *new std::vector<int>();
}

Index::Index(char *name, Table* obj, attribColumn *objAttrib) {
	this->name = name;
	objTable = obj;
	this->objAttrib = *objAttrib;
	content.clear();
	unsigned int pos;
	for (pos = 0; pos < objTable->getAttrib()->size(); pos++) {
		if (objAttrib->name == (*objTable->getAttrib())[pos]->name)break;
	}
	for (unsigned int i = 0; i < obj->getTuple()->size(); i++) {
		auto t = (*obj->getTuple())[i];
		content.push_back(t->value[pos]);
		tree.insert(std::pair<elementNode, int>(*t->value[pos], i));
	}
}
Index::~Index() {}

Index *Table::createIndex(SGstring name, int pk) {
	Index *tmp = new Index((char *)name, this, schema[pk]);
	index.push_back(tmp);
	return tmp;
}

void Index::insert(elementNode node) {
	unsigned int pos;
	content.push_back(new elementNode(node));
	tree.insert(std::pair<elementNode, int>(node, content.size()-1));
}
void Index::del(elementNode *node, int pos) {
	auto range = tree.equal_range(*node);
	while (range.second != range.first) {
		if (range.second->second == pos) {
			tree.erase(range.second);
			content[pos] = NULL;
			break;
		}
		range.second--;
	}
	int i = 0;
	while (i < content.size() - 1) {
		if (content[i])i++;
		else {
			content[i] = content[i + 1];
			content[i + 1] = NULL;
			i++;
		}
	}
	content.pop_back();
}
std::vector<int> Index::find(queryNode *q) {
	std::vector<int> rt;
	if (q->op == OP_ANDAND) {
		return join(find(q->left), find(q->right));
	}
	else if (q->op == OP_OROR) {
		return conj(find(q->left), find(q->right));
	}
	else if (q->op == OP_SMALLER) {
		if (q->left->value->type == ET_USER&&
			q->right->left == NULL&&q->right->right == NULL) {
			std::vector<attribColumn *> *a = objTable->getAttrib();
			unsigned int i;
			for (i = 0; i < a->size(); i++) {
				if ((*a)[i]->name == (char *)(q->left->value->ptr))break;
			}
			elementNode *finder = new elementNode((*a)[i]->type, q->right->value->ptr);
			auto rslt = tree.lower_bound(*finder);
			for (auto b = tree.begin(); b != rslt; b++) {
				rt.push_back(b->second);
			}
			return rt;
		}
		if (q->right->value->type == ET_USER&&
			q->left->left == NULL&&q->left->right == NULL) {
			std::vector<attribColumn *> *a = objTable->getAttrib();
			unsigned int i;
			for (i = 0; i < a->size(); i++) {
				if ((*a)[i]->name == (char *)(q->right->value->ptr))break;
			}
			elementNode *finder = new elementNode((*a)[i]->type, q->left->value->ptr);
			auto rslt = tree.upper_bound(*finder);
			for (auto b = rslt; b != tree.end(); b++) {
				rt.push_back(b->second);
			}
			return rt;
		}
	}
	else if (q->op == OP_GREATER) {
		if (q->left->value->type == ET_USER&&
			q->right->left == NULL&&q->right->right == NULL) {
			std::vector<attribColumn *> *a = objTable->getAttrib();
			unsigned int i;
			for (i = 0; i < a->size(); i++) {
				if ((*a)[i]->name == (char *)(q->left->value->ptr))break;
			}
			elementNode *finder = new elementNode((*a)[i]->type, q->right->value->ptr);
			auto rslt = tree.upper_bound(*finder);
			for (auto b = rslt; b != tree.end(); b++) {
				rt.push_back(b->second);
			}
			return rt;
		}
		if (q->right->value->type == ET_USER&&
			q->left->left == NULL&&q->left->right == NULL) {
			std::vector<attribColumn *> *a = objTable->getAttrib();
			unsigned int i;
			for (i = 0; i < a->size(); i++) {
				if ((*a)[i]->name == (char *)(q->right->value->ptr))break;
			}
			elementNode *finder = new elementNode((*a)[i]->type, q->left->value->ptr);
			auto rslt = tree.lower_bound(*finder);
			for (auto b = tree.begin(); b != rslt; b++) {
				rt.push_back(b->second);
			}
			return rt;
		}
	}
	else if (q->op == OP_NGREATER) {
		if (q->left->value->type == ET_USER&&
			q->right->left == NULL&&q->right->right == NULL) {
			std::vector<attribColumn *> *a = objTable->getAttrib();
			unsigned int i;
			for (i = 0; i < a->size(); i++) {
				if ((*a)[i]->name == (char *)(q->left->value->ptr))break;
			}
			elementNode *finder = new elementNode((*a)[i]->type, q->right->value->ptr);
			auto rslt = tree.lower_bound(*finder);
			for (auto b = rslt; b != tree.end(); b++) {
				rt.push_back(b->second);
			}
			return rt;
		}
		if (q->right->value->type == ET_USER&&
			q->left->left == NULL&&q->left->right == NULL) {
			std::vector<attribColumn *> *a = objTable->getAttrib();
			unsigned int i;
			for (i = 0; i < a->size(); i++) {
				if ((*a)[i]->name == (char *)(q->right->value->ptr))break;
			}
			elementNode *finder = new elementNode((*a)[i]->type, q->left->value->ptr);
			auto rslt = tree.upper_bound(*finder);
			for (auto b = tree.begin(); b != rslt; b++) {
				rt.push_back(b->second);
			}
			return rt;
		}
	}
	else if (q->op == OP_NSMALLER) {
		if (q->left->value->type == ET_USER&&
			q->right->left == NULL&&q->right->right == NULL) {
			std::vector<attribColumn *> *a = objTable->getAttrib();
			unsigned int i;
			for (i = 0; i < a->size(); i++) {
				if ((*a)[i]->name == (char *)(q->left->value->ptr))break;
			}
			elementNode *finder = new elementNode((*a)[i]->type, q->right->value->ptr);
			auto rslt = tree.upper_bound(*finder);
			for (auto b = tree.begin(); b != rslt; b++) {
				rt.push_back(b->second);
			}
			return rt;
		}
		if (q->right->value->type == ET_USER&&
			q->left->left == NULL&&q->left->right == NULL) {
			std::vector<attribColumn *> *a = objTable->getAttrib();
			unsigned int i;
			for (i = 0; i < a->size(); i++) {
				if ((*a)[i]->name == (char *)(q->right->value->ptr))break;
			}
			elementNode *finder = new elementNode((*a)[i]->type, q->left->value->ptr);
			auto rslt = tree.lower_bound(*finder);
			for (auto b = rslt; b != tree.end(); b++) {
				rt.push_back(b->second);
			}
			return rt;
		}
	}
	else if (q->op == OP_EQUAL) {
		if (q->left->value->type == ET_USER&&
			q->right->left == NULL&&q->right->right == NULL) {
			std::vector<attribColumn *> *a = objTable->getAttrib();
			unsigned int i;
			for (i = 0; i < a->size(); i++) {
				if ((*a)[i]->name == (char *)(q->left->value->ptr))break;
			}
			elementNode *finder = new elementNode((*a)[i]->type, q->right->value->ptr);
			auto range = tree.equal_range(*finder);
			for (auto b = range.first; b != range.second; b--) {
				rt.push_back(b->second);
			}
			return rt;
		}
		if (q->right->value->type == ET_USER&&
			q->left->left == NULL&&q->left->right == NULL) {
			std::vector<attribColumn *> *a = objTable->getAttrib();
			unsigned int i;
			for (i = 0; i < a->size(); i++) {
				if ((*a)[i]->name == (char *)(q->right->value->ptr))break;
			}
			elementNode *finder = new elementNode((*a)[i]->type, q->left->value->ptr);
			auto range = tree.equal_range(*finder);
			for (auto b = range.first; b != range.second; b--) {
				rt.push_back(b->second);
			}
			return rt;
		}
	}
	
	return *new std::vector<int>();
}

