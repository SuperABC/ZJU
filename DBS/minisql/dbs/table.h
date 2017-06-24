#ifndef TABLE_H
#define TABLE_H
#include "../parser/syntax.h"
#include <vector>

enum ATTRIBTYPE { //locked.
	AT_INTEGER,
	AT_CHARN,
	AT_FLOAT,
	AT_NOCARE
};

enum TABLEERROR {
	TE_NOINSTANCE,
	TE_REDEF,
	TE_ILLEGAL,
	TE_PRIMCONF
};

struct attribColumn {
	enum ATTRIBTYPE type;
	std::string name;
	attribColumn(int t = 0, std::string n = std::string()) : type((enum ATTRIBTYPE)t), name(n) {};
	bool operator==(attribColumn obj) {
		if (name != obj.name)return false;
		if (type != obj.type)return false;
		return true;
	}
};
struct elementNode {
	enum ATTRIBTYPE type;
	void *value;
	elementNode(int t = 0, void *v = NULL) :type((enum ATTRIBTYPE)t), value(v) {};
	bool operator==(elementNode e) {
		if (type != e.type)return false;
		switch (type) {
		case AT_FLOAT:
			return *(float *)value == *(float *)e.value;
		case AT_INTEGER:
			return (int)*(float *)value == (int)*(float *)e.value;
		case AT_CHARN:
			return std::string((char *)value) == (char *)e.value;
		default:
			return false;
		}
	}
	bool operator<(elementNode e) const {
		if (type != e.type)return false;
		switch (type) {
		case AT_FLOAT:
			return *(float *)value < *(float *)e.value;
		case AT_INTEGER:
			return (int)*(float *)value < (int)*(float *)e.value;
		case AT_CHARN:
			return std::string((char *)value) < (char *)e.value;
		default:
			return false;
		}
	}
};
struct tupleContent {
	attribColumn pk;
	std::vector<elementNode *>value;
	tupleContent(attribColumn k, std::vector<elementNode *>v) : pk(k), value(v) {};
};

class Index;
class Table {
private:
	std::vector<attribColumn *>schema;
	int primaryKey;
	std::vector<tupleContent *>tuple;

	std::vector<Index *> index;
public:
	std::string name;

	Table(SGstring n, std::vector<attribColumn *> s, int pk = 0);
	~Table();

	Index *createIndex(SGstring name, int pk);
	std::vector<Index *> *getIndex() { return &index; }

	bool haveAttrib(SGstring name);
	Table *renameTable(SGstring name);
	Table *alterSchema(attribColumn *old, attribColumn *set);
	std::vector<attribColumn *> *getAttrib();
	void setAttrib(std::vector<attribColumn *> *a) { schema = *a; }
	std::vector<tupleContent *> *getTuple();
	void setTuple(std::vector<tupleContent *> *t) { tuple = *t; }
	int getPk() { return primaryKey; }
	void setPk(int p) { primaryKey = p; }
	static queryNode *copy(queryNode *n);
	static bool accord(queryNode *n, tupleContent *c, std::vector<attribColumn *> *a);

	int deleteTuple(queryNode *q);
	Table *insertTuple(std::vector<elementNode *>n);
	Table *updateTuple(SGstring attrib, elementNode *value, queryNode *q);

	static Table *showTable(Table *t);
	static void error(const char *inst, int type);
};

#endif
