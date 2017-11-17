#define _CRT_SECURE_NO_WARNINGS
#include "lexeme.h"

Lexeme::Lexeme(const char *input) {
	for (int i = 0; i < 256; i++) {
		list[i] = NULL;
	}
	idNum = 0;
	prepare();

	if (input == NULL)return;
	content = std::string(input);
}
Lexeme::~Lexeme() {

}

int Lexeme::preserve(char *str) {
	int value = 0;
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		value += str[i];
	}
	value %= 256;
	hashNode *tmp = list[value];
	while (tmp != NULL && strcmp(tmp->name.c_str(), str) != 0) {
		tmp = tmp->next;
	}
	if (tmp == NULL) {
		tmp = new hashNode();
		tmp->id = idNum++;
		tmp->type = TT_SYS;
		tmp->name = string(str);
		tmp->next = list[value];
		list[value] = tmp;
		strId.push_back(string(str));
	}
	return tmp->id;
}
void Lexeme::prepare() {
	preserve("integer");
	preserve("char");
	preserve("string");
	preserve("float");
	preserve("bool");
	preserve("array");
	preserve("class");
	preserve("function");
	preserve("none");
	preserve("let");
	preserve("be");
	preserve("new");
	preserve("with");
	preserve("start");
	preserve("end");
	preserve("if");
	preserve("then");
	preserve("else");
	preserve("loop");
	preserve("when");
	preserve("of");
	preserve("is");
	preserve("are");
	preserve("smaller");
	preserve("larger");
	preserve("than");
	preserve("use");
	preserve("library");
	preserve("result");
	preserve("quit");
	preserve("and");
	preserve("or");
	preserve("not");
	preserve("xor");
	preserve("break");
	preserve("redo");
	preserve("comment");
}
Lexeme *Lexeme::input(const char *str) {
	content = std::string(str);
	return this;
}
vector<tokenPrim> Lexeme::parse() {
	int len = content.length();
	for (int i = 0; i < len; i++) {
		tokenPrim *node = new tokenPrim();
		if (content[i] == ' ')continue;
		else if (content[i] >= '0' && content[i] <= '9' || content[i] == '-') {
			if (content[i] == '-' && (content[i + 1] < '0' || content[i + 1] > '9')) {
				node->type = TT_OP;
				node->value = 0;
				if (content[i + 1] == '-') {
					node->id = OP_MINUSMINUS;
					i++;
					output.push_back(*node);
					continue;
				}
				else if (content[i + 1] == '=') {
					node->id = OP_EQMINUS;
					i++;
					output.push_back(*node);
					continue;
				}
				else {
					node->id = OP_MINUS;
					output.push_back(*node);
					continue;
				}
			}
			else if((content[i + 1] < '0'||content[i+1]>'9')&&content[i+1]!='.') {
				error((string()+content[i]).c_str(), LE_ILLEGAL);
			}
			node->type = TT_DATA;
			node->id = 0;
			node->value = float(atof(content.c_str() + i));
			output.push_back(*node);
			i++;
			bool point = false;
			while (content[i] >= '0' && content[i] <= '9' || content[i] == '.') {
				if (content[i] == '.') {
					if (point)break;
					else point = true;
				}
				i++;
			}
			i--;
			if (content[i] == '.')i--;
			continue;
		}
		else if (content[i] >= 'A'&&content[i] <= 'Z' || content[i] >= 'a'&&content[i] <= 'z' || content[i] == '_') {
			node->type = TT_SYS;
			node->value = 0;
			char *str = (char *)malloc(32);
			int j = 0;
			while (content[i] >= 'A'&&content[i] <= 'Z' || content[i] >= 'a'&&content[i] <= 'z' ||
				content[i] >= '0'&&content[i] <= '9' || content[i] == '_') {
				str[j++] = content[i++];
				if (j == 31) {
					str[j] = '\0';
					error(str, LE_TOOLONG);
				}
			}
			str[j] = '\0';
			node->id = hash(str);
			if (node->id > ID_COMMENT) {
				node->type = TT_USER;
			}
			output.push_back(*node);
			i--;
			continue;
		}
		else {
			node->type = TT_OP;
			node->value = 0;
			std::string str;
			char *a = new char[32];
			switch (content[i]) {
			case '+':
				if (content[i + 1] == '+') {
					node->id = OP_PLUSPLUS;
					i++;
					output.push_back(*node);
					continue;
				}
				else if (content[i + 1] == '=') {
					node->id = OP_EQPLUS;
					i++;
					output.push_back(*node);
					continue;
				}
				else {
					node->id = OP_PLUS;
					output.push_back(*node);
					continue;
				}
			case '-':
				if (content[i + 1] == '-') {
					node->id = OP_MINUSMINUS;
					i++;
					output.push_back(*node);
					continue;
				}
				else if (content[i + 1] == '=') {
					node->id = OP_EQMINUS;
					i++;
					output.push_back(*node);
					continue;
				}
				else {
					node->id = OP_MINUS;
					output.push_back(*node);
					continue;
				}
			case '*':
				if (content[i + 1] == '=') {
					node->id = OP_EQMULTY;
					i++;
					output.push_back(*node);
					continue;
				}
				else {
					node->id = OP_MULTY;
					output.push_back(*node);
					continue;
				}
			case '/':
				if (content[i + 1] == '=') {
					node->id = OP_EQDIVIDE;
					i++;
					output.push_back(*node);
					continue;
				}
				else {
					node->id = OP_DIVIDE;
					output.push_back(*node);
					continue;
				}
			case '&':
				if (content[i + 1] == '&') {
					node->id = OP_ANDAND;
					i++;
					output.push_back(*node);
					continue;
				}
				else if (content[i + 1] == '=') {
					node->id = OP_EQAND;
					i++;
					output.push_back(*node);
					continue;
				}
				else {
					node->id = OP_AND;
					output.push_back(*node);
					continue;
				}
			case '|':
				if (content[i + 1] == '|') {
					node->id = OP_OROR;
					i++;
					output.push_back(*node);
					continue;
				}
				else if (content[i + 1] == '=') {
					node->id = OP_EQOR;
					i++;
					output.push_back(*node);
					continue;
				}
				else {
					node->id = OP_OR;
					output.push_back(*node);
					continue;
				}
			case '^':
				if (content[i + 1] == '=') {
					node->id = OP_EQNOR;
					i++;
					output.push_back(*node);
					continue;
				}
				else {
					node->id = OP_NOR;
					output.push_back(*node);
					continue;
				}
			case '~':
				if (content[i + 1] == '=') {
					node->id = OP_EQINVERSE;
					i++;
					output.push_back(*node);
					continue;
				}
				else {
					node->id = OP_INVERSE;
					output.push_back(*node);
					continue;
				}
			case '(':
				node->id = OP_LBRACE;
				output.push_back(*node);
				continue;
			case ')':
				node->id = OP_RBRACE;
				output.push_back(*node);
				continue;
			case '[':
				node->id = OP_LPARENTHESIS;
				output.push_back(*node);
				continue;
			case ']':
				node->id = OP_RPARENTHESIS;
				output.push_back(*node);
				continue;
			case '{':
				node->id = OP_LBRAKET;
				output.push_back(*node);
				continue;
			case '}':
				node->id = OP_RBRAKET;
				output.push_back(*node);
				continue;
			case '>':
				if (content[i + 1] == '=') {
					node->id = OP_NSMALLER;
					i++;
					output.push_back(*node);
					continue;
				}
				else {
					node->id = OP_GREATER;
					output.push_back(*node);
					continue;
				}
			case '<':
				if (content[i + 1] == '=') {
					node->id = OP_NGREATER;
					i++;
					output.push_back(*node);
					continue;
				}
				else {
					node->id = OP_SMALLER;
					output.push_back(*node);
					continue;
				}
			case ';':
				node->id = OP_SEMI;
				output.push_back(*node);
				continue;
			case ',':
				node->id = OP_COMMA;
				output.push_back(*node);
				continue;
			case '.':
				node->id = OP_DOT;
				output.push_back(*node);
				continue;
			case  '!':
				if (content[i + 1] == '=') {
					node->id = OP_NOTEQ;
					i++;
					output.push_back(*node);
					continue;
				}
				else {
					node->id = OP_NOT;
					output.push_back(*node);
					continue;
				}
			case '=':
				node->id = OP_EQUAL;
				output.push_back(*node);
				continue;
			case '?':
				node->id = OP_QUERY;
				output.push_back(*node);
				continue;
			case '\'':
				node->type = TT_DATA;
				i++;
				while (content[i] != '\''&& i < (int)content.length()) {
					str.push_back(content[i++]);
				}
				if (content[i] != '\'')
					error("", LE_INCOMPLETE);
				strcpy(a, str.c_str());
				node->id = hash(a);
				node->s = a;
				output.push_back(*node);
				continue;
			case '\"':
				node->id = OP_DBQUOT;
				output.push_back(*node);
				continue;
			}
		}
	}
	return output;
}
int Lexeme::hash(string str) {
	int value = 0;
	int len = str.length();
	for (int i = 0; i < len; i++) {
		value += str[i];
	}
	value %= 256;
	hashNode *tmp = list[value];
	while (tmp != NULL && str != tmp->name) {
		tmp = tmp->next;
	}
	if (tmp == NULL) {
		tmp = new hashNode();
		tmp->id = idNum++;
		tmp->type = TT_USER;
		tmp->name = *new std::string(str);
		tmp->next = list[value];
		list[value] = tmp;
		strId.push_back(str);
	}
	return tmp->id;
}
void Lexeme::error(const char *word, int type) {
	switch (type) {
	case LE_ILLEGAL:
		throw new LexemeException(string("非法的标识符") + word);
	case LE_TOOLONG:
		throw new LexemeException(string("标识符太长：") + word);
	case LE_INCOMPLETE:
		throw new LexemeException(string("结构不完整") + word);
	}
}
