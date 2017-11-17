#ifndef LEXEME_H
#define LEXEME_H
#include <vector>
#include <string>

#define _CRT_SECURE_NO_WARNINGS
#define SYS_ID_NUM 37

using std::vector;
using std::string;

enum TOKENTYPE {
	TT_NUM,
	TT_OP,
};

enum IDENTIFIER {
	ID_INTEGER,
	ID_CHAR,
	ID_STRING,
	ID_FLOAT,
	ID_BOOL,
	ID_ARRAY,
	ID_CLASS,
	ID_FUNCTION,
	ID_NONE,

	ID_LET,
	ID_BE,
	ID_NEW,
	ID_WITH,
	ID_START,
	ID_END,
	ID_IF,
	ID_THEN,
	ID_ELSE,
	ID_LOOP,
	ID_WHEN,
	ID_OF,
	ID_IS,
	ID_ARE,
	ID_SMALLER,
	ID_LARGER,
	ID_THAN,
	ID_USE,
	ID_LIBRARY,
	ID_RESULT,
	ID_QUIT,
	ID_AND,
	ID_OR,
	ID_NOT,
	ID_XOR,
	ID_BREAK,
	ID_REDO,
	ID_COMMENT
};
enum OPERATOR {
	OP_PLUS,
	OP_MINUS,
	OP_MULTY,
	OP_DIVIDE,
	OP_LBRACE,
	OP_RBRACE,
	OP_COMMA,
	OP_DOT,
	OP_EXP,
	OP_LOG,
	OP_ROOT,
	OP_MOD
};

typedef struct {
	enum TOKENTYPE type;
	char *s;
}tokenPrim;

class Lexeme {
private:
	string content;

public:
	vector<tokenPrim> output;

	Lexeme(const char *input = NULL);
	~Lexeme();

	std::vector<tokenPrim>parse();
};

#endif