#define _CRT_SECURE_NO_WARNINGS
#include "table.h"
#include "index.h"

class Database;

Table::Table(SGstring n, std::vector<attribColumn *>s, int pk) {
	name = std::string((char *)n);
	schema = s;
	primaryKey = pk;
	tuple.clear();
}
Table::~Table() {

}

bool Table::haveAttrib(SGstring name) {
	for (attribColumn *&attr : schema) {
		if (attr->name == std::string((char *)name))return true;
	}
	return false;
}
Table *Table::renameTable(SGstring name) {
	this->name = *new std::string((char *)name);
	return this;
}
Table *Table::alterSchema(attribColumn *old, attribColumn *set) {
	for (attribColumn *&attr : schema) {
		if (*attr == *old) {
			delete attr;
			attr = new attribColumn(*set);
			return this;
		}
	}
	return NULL;
}
std::vector<attribColumn *> *Table::getAttrib() {
	return &schema;
}
std::vector<tupleContent *> *Table::getTuple() {
	return &tuple;
}
queryNode *Table::copy(queryNode *n) {
	if (n == NULL)return NULL;
	queryNode *rt = new queryNode();
	rt->type = n->type;
	rt->op = n->op;
	if (n->value) {
		rt->value = new entityNode(n->value->type, n->value->ptr);
	}
	if (n->left)rt->left = copy(n->left);
	if (n->right)rt->right = copy(n->right);
	return rt;
}
bool Table::accord(queryNode *n, tupleContent *c, std::vector<attribColumn *> *a) {
	if (n->value == NULL)
		error("", TE_ILLEGAL);
	if (n->value->type == ET_USER) {
		for (unsigned int i = 0; i < a->size(); i++) {
			if ((*a)[i]->name == (char *)(n->value->ptr)) {
				switch (c->value[i]->type) {
				case AT_CHARN:
					n->value->type = ET_CHARN;
					n->value->ptr = new char[32];
					strcpy((char *)(n->value->ptr), (char *)(c->value[i]->value));
					break;
				case AT_FLOAT:
					n->value->type = ET_FLOAT;
					n->value->ptr = new float(*(float *)(c->value[i]->value));
					break;
				case AT_INTEGER:
					n->value->type = ET_INTEGER;
					n->value->ptr = new float(*(float *)(c->value[i]->value));
					break;
				}
			}
		}
		return true;
	}
	if (n->left)accord(n->left, c, a);
	if (n->right)accord(n->right, c, a);
	if (n->left == NULL&&n->right != NULL || n->left != NULL&&n->right == NULL)
		error("", TE_ILLEGAL);
	if (n->left&&n->right) {
		switch (n->op) {
		case OP_PLUS:
			if (!((n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER) &&
				(n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER)))
				error("", TE_ILLEGAL);
			n->value->type = ET_FLOAT;
			n->value->ptr = new float(*(float *)(n->left->value->ptr) + *(float *)(n->right->value->ptr));
			break;
		case OP_MINUS:
			if (!((n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER) &&
				(n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER)))
				error("", TE_ILLEGAL);
			n->value->type = ET_FLOAT;
			n->value->ptr = new float(*(float *)(n->left->value->ptr) - *(float *)(n->right->value->ptr));
			break;
		case OP_MULTY:
			if (!((n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER) &&
				(n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER)))
				error("", TE_ILLEGAL);
			n->value->type = ET_FLOAT;
			n->value->ptr = new float(*(float *)(n->left->value->ptr) * *(float *)(n->right->value->ptr));
			break;
		case OP_DIVIDE:
			if (!((n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER) &&
				(n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER)))
				error("", TE_ILLEGAL);
			n->value->type = ET_FLOAT;
			n->value->ptr = new float(*(float *)(n->left->value->ptr) / *(float *)(n->right->value->ptr));
			break;
		case OP_EQUAL:
			if (!((n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER) &&
				(n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER)) &&
				!(n->left->value->type == ET_CHARN&&n->right->value->type == ET_CHARN))
				error("", TE_ILLEGAL);
			n->value->type = ET_BOOL;
			if (n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER) {
				n->value->ptr = new float(*(float *)(n->left->value->ptr) == *(float *)(n->right->value->ptr));
				return *(float *)(n->value->ptr) != 0;
			}
			else if (n->left->value->type == ET_CHARN) {
				n->value->ptr = new float(std::string((char *)(n->left->value->ptr)) == (char *)(n->right->value->ptr));
				return *(float *)(n->value->ptr) != 0;
			}
			break;
		case OP_NOTEQ:
			if (!((n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER) &&
				(n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER)) &&
				!(n->left->value->type == ET_CHARN&&n->right->value->type == ET_CHARN))
				error("", TE_ILLEGAL);
			n->value->type = ET_BOOL;
			if (n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER) {
				n->value->ptr = new float(*(float *)(n->left->value->ptr) != *(float *)(n->right->value->ptr));
				return *(float *)(n->value->ptr) != 0;
			}
			else if (n->left->value->type == ET_CHARN) {
				n->value->ptr = new float(std::string((char *)(n->left->value->ptr)) != (char *)(n->right->value->ptr));
				return *(float *)(n->value->ptr) != 0;
			}
			break;
		case OP_GREATER:
			if (!((n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER) &&
				(n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER)))
				error("", TE_ILLEGAL);
			n->value->type = ET_BOOL;
			n->value->ptr = new float(*(float *)(n->left->value->ptr) > *(float *)(n->right->value->ptr));
			return *(float *)(n->value->ptr) != 0;
		case OP_SMALLER:
			if (!((n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER) &&
				(n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER)))
				error("", TE_ILLEGAL);
			n->value->type = ET_BOOL;
			n->value->ptr = new float(*(float *)(n->left->value->ptr) < *(float *)(n->right->value->ptr));
			return *(float *)(n->value->ptr) != 0;
		case OP_NGREATER:
			if (!((n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER) &&
				(n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER)))
				error("", TE_ILLEGAL);
			n->value->type = ET_BOOL;
			n->value->ptr = new float(*(float *)(n->left->value->ptr) <= *(float *)(n->right->value->ptr));
			return *(float *)(n->value->ptr) != 0;
		case OP_NSMALLER:
			if (!((n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER) &&
				(n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER)))
				error("", TE_ILLEGAL);
			n->value->type = ET_BOOL;
			n->value->ptr = new float(*(float *)(n->left->value->ptr) >= *(float *)(n->right->value->ptr));
			return *(float *)(n->value->ptr) != 0;
		case OP_ANDAND:
			if (!((n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER || n->left->value->type == ET_BOOL) &&
				(n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER || n->left->value->type == ET_BOOL)))
				error("", TE_ILLEGAL);
			n->value->type = ET_BOOL;
			n->value->ptr = new float(*(float *)(n->left->value->ptr) && *(float *)(n->right->value->ptr));
			return *(float *)(n->value->ptr) != 0;
		case OP_OROR:
			if (!((n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER || n->left->value->type == ET_BOOL) &&
				(n->left->value->type == ET_FLOAT || n->left->value->type == ET_INTEGER || n->left->value->type == ET_BOOL)))
				error("", TE_ILLEGAL);
			n->value->type = ET_BOOL;
			n->value->ptr = new float(*(float *)(n->left->value->ptr) || *(float *)(n->right->value->ptr));
			return *(float *)(n->value->ptr) != 0;
		}
	}
	return true;
}

Table *Table::insertTuple(std::vector<elementNode *>n) {
	for (tupleContent *t : tuple) {
		if (*(t->value[this->primaryKey]) == *n[this->primaryKey])
			error(t->pk.name.c_str(), TE_PRIMCONF);
	}
	tuple.push_back(new tupleContent(*this->schema[this->primaryKey], n));
	for (Index *idx : this->index) {
		for (unsigned int i = 0; i < schema.size(); i++) {
			if (idx->objAttrib == *schema[i]) {
				idx->insert(*n[i]);
				break;
			}
		}
	}
	return this;
}
int Table::deleteTuple(queryNode *q) {
	std::vector<int> indices;
	for (unsigned int i = 0; i < tuple.size(); i++) {
		if (accord(copy(q), tuple[i], &schema))
			indices.push_back(i);
	}
	for (int i = indices.size() - 1; i >= 0; i--) {
		for (Index *idx : this->index) {
			for (unsigned int i = 0; i < schema.size(); i++) {
				if (idx->objAttrib == *schema[i]) {
					idx->del(tuple[tuple.size() - 1]->value[i], indices[i]);
					break;
				}
			}
		}
		tuple[indices[i]] = tuple[tuple.size() - 1];
		tuple.pop_back();
	}
	return (int)indices.size();
}
Table *Table::updateTuple(SGstring attrib, elementNode *value, queryNode *q) {
	unsigned int pos;
	for (pos = 0; pos < schema.size(); pos++) {
		if (schema[pos]->name == std::string((char *)attrib))break;
	}
	if (pos == schema.size())
		error(schema[pos]->name.c_str(), TE_NOINSTANCE);

	std::vector<int> index;
	for (unsigned int i = 0; i < tuple.size(); i++) {
		if (accord(copy(q->right), tuple[i], &schema))
			index.push_back(i);
	}
	for (unsigned int i = index.size() - 1; i >= 0; i--) {
		tuple[i]->value[pos] = value;
	}
	return this;
}
Table *Table::showTable(Table *t) {
	std::string msg;
	std::vector<int>pos;
	for (attribColumn *attr : t->schema) {
		msg += attr->name;
		int len = attr->name.length();
		if (len < 9) {
			for (int i = 0; i < 9 - len; i++)msg += " ";
		}
		msg += " | ";
		pos.push_back(attr->name.length() < 9 ? 9 : attr->name.length());
	}
	msg.push_back('\n');
	for (tupleContent *tuple : t->tuple) {
		int i = 0;
		for (elementNode *element : tuple->value) {
			int preDelta, afterDelta;
			preDelta = msg.length();
			char *buffer = (char *)malloc(20);
			switch (element->type) {
			case AT_INTEGER:
				sprintf(buffer, "%d", (int)*(float *)element->value);
				msg += buffer;
				break;
			case AT_FLOAT:
				sprintf(buffer, "%f", *(float *)element->value);
				msg += buffer;
				break;
			case AT_CHARN:
				msg += (char *)element->value;
			}
			free(buffer);
			afterDelta = msg.length();
			if (afterDelta - preDelta < pos[i]) {
				for (int j = 0; j < pos[i] - (afterDelta - preDelta); j++)msg += " ";
			}
			else {
				for (int j = 0; j < afterDelta - preDelta - 9; j++)
					msg.pop_back();
			}
			msg += " | ";
			i++;
		}
		msg.push_back('\n');
	}
	strcpy((char *)getWidgetByName("output")->content,
		msg.c_str());
	getWidgetByName("input")->content[0] = '\0';
	return t;
}

void Table::error(const char *inst, int type) {
	switch (type) {
	case TE_NOINSTANCE:
		throw new SyntaxException(std::string("找不到") + inst);
	case TE_REDEF:
		throw new SyntaxException(std::string("已经存在") + inst);
	case TE_ILLEGAL:
		throw new SyntaxException(std::string("非法表达式") + inst);
	case TE_PRIMCONF:
		throw new SyntaxException(std::string("内容重复的主键") + inst);
	}
}
