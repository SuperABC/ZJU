#ifndef FILE_H
#define FILE_H
#include "../dbs/database.h"
#include "../dbs/table.h"

Database *load(char *name);
bool save(Database *d, Table *t);

char *typeStr(ATTRIBTYPE t);
int strType(const char *t);

#endif
