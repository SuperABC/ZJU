#ifndef DATABASE_H
#define DATABASE_H
#include "table.h"

#define MAXDB 16

typedef struct _h {
	char *name;
	struct _h *next;
}hashName;

class Database {
private:
	std::string name;
	bool focus;
	std::vector<Table *>tables;
public:
	Database(SGstring name = NULL);
	~Database();
	
	bool focused() { return focus; }
	static bool create(queryNode *q, bool out = true);
	Table *selectTuple(queryNode *n, bool distinct);
	Table *execute(queryNode *q, bool out = true);

	friend Database *load(char *name = NULL);
	friend bool save(Database *d, Table *t = NULL);
};

#endif
