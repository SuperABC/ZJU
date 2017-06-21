#ifndef LEXEME_H
#define LEXEME_H
#include <vector>
#include <cstring>
#include "../sgl/winsgl.h"

enum TOKENTYPE{
	TT_USER,
	TT_DATA,
	TT_OP,
	TT_SYS,
};

enum IDENTIFIER {
	ID_INT,
	ID_CHAR,
	ID_FLOAT,
	ID_NULL,

	ID_CREATE,
	ID_DROP,
	ID_SELECT,
	ID_ALTER,
	ID_UPDATE,
	ID_INSERT,
	ID_DELETE,
	ID_USE,

	ID_DATABASE,
	ID_TABLE,
	ID_INDEX,
	ID_KEY,

	ID_FROM,
	ID_WHERE,
	ID_INTO,
	ID_VALUES,
	ID_SET,

	ID_CONSTRAINT,
	ID_PRIMARY,
	ID_DISTINCT,
	ID_UNIQUE,
	ID_CHECK,
	
	ID_AND,
	ID_OR,
	ID_AS,
	ID_IN,
	ID_ON,

	ID_RENAME,
	ID_COLUMN,
	ID_MODIFY,
	ID_ADD,
	ID_CHANGE,

	ID_IF,
	ID_GO,
	ID_BEGIN,
	ID_END
};
enum OPERATOR {
	OP_PLUS,
	OP_PLUSPLUS,
	OP_EQPLUS,
	OP_MINUS,
	OP_MINUSMINUS,
	OP_EQMINUS,
	OP_MULTY,
	OP_EQMULTY,
	OP_DIVIDE,
	OP_EQDIVIDE,
	OP_AND,
	OP_ANDAND,
	OP_EQAND,
	OP_OR,
	OP_OROR,
	OP_EQOR,
	OP_NOR,
	OP_EQNOR,
	OP_INVERSE,
	OP_EQINVERSE,
	OP_LBRACE,
	OP_RBRACE,
	OP_LPARENTHESIS,
	OP_RPARENTHESIS,
	OP_LBRAKET,
	OP_RBRAKET,
	OP_SEMI,
	OP_COMMA,
	OP_DOT,
	OP_SMALLER,
	OP_NSMALLER,
	OP_GREATER,
	OP_NGREATER,
	OP_NOT,
	OP_NOTEQ,
	OP_EQUAL,
	OP_QUERY,
	OP_QUOT,
	OP_DBQUOT
};

enum LEXEMEERROR {
	LE_UNDEFINED,
	LE_TOOLONG,
	LE_INCOMPLETE
};

typedef struct _hn {
	enum TOKENTYPE type;
	std::string name;
	int id;
	struct _hn *next;
}hashNode;
typedef struct {
	enum TOKENTYPE type;
	int id;
	float value;
	char *s;
}tokenPrim;

class Lexeme {
private:
	std::string content;
	int idNum;
	hashNode *list[256];

	std::vector<tokenPrim>output;
public:
	std::vector<char *>strId;

	Lexeme(const SGstring input = NULL);
	~Lexeme();

	void prepare();
	std::vector<tokenPrim>parse();
	int preserve(char *str);
	int hash(char *s);
	static void error(const char *word, int type);
};

class LexemeException {
private:
	std::string msg;
public:
	LexemeException(std::string s) {
		msg = s;
	}
	const char *message() { return msg.c_str(); }
};
#endif
