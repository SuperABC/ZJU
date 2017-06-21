#ifndef SYNTAX_H
#define SYNTAX_H
#include "lexeme.h"

enum ENTITYTYPE { //locked.
	ET_DATABASE,
	ET_TABLE,
	ET_ATTRIB,
	ET_INTEGER,
	ET_CHARN,
	ET_FLOAT,
	ET_NULL,
	ET_BOOL,
	ET_USER,
	ET_INDEX
};
enum QUERYTYPE { //locked.
	QT_CREATE,
	QT_DROP,
	QT_SELECT,
	QT_ALTER,
	QT_UPDATE,
	QT_INSERT,
	QT_DELETE,
	QT_USE,

	QT_DATABASE,
	QT_TABLE,
	QT_ATTRIB,
	QT_VALUE,
	QT_INDEX,

	QT_WHERE,
	QT_PK
};
enum QUERYSTEP { //locked.
	QS_IDLE,

	QS_CREATE,
	QS_DROP,
	QS_SELECT,
	QS_ALTER,
	QS_UPDATE,
	QS_INSERT,
	QS_DELETE,
	QS_USE,

	QS_CREATEDB,
	QS_CREATET,
	QS_DROPDB,
	QS_DROPT,
	QS_SELECTT,
	QS_ALTERT,
	QS_UPDATET,
	QS_INSERTT,
	QS_DELETET,

	QS_SELECTA,
	QS_SELECTF,

	QS_CREATEIDX,

	QS_COMPLETE
};

enum SYNTAXERROR {
	SE_INCOMPLETE,
	SE_PRELESS,
	SE_USERID,
	SE_EXPSEMI,
	SE_EXPCOMMA,
	SE_EXPBRACE,
	SE_REDEF,
	SE_INVALIDTYPE,
	SE_UNKNOWN,
	SE_UNSUPPORT
};

typedef struct _e {
	enum ENTITYTYPE type;
	void *ptr;
	_e(int t, void *p) { type = ENTITYTYPE(t); ptr = p; }
}entityNode;
typedef struct _q {
	enum QUERYTYPE type;
	enum OPERATOR op;
	entityNode *value;
	struct _q *left, *right;
	_q() { left = right = NULL; value = NULL; }
	~_q() { if (left)delete left; if (right)delete right; if (value)delete value; }
}queryNode;

class Syntax {
private:
	std::vector<tokenPrim>content;
	std::vector<char *>strId;
	enum QUERYSTEP step;
	int proc;
public:
	Syntax(std::vector<char *>ids, std::vector<tokenPrim>input);
	~Syntax();

	static char *opStr(int id);
	static char *valueStr(float value);

	queryNode *parse();
	queryNode *expression(int *proc, queryNode *root);
	static void error(const char *inst, int type);
};

class SyntaxException {
private:
	std::string msg;
public:
	SyntaxException(std::string s) {
		msg = s;
	}
	const char *message() { return msg.c_str(); }
};
#endif
