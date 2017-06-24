#define _CRT_SECURE_NO_WARNINGS
#include "database.h"
#include "index.h"

extern int dbNum;
extern Database *db[MAXDB];

LPWSTR widen(const char *src) {
	int rt;
	LPWSTR rs;
	rt = MultiByteToWideChar(CP_ACP, 0, src, -1, NULL, 0);
	rs = (LPWSTR)malloc(rt * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, src, -1, rs, rt * sizeof(wchar_t));
	return rs;
}

Database::Database(SGstring name) {
	this->name = std::string((char *)name);
	focus = false;
	tables.clear();
}
Database::~Database() {

}

bool Database::create(queryNode *q, bool out) {
	if (q == NULL)return true;
	if (q->type == QT_CREATE) {
		if (q->right == NULL)
			Syntax::error("", SE_INCOMPLETE);
		else if (q->right->type != QT_DATABASE)
			return false;
		else {
			for (int i = 0; i < dbNum; i++) {
				if (db[i]->name == (char *)(q->right->value->ptr))
					Syntax::error(db[i]->name.c_str(), SE_REDEF);
			}
			Database *tmp = new Database(SGstring(q->right->value->ptr));
			db[dbNum++] = tmp;
			if (out) {
				strcpy((char *)getWidgetByName("output")->content,
					(std::string("成功创建数据库") + tmp->name).c_str());
				getWidgetByName("input")->content[0] = '\0';
			}
		}
		return true;
	}
	if (q->type == QT_USE) {
		if (q->right != NULL)
			Syntax::error("", SE_EXPSEMI);
		else if (q->left->type != QT_DATABASE)
			Syntax::error("USE", SE_INVALIDTYPE);
		else {
			if (!dbNum)
				Table::error((char *)(q->left->value->ptr), TE_NOINSTANCE);
			for (int i = 0; i < dbNum; i++) {
				if (db[i]->name == (char *)(q->left->value->ptr)) {
					for (int j = 0; j < dbNum; j++) {
						db[j]->focus = false;
					}
					db[i]->focus = true;
					break;
				}
				if (i == dbNum - 1)
					Table::error((char *)(q->left->value->ptr), TE_NOINSTANCE);
			}
			if (out) {
				strcpy((char *)getWidgetByName("output")->content,
					(std::string("正在使用数据库") + (char *)(q->left->value->ptr)).c_str());
				getWidgetByName("input")->content[0] = '\0';
			}
		}
		return true;
	}
	return false;
}
Table *Database::selectTuple(queryNode *n, bool distinct) {
	if (n->type == QT_SELECT) {
		if (n == NULL || n->left == NULL ||
			n->left->type != QT_ATTRIB || n->left->value == NULL)
			Syntax::error("", SE_UNKNOWN);
		Table *objTable = selectTuple(n->right, distinct);
		if (objTable == NULL)return NULL;
		std::vector<attribColumn*> tmpAttrib;
		if (n->left->value->ptr == NULL) {
			tmpAttrib = *objTable->getAttrib();
		}
		else {
			std::vector<std::string> attribs = *(std::vector<std::string>*)(n->left->value->ptr);
			for (std::string &s : attribs) {
				if (objTable->haveAttrib(SGstring(s.c_str())) == false)
					Lexeme::error(s.c_str(), LE_UNDEFINED);
				else {
					tmpAttrib.push_back(new attribColumn(AT_NOCARE, s));
				}
			}
		}
		Table *rt = new Table(SGstring("tmpTable"), tmpAttrib);
		std::vector<int> proj;
		for (unsigned int j = 0; j < tmpAttrib.size(); j++) {
			for (unsigned int i = 0; i < objTable->getAttrib()->size(); i++) {
				if ((*objTable->getAttrib())[i]->name == tmpAttrib[j]->name) {
					proj.push_back(i);
				}
			}
		}
		std::vector<tupleContent *> content = *objTable->getTuple();
		std::vector<elementNode *> newValue;
		for (tupleContent *t : content) {
			newValue.clear();
			for (unsigned int i = 0; i < proj.size(); i++) {
				newValue.push_back(t->value[proj[i]]);
			}
			rt->insertTuple(newValue);
		}
		return rt;
	}
	if (n->type == QT_TABLE) {
		for (unsigned int i = 0; i < this->tables.size(); i++) {
			if (this->tables[i]->name == (char *)n->value->ptr) {
				if (n->left==NULL||n->right==NULL)
					return this->tables[i];
				else if(n->left->type!=QT_WHERE)
					Table::error(this->tables[i]->name.c_str(), SE_UNKNOWN);
				else {
					Table *tmp = new Table(SGstring("tmpTable"), *tables[i]->getAttrib());
					if (tables[i]->getIndex()->size() == 0) {
						for (tupleContent *t : *tables[i]->getTuple()) {
							if (Table::accord(Table::copy(n->right), t, tables[i]->getAttrib()))
								tmp->insertTuple(t->value);
						}
						return tmp;
					}
					else {
						int *ac = new int[tables[i]->getTuple()->size()];
						bool use = false;
						std::vector<tupleContent *> *full = tables[i]->getTuple();
						for (Index *idx : *tables[i]->getIndex()) {
							std::vector<int> filter = idx->find(n->right);
							if (filter.size()) {
								for (int &f : filter)ac[f] = 1;
								use = true;
							}
						}
						if (use) {
							for (unsigned int j = 0; j < full->size(); j++) {
								if (ac[j]) {
									if (Table::accord(Table::copy(n->right),
										(*full)[j], tables[i]->getAttrib()))
										tmp->insertTuple((*full)[j]->value);
								}
							}
						}
						else {
							for (tupleContent *t : *tables[i]->getTuple()) {
								if (Table::accord(Table::copy(n->right), t, tables[i]->getAttrib()))
									tmp->insertTuple(t->value);
							}
						}
						return tmp;
					}
				}
			}
			if (i == this->tables.size() - 1)
				Table::error((char *)n->value->ptr, TE_NOINSTANCE);
		}
	}
	return NULL;
}
Table *Database::execute(queryNode *q, bool out) {
	switch (q->type) {
	case QT_DROP:
		if (q->right == NULL || q->left == NULL)
			Syntax::error("", SE_INCOMPLETE);
		else if (q->right->type == QT_DATABASE) {
			for (int i = 0; i < dbNum; i++) {
				if (db[i]->name == (char *)(q->right->value->ptr)) {
					delete db[i];
					db[i] = db[--dbNum];
					db[dbNum] = NULL;
					DeleteFile(widen((std::string("save\\") + (char *)(q->right->value->ptr) + ".mdb").c_str()));
					break;
				}
				if (i == dbNum - 1)
					Table::error((char *)(q->right->value->ptr), TE_NOINSTANCE);
			}
			if (out) {
				strcpy((char *)getWidgetByName("output")->content,
					(std::string("成功删除数据库") + (char *)(q->right->value->ptr)).c_str());
				getWidgetByName("input")->content[0] = '\0';
			}
		}
		else if (q->right->type == QT_TABLE) {
			for (unsigned int i = 0; i < tables.size(); i++) {
				if (tables[i]->name == (char *)(q->right->value->ptr)) {
					delete tables[i];
					tables[i] = tables[tables.size() - 1];
					tables.pop_back();
					DeleteFile(widen((std::string("save\\") + (char *)(q->right->value->ptr) + ".mt").c_str()));
					break;
				}
				if (i == tables.size() - 1)
					Table::error((char *)(q->right->value->ptr), TE_NOINSTANCE);
			}
			if (out) {
				strcpy((char *)getWidgetByName("output")->content,
					(std::string("成功删除表") + (char *)(q->right->value->ptr)).c_str());
				getWidgetByName("input")->content[0] = '\0';
			}
		}
		break;
	case QT_CREATE:
		if (q->right == NULL || q->left == NULL ||
			q->right->value == NULL || q->right->value->ptr == NULL)
			Syntax::error("", SE_INCOMPLETE);
		if (q->left->type == QT_TABLE) {
			if (q->right->left == NULL || q->right->left->type != QT_ATTRIB)
				Table::error("Create table", SE_INCOMPLETE);
			for (Table *t : tables) {
				if (t->name == std::string((char *)q->right->value->ptr))
					Table::error((char *)q->right->value->ptr, TE_REDEF);
			}
			entityNode *tmp = q->right->left->value;
			std::vector<attribColumn *> newAttrib;
			for (entityNode *en : *((std::vector<entityNode*>*)(tmp->ptr))) {
				newAttrib.push_back(new attribColumn(en->type - 3, std::string((char *)en->ptr)));
			}
			int pk = 0;
			if (q->right->right&&q->right->right->type == QT_PK) {
				if (q->right->right->value&&q->right->right->value->type == ET_INTEGER) {
					pk = *(int *)q->right->right->value->ptr;
				}
			}
			tables.push_back(new Table(SGstring(q->right->value->ptr), newAttrib, pk));
			if (out) {
				strcpy((char *)getWidgetByName("output")->content,
					(std::string("成功创建表") + (char *)(q->right->value->ptr)).c_str());
				getWidgetByName("input")->content[0] = '\0';
			}
		}
		if (q->left->type == QT_INDEX) {
			bool success = false;
			for (Table *t : tables) {
				if (t->name == std::string((char *)q->right->left->value->ptr)) {
					for (Index *idx : *t->getIndex()) {
						if (idx->name == std::string((char *)q->right->value->ptr))
							Table::error((char *)q->right->value->ptr, TE_REDEF);
					}
					unsigned int i = 0;
					for (i = 0; i < t->getAttrib()->size(); i++) {
						if ((*t->getAttrib())[i]->name == (char *)q->right->right->value->ptr)
							break;
					}
					t->createIndex((SGstring)q->right->value->ptr, i);
					success = true;
				}
			}
			if (!success)
				Table::error((char *)q->right->left->value->ptr, TE_NOINSTANCE);
			strcpy((char *)getWidgetByName("output")->content,
				(std::string("成功创建索引") + (char *)(q->right->value->ptr)).c_str());
			getWidgetByName("input")->content[0] = '\0';
		}
		break;
	case QT_INSERT:
		if (q->right == NULL || q->left == NULL)
			Syntax::error("", SE_INCOMPLETE);
		if (q->left->type == QT_TABLE) {
			if (q->right->left == NULL || q->right->left->type != QT_ATTRIB)
				Table::error("Insert", SE_INCOMPLETE);
			Table *tmpTable = NULL;
			for (Table *t : tables) {
				if (t->name == std::string((char *)q->left->value->ptr)) {
					tmpTable = t;
					break;
				}
			}
			if (!tmpTable)Table::error((char *)q->left->value->ptr, TE_NOINSTANCE);
			entityNode *tmp = q->right->left->value;
			std::vector<elementNode *> newTuple;
			for (entityNode *en : *((std::vector<entityNode*>*)(tmp->ptr))) {
				newTuple.push_back(new elementNode(en->type - 3, en->ptr));
			}
			tmpTable->insertTuple(newTuple);
			if (out) {
				strcpy((char *)getWidgetByName("output")->content, "成功插入数据");
				getWidgetByName("input")->content[0] = '\0';
			}
			return tmpTable;
		}
		break;
	case QT_SELECT:
		return selectTuple(q, true);
	case QT_ALTER:
		if (q->right == NULL || q->left == NULL ||
			q->right->value == NULL || q->right->value->ptr == NULL)
			Syntax::error("", SE_INCOMPLETE);
		if (q->left->type == QT_TABLE) {
			if (q->right->left == NULL || q->right->left->type != QT_ATTRIB)
				Table::error("Alter table", SE_INCOMPLETE);
			unsigned int i;
			for (i = 0; i < tables.size(); i++) {
				if (tables[i]->name == std::string((char *)q->right->value->ptr))break;
			}
			if (i == tables.size())
				Table::error((char *)q->right->value->ptr, TE_NOINSTANCE);
			if (tables[i]->getTuple()->size())
				Table::error("Alter table", TE_ILLEGAL);
			entityNode *tmp = q->right->left->value;
			std::vector<attribColumn *> newAttrib;
			for (entityNode *en : *((std::vector<entityNode*>*)(tmp->ptr))) {
				newAttrib.push_back(new attribColumn(en->type - 3, std::string((char *)en->ptr)));
			}
			tables[i]->setAttrib(&newAttrib);
			int pk = 0;
			if (q->right->right&&q->right->right->type == QT_PK) {
				if (q->right->right->value&&q->right->right->value->type == ET_INTEGER) {
					pk = *(int *)q->right->right->value->ptr;
				}
			}
			tables[i]->setPk(pk);
			if (out) {
				strcpy((char *)getWidgetByName("output")->content,
					(std::string("成功修改表头") + (char *)(q->right->value->ptr)).c_str());
				getWidgetByName("input")->content[0] = '\0';
			}
		}
		break;
	case QT_DELETE:
		if (q == NULL || q->left == NULL || q->right == NULL)
			Table::error("", TE_ILLEGAL);
		unsigned int i;
		for (i = 0; i < tables.size(); i++) {
			if (tables[i]->name == std::string((char *)q->left->value->ptr))break;
		}
		char *count = new char[8];
		if (i == tables.size())
			Table::error((char *)q->left->value->ptr, TE_NOINSTANCE);
		else sprintf(count, "%d", tables[i]->deleteTuple(q->right));
		if (out) {
			strcpy((char *)getWidgetByName("output")->content,
				(std::string("成功修改") + count + "项").c_str());
			getWidgetByName("input")->content[0] = '\0';
		}
		break;
	}
	return NULL;
}
