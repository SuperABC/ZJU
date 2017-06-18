#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include "file.h"

extern int dbNum;
extern Database *db[MAXDB];

Database *load(char *name) {
	if (name) {
		Database *tmpDb = new Database(SGstring(name));
		std::ifstream dbin(std::string("save\\") + name + ".mdb", std::ios::in | std::ios::binary);
		dbin >> tmpDb->name;
		dbin >> tmpDb->focus;
		int tableNum;
		std::vector<std::string> tableName;
		std::string tmpName;
		dbin >> tableNum;
		for (int i = 0; i < tableNum; i++) {
			dbin >> tmpName;
			tableName.push_back(tmpName);
		}
		dbin.close();
		int tmpNum, tmpPk, tmpAmount;
		std::vector<attribColumn *> tmpSchema;
		std::vector<tupleContent *> tmpTuple;
		std::vector<elementNode *> tmpValue;
		std::string tmpAttrib;
		std::string tmpType;
		float *tmpFloat = new float();
		unsigned char *tmpCharn = new unsigned char[32];
		for (int i = 0; i < tableNum; i++) {
			tmpSchema.clear();
			tmpTuple.clear();
			tmpValue.clear();
			std::ifstream tin(std::string("save\\") + tableName[i] + ".mt", std::ios::in | std::ios::binary);
			tin >> tmpName;
			tin >> tmpNum;
			for (int j = 0; j < tmpNum; j++) {
				tin >> tmpAttrib;
				tin >> tmpType;
				tmpSchema.push_back(new attribColumn(strType(tmpType.c_str()), tmpAttrib));
			}
			Table *tmpTable = new Table(SGstring(tmpName.c_str()), tmpSchema);
			tin >> tmpPk;
			tmpTable->setPk(tmpPk);
			tin >> tmpAmount;
			for (int j = 0; j < tmpAmount; j++) {
				tin >> tmpAttrib;
				tin >> tmpType;
				tmpValue.clear();
				for (int k = 0; k < tmpNum; k++) {
					if (tmpSchema[k]->type == AT_INTEGER ||
						tmpSchema[k]->type == AT_FLOAT) {
						tin >> *tmpFloat;
						tmpValue.push_back(new elementNode(tmpSchema[k]->type, new float(*tmpFloat)));
					}
					if (tmpSchema[k]->type == AT_CHARN) {
						tin >> tmpCharn;
						unsigned char *insertCharn = new unsigned char[32];
						strcpy((char *)insertCharn, (char *)tmpCharn);
						tmpValue.push_back(new elementNode(tmpSchema[k]->type, insertCharn));
					}
				}
				tmpTuple.push_back(new tupleContent(*new attribColumn(strType(tmpType.c_str()), tmpAttrib), tmpValue));
			}
			tmpTable->setTuple(&tmpTuple);
			tmpDb->tables.push_back(tmpTable);
			tin.close();
		}
		return tmpDb;
	}
	else {
		std::ifstream sysin(std::string("save\\") + "system" + ".mda", std::ios::in | std::ios::binary);
		sysin >> dbNum;
		char *tmpName = new char[32];
		for (int s = 0; s < dbNum; s++) {
			sysin >> tmpName;
			db[s] = load(tmpName);
		}
		return NULL;
	}
}
bool save(Database *d, Table *t) {
	std::ofstream sysout(std::string("save\\") + "system" + ".mda", std::ios::out | std::ios::binary | std::ios::trunc);
	sysout << dbNum << std::endl;
	for (int i = 0; i < dbNum; i++) {
		sysout << db[i]->name << std::endl;
	}
	sysout.close();
	std::ofstream dbout(std::string("save\\") + d->name + ".mdb", std::ios::out | std::ios::binary | std::ios::trunc);
	dbout << d->name << std::endl;
	dbout << d->focus << std::endl;
	dbout << d->tables.size() << std::endl;
	for (unsigned int i = 0; i < d->tables.size(); i++) {
		dbout << d->tables[i]->name << std::endl;
	}
	dbout.close();
	if (t) {
		std::ofstream tout(std::string("save\\") + t->name + ".mt", std::ios::out | std::ios::binary | std::ios::trunc);
		tout << t->name << std::endl;
		tout << t->getAttrib()->size() << std::endl;
		for (unsigned int i = 0; i < t->getAttrib()->size(); i++) {
			tout << (*t->getAttrib())[i]->name << std::endl;
			tout << typeStr((*t->getAttrib())[i]->type) << std::endl;
		}
		tout << t->getPk() << std::endl;
		tout << t->getTuple()->size() << std::endl;
		for (unsigned int i = 0; i < t->getTuple()->size(); i++) {
			tout << (*t->getTuple())[i]->pk.name << std::endl;
			tout << typeStr((*t->getTuple())[i]->pk.type) << std::endl;
			for (unsigned int j = 0; j < (*t->getTuple())[i]->value.size(); j++) {
				switch ((*t->getTuple())[i]->value[j]->type) {
				case	AT_FLOAT:
					tout << *(float *)(*t->getTuple())[i]->value[j]->value << std::endl;
					break;
				case AT_CHARN:
					tout << (char *)(*t->getTuple())[i]->value[j]->value << std::endl;
					break;
				case AT_INTEGER:
					tout << (int)*(float *)(*t->getTuple())[i]->value[j]->value << std::endl;
					break;
				}
			}
		}
		tout.close();
	}
	else {
		for (unsigned int i = 0; i < d->tables.size(); i++) {
			t = d->tables[i];
			std::ofstream tout(std::string("save\\") + t->name + ".mt", std::ios::out | std::ios::binary | std::ios::trunc);
			tout << t->name << std::endl;
			tout << t->getAttrib()->size() << std::endl;
			for (unsigned int j = 0; j < t->getAttrib()->size(); j++) {
				tout << (*t->getAttrib())[j]->name << std::endl;
				tout << typeStr((*t->getAttrib())[j]->type) << std::endl;
			}
			tout << t->getPk() << std::endl;
			tout << t->getTuple()->size() << std::endl;
			for (unsigned int j = 0; j < t->getTuple()->size(); j++) {
				tout << (*t->getTuple())[j]->pk.name << std::endl;
				tout << typeStr((*t->getTuple())[j]->pk.type) << std::endl;
				for (unsigned int k = 0; k < (*t->getTuple())[j]->value.size(); k++) {
					switch ((*t->getTuple())[j]->value[k]->type) {
					case	AT_FLOAT:
						tout << *(float *)(*t->getTuple())[j]->value[k]->value << std::endl;
						break;
					case AT_CHARN:
						tout << (char *)(*t->getTuple())[j]->value[k]->value << std::endl;
						break;
					case AT_INTEGER:
						tout << (int)*(float*)(*t->getTuple())[j]->value[k]->value << std::endl;
						break;
					}
				}
			}
			tout.close();
		}
	}
	return true;
}

char *typeStr(ATTRIBTYPE t) {
	switch (t) {
	case AT_FLOAT:
		return "float";
	case AT_CHARN:
		return "charn";
	case AT_INTEGER:
		return "integer";
	case AT_NOCARE:
		return "nocare";
	}
	return NULL;
}
int strType(const char *t) {
	if (std::string("float") == std::string(t))return AT_FLOAT;
	if (std::string("integer") == std::string(t))return AT_INTEGER;
	if (std::string("charn") == std::string(t))return AT_CHARN;
	return -1;
}
