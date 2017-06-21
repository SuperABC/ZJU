#define _CRT_SECURE_NO_WARNINGS
#include "syntax.h"

bool operator> (enum OPERATOR op1, enum OPERATOR op2) {
	static int prior[][8] = {
		{ OP_SEMI },
		{ OP_OROR },
		{ OP_ANDAND },
		{ OP_EQUAL, OP_NOTEQ },
		{ OP_GREATER, OP_SMALLER, OP_NGREATER, OP_NSMALLER },
		{ OP_PLUS, OP_MINUS },
		{ OP_MULTY, OP_DIVIDE },
		{ OP_LBRACE },
		{ OP_RBRACE }
	};
	int p1, p2;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 8; j++) {
			if (prior[i][j] == op1)p1 = i;
			if (prior[i][j] == op2)p2 = i;
		}
	}
	return p1 > p2;
}

Syntax::Syntax(std::vector<char *>ids, std::vector<tokenPrim>input) {
	content = input;
	strId = ids;
	step = QS_IDLE;
	proc = 0;
	if (content.size() == 0)return;
	if (content[content.size() - 1].type != TT_OP || content[content.size() - 1].id != OP_SEMI) {
		tokenPrim tmp = *new tokenPrim();
		tmp.type = TT_OP;
		tmp.id = OP_SEMI;
		content.push_back(tmp);
	}
}
Syntax::~Syntax() {

}

char *Syntax::opStr(int id) {
	switch (id) {
	case OP_PLUS: return "+";
	case OP_PLUSPLUS: return "++";
	case OP_EQPLUS: return "+=";
	case OP_MINUS: return "-";
	case OP_MINUSMINUS: return "--";
	case OP_EQMINUS: return "-=";
	case OP_MULTY: return "*";
	case OP_EQMULTY: return "*=";
	case OP_DIVIDE: return "/";
	case OP_EQDIVIDE: return "/=";
	case OP_AND: return "&";
	case OP_ANDAND: return "&&";
	case OP_EQAND: return "&=";
	case OP_OR: return "|";
	case OP_OROR: return "||";
	case OP_EQOR: return "|=";
	case OP_NOR: return "^";
	case OP_EQNOR: return "^=";
	case OP_INVERSE: return "~";
	case OP_EQINVERSE: return "~=";
	case OP_LBRACE: return "(";
	case OP_RBRACE: return ")";
	case OP_LPARENTHESIS: return "[";
	case OP_RPARENTHESIS: return "]";
	case OP_LBRAKET: return "{";
	case OP_RBRAKET: return "}";
	case OP_SEMI: return ";";
	case OP_COMMA: return ",";
	case OP_DOT: return ".";
	case OP_SMALLER: return "<";
	case OP_NSMALLER: return ">=";
	case OP_GREATER: return ">";
	case OP_NGREATER: return "<=";
	case OP_NOT: return "!";
	case OP_NOTEQ: return "!=";
	case OP_EQUAL: return "=";
	case OP_QUERY: return "?";
	case OP_QUOT: return "\'";
	case OP_DBQUOT: return "\"";
	default: return "";
	}
}
char *Syntax::valueStr(float value) {
	char *rt = (char *)malloc(20);
	sprintf(rt, "%f", value);
	return rt;
}

queryNode *Syntax::parse() {
	queryNode *rt = new queryNode();
	std::vector<std::string> *obj = new std::vector<std::string>();
	if (proc == content.size()) {
		if (step == QS_COMPLETE || step == QS_SELECTT || step == QS_IDLE) {
			delete rt;
			return NULL;
		}
		else
			error("", SE_INCOMPLETE);
	}
	switch (content[proc].type) {
	case TT_SYS:
		switch (step) {
		case QS_IDLE:
			rt->value = NULL;
			if (content[proc].id < ID_CREATE || content[proc].id > ID_USE)
				error(strId[content[proc].id], SE_PRELESS);
			rt->type = QUERYTYPE(content[proc].id - 4);
			step = QUERYSTEP(rt->type + 1);
			proc++;
			rt->left = parse();
			rt->right = parse();
			break;
		case QS_CREATE:
			rt->value = NULL;
			if (content[proc].id == ID_INDEX) {
				rt->type = QT_INDEX;
				step = QS_CREATEIDX;
				proc++;
				break;
			}
			if (content[proc].id < ID_DATABASE || content[proc].id > ID_TABLE)
				error(strId[content[proc].id], SE_PRELESS);
			rt->type = QUERYTYPE(content[proc].id - 4);
			step = QUERYSTEP(rt->type + 1);
			proc++;
			break;
		case	QS_CREATEDB:
		case QS_CREATET:
			error(strId[content[proc].id], SE_USERID);
		case QS_DROP:
			rt->value = NULL;
			if (content[proc].id < ID_DATABASE || content[proc].id > ID_TABLE)
				error(strId[content[proc].id], SE_PRELESS);
			rt->type = QUERYTYPE(content[proc].id - 4);
			step = QUERYSTEP(rt->type + 3);
			proc++;
			break;
		case	QS_DROPDB:
		case QS_DROPT:
			error(strId[content[proc].id], SE_USERID);
		case QS_INSERTT:
			if (content[proc].id != ID_VALUES)
				error(strId[content[proc - 1].id], SE_PRELESS);
			else {
				proc++;
				if (content[proc].type != TT_OP || content[proc].id != OP_LBRACE)
					error(strId[content[proc - 1].id], SE_INCOMPLETE);
				rt->type = QT_TABLE;
				rt->left = new queryNode();
				rt->left->type = QT_ATTRIB;
				rt->left->value = new entityNode(ET_ATTRIB, new std::vector<entityNode*>);
				int idx = 0;
				proc++;
				while (content[proc].type != TT_OP || content[proc].id != OP_RBRACE) {
					if(content[proc].type==TT_DATA) {
						if (content[proc].s) {
							((std::vector<entityNode*>*)(rt->left->value->ptr))->push_back(new entityNode
							(ET_CHARN, content[proc].s));
						}
						else {
							((std::vector<entityNode*>*)(rt->left->value->ptr))->push_back(new entityNode
								(int(content[proc].value) == content[proc].value ? ET_INTEGER : ET_FLOAT,
								new float(content[proc].value)));
						}
					}
					proc++;
					if (content[proc].type == TT_OP && content[proc].id == OP_RBRACE) {
						proc++;
						break;
					}
					if (content[proc].type != TT_OP || content[proc].id != OP_COMMA)
						error(strId[content[proc - 1].id], SE_EXPCOMMA);
					else proc++;
				}
				step = QS_COMPLETE;
			}
			break;
		case QS_INSERT:
			if (content[proc].id != ID_INTO)
				error(strId[content[proc].id], SE_PRELESS);
			else {
				proc++;
				delete rt;
				return parse();
			}
		case QS_SELECT:
		case QS_ALTERT:
		case QS_UPDATE:
		case QS_USE:
		case QS_CREATEIDX:
			error(strId[content[proc].id], SE_USERID);
		case QS_DELETE:
			if (content[proc].id != ID_FROM)
				error(strId[content[proc].id], SE_PRELESS);
			proc++;
			if (content[proc].type != TT_USER)
				error(strId[content[proc].id], SE_USERID);
			else {
				rt->type = QT_TABLE;
				rt->value = new entityNode(ET_TABLE, strId[content[proc].id]);
				step = QS_DELETET;
				proc++;
			}
			break;
		case QS_DELETET:
			if (content[proc].id != ID_WHERE)
				error(strId[content[proc].id], SE_PRELESS);
			else {
				proc++;
				return expression(&proc, rt);
			}
			break;
		case QS_SELECTA:
			if (content[proc].id != ID_FROM)
				error(strId[content[proc].id], SE_PRELESS);
			else {
				proc++;
				step = QS_SELECTF;
				rt = parse();
			}
			break;
		case QS_SELECTT:
			if (content[proc].id != ID_WHERE)
				error(strId[content[proc].id], SE_PRELESS);
			else {
				proc++;
				return expression(&proc, rt);
			}
		case QS_SELECTF:
			if (content[proc].id != ID_SELECT)
				error(strId[content[proc].id], SE_PRELESS);
			else {
				rt->type = QT_SELECT;
				rt->value = NULL;
				step = QS_SELECT;
				proc++;
				rt->left = parse();
				rt->right = parse();
			}
			break;
		case QS_ALTER:
			rt->value = NULL;
			if (content[proc].id != ID_TABLE || content[proc].type != TT_SYS)
				error(strId[content[proc].id], SE_PRELESS);
			rt->type = QT_TABLE;
			step = QS_ALTERT;
			proc++;
			break;
		case QS_UPDATET:
			error(strId[content[proc].id], SE_PRELESS);
		case QS_COMPLETE:
			error(strId[content[proc].id], SE_EXPSEMI);
		}
		break;
	case TT_USER:
		switch (step) {
		case QS_IDLE:
		case	QS_CREATE:
		case QS_DROP:
		case QS_ALTER:
			error(strId[content[proc].id], SE_PRELESS);
		case QS_UPDATE:
		case QS_UPDATET:
			error("Update", SE_UNSUPPORT);
		case QS_CREATEDB:
			rt->value = new entityNode(ET_DATABASE, strId[content[proc].id]);
			rt->type = QT_DATABASE;
			step = QS_COMPLETE;
			proc++;
			break;
		case QS_CREATET:
			rt->value = new entityNode(ET_TABLE, strId[content[proc].id]);
			proc++;
			if (content[proc].type != TT_OP || content[proc].id != OP_LBRACE)
				error(strId[content[proc - 1].id], SE_INCOMPLETE);
			else {
				proc++;
				rt->type = QT_TABLE;
				rt->value = new entityNode(ET_TABLE, strId[content[proc - 2].id]);
				rt->left = new queryNode();
				rt->left->type = QT_ATTRIB;
				rt->left->value = new entityNode(ET_ATTRIB, new std::vector<entityNode*>);
				while (content[proc].type != TT_OP || content[proc].id != OP_RBRACE) {
					if (content[proc].type == TT_USER&&content[proc + 1].type == TT_SYS&&
						content[proc + 1].id <= ID_NULL) {
						((std::vector<entityNode*>*)(rt->left->value->ptr))->push_back(
							new entityNode(content[proc + 1].id + 3, strId[content[proc].id]));
						if (content[proc + 1].id == ID_CHAR &&
							content[proc + 2].type == TT_OP&&content[proc + 2].id == OP_LBRACE) {
							proc += 3;
							if (content[proc + 1].type != TT_OP || content[proc + 1].id != OP_RBRACE)
								error("", SE_EXPBRACE);
						}
						proc += 2;
						if (content[proc].type == TT_SYS && content[proc].id == ID_PRIMARY) {
							if (content[proc + 1].type == TT_SYS && content[proc + 1].id == ID_KEY) {
								rt->right = new queryNode();
								rt->right->type = QT_PK;
								rt->right->value = new entityNode(ET_INTEGER,
									new int(((std::vector<entityNode*>*)(rt->left->value->ptr))->size() - 1));
								proc += 2;
							}
							else error("Primary key", SE_PRELESS);
						}
						if (content[proc].type == TT_OP && content[proc].id == OP_RBRACE) {
							proc++;
							break;
						}
						if (content[proc].type != TT_OP || content[proc].id != OP_COMMA)
							error(strId[content[proc - 1].id], SE_EXPCOMMA);
						else proc++;
					}
					else error("Create table", SE_INCOMPLETE);
				}
				step = QS_COMPLETE;
			}
			break;
		case QS_CREATEIDX:
			rt->type = QT_INDEX;
			rt->value = new entityNode(ET_INDEX, strId[content[proc].id]);
			proc++;
			if (content[proc].type != TT_SYS || content[proc].id != ID_ON)
				error("Create index", SE_PRELESS);
			proc++;
			rt->left = new queryNode();
			if (content[proc].type != TT_USER)
				error("Create index", SE_PRELESS);
			rt->left->type = QT_TABLE;
			rt->left->value = new entityNode(ET_TABLE, strId[content[proc].id]);
			proc++;
			proc++;
			rt->right = new queryNode();
			if (content[proc].type != TT_USER)
				error("Create index", SE_PRELESS);
			rt->right->type = QT_ATTRIB;
			rt->right->value = new entityNode(ET_ATTRIB, strId[content[proc].id]);
			step = QS_COMPLETE;
			proc++;
			proc++;
			break;
		case QS_DROPDB:
			rt->value = new entityNode(ET_DATABASE, strId[content[proc].id]);
			rt->type = QT_DATABASE;
			step = QS_COMPLETE;
			proc++;
			break;
		case QS_DROPT:
			rt->value = new entityNode(ET_TABLE, strId[content[proc].id]);
			rt->type = QT_TABLE;
			step = QS_COMPLETE;
			proc++;
			break;
		case QS_USE:
			rt->value = new entityNode(ET_DATABASE, strId[content[proc].id]);
			rt->type = QT_DATABASE;
			step = QS_COMPLETE;
			proc++;
			break;
		case QS_INSERT:
			rt->type = QT_TABLE;
			rt->value = new entityNode(ET_TABLE, strId[content[proc].id]);
			step = QS_INSERTT;
			proc++;
			break;
		case QS_INSERTT:
			error(strId[content[proc].id], SE_PRELESS);
		case QS_SELECT:
			rt->type = QT_ATTRIB;
			while (content[proc].type != TT_SYS || content[proc].id != ID_FROM) {
				if (content[proc].type == TT_USER) {
					obj->push_back(strId[content[proc].id]);
					proc++;
				}
				else if (content[proc].type == TT_OP&&content[proc].id == OP_COMMA)
					proc++;
				else error("", SE_INCOMPLETE);
			}
			rt->value = new entityNode(ET_ATTRIB, obj);
			step = QS_SELECTA;
			break;
		case QS_DELETE:
		case QS_DELETET:
			error("", SE_UNKNOWN);
		case QS_SELECTA:
		case QS_SELECTT:
			error(strId[content[proc].id], SE_PRELESS);
		case QS_SELECTF:
			rt->type = QT_TABLE;
			rt->value = new entityNode(ET_TABLE, strId[content[proc].id]);
			step = QS_SELECTT;
			proc++;
			rt->left = new queryNode();
			rt->left->type = QT_WHERE;
			rt->right = parse();
			break;
		case QS_ALTERT:
			rt->value = new entityNode(ET_TABLE, strId[content[proc].id]);
			proc++;
			if (content[proc].type != TT_OP || content[proc].id != OP_LBRACE)
				error(strId[content[proc - 1].id], SE_INCOMPLETE);
			else {
				proc++;
				rt->type = QT_TABLE;
				rt->value = new entityNode(ET_TABLE, strId[content[proc - 2].id]);
				rt->left = new queryNode();
				rt->left->type = QT_ATTRIB;
				rt->left->value = new entityNode(ET_ATTRIB, new std::vector<entityNode*>);
				while (content[proc].type != TT_OP || content[proc].id != OP_RBRACE) {
					if (content[proc].type == TT_USER&&content[proc + 1].type == TT_SYS&&
						content[proc + 1].id <= ID_NULL) {
						((std::vector<entityNode*>*)(rt->left->value->ptr))->push_back(
							new entityNode(content[proc + 1].id + 3, strId[content[proc].id]));
						if (content[proc + 1].id == ID_CHAR &&
							content[proc + 2].type == TT_OP&&content[proc + 2].id == OP_LBRACE) {
							proc += 3;
							if (content[proc + 1].type != TT_OP || content[proc + 1].id != OP_RBRACE)
								error("", SE_EXPBRACE);
						}
						proc += 2;
						if (content[proc].type == TT_SYS && content[proc].id == ID_PRIMARY) {
							if (content[proc + 1].type == TT_SYS && content[proc + 1].id == ID_KEY) {
								rt->right = new queryNode();
								rt->right->type = QT_PK;
								rt->right->value = new entityNode(ET_INTEGER,
									new int(((std::vector<entityNode*>*)(rt->left->value->ptr))->size() - 1));
								proc += 2;
							}
							else error("Primary key", SE_PRELESS);
						}
						if (content[proc].type == TT_OP && content[proc].id == OP_RBRACE) {
							proc++;
							break;
						}
						if (content[proc].type != TT_OP || content[proc].id != OP_COMMA)
							error(strId[content[proc - 1].id], SE_EXPCOMMA);
						else proc++;
					}
					else error("Alter table", SE_INCOMPLETE);
				}
				step = QS_COMPLETE;
			}
			break;
		case QS_COMPLETE:
			error(strId[content[proc].id], SE_EXPSEMI);
		}
		break;
	case TT_OP:
		switch (step) {
		case QS_IDLE:
		case	QS_CREATE:
		case	QS_CREATEDB:
		case	QS_CREATET:
		case QS_DROP:
		case QS_DROPDB:
		case QS_DROPT:
		case QS_INSERT:
		case QS_INSERTT:
		case QS_SELECTA:
		case QS_SELECTF:
		case QS_DELETE:
		case QS_DELETET:
		case QS_ALTER:
		case QS_ALTERT:
		case QS_UPDATE:
		case QS_UPDATET:
		case QS_USE:
		case QS_CREATEIDX:
			error(opStr(content[proc].id), SE_PRELESS);
			break;
		case QS_SELECT:
			if(content[proc].id!=OP_MULTY)
				error(opStr(content[proc].id), SE_PRELESS);
			else {
				rt->type = QT_ATTRIB;
				rt->value = new entityNode(ET_ATTRIB, NULL);
				step = QS_SELECTA;
				proc++;
			}
			break;
		case QS_SELECTT:
			if (content[proc].id != OP_SEMI) {
				error(opStr(content[proc].id), SE_EXPSEMI);
			}
			delete rt;
			return NULL;
		case QS_COMPLETE:
			if (content[proc].id != OP_SEMI) {
				error(opStr(content[proc].id), SE_EXPSEMI);
			}
			else {
				delete rt;
				return NULL;
			}
		}
		break;
	case TT_DATA:
		switch (step) {
		case QS_IDLE:
		case	QS_CREATE:
		case	QS_CREATEDB:
		case	QS_CREATET:
		case QS_DROP:
		case QS_DROPDB:
		case QS_DROPT:
		case QS_INSERT:
		case QS_INSERTT:
		case QS_SELECT:
		case QS_SELECTA:
		case QS_SELECTT:
		case QS_SELECTF:
		case QS_DELETE:
		case QS_DELETET:
		case QS_ALTER:
		case QS_ALTERT:
		case QS_UPDATE:
		case QS_UPDATET:
		case QS_USE:
		case QS_CREATEIDX:
			error(valueStr(content[proc].value), SE_PRELESS);
			break;
		case QS_COMPLETE:
			error(strId[content[proc].id], SE_EXPSEMI);
		}
		break;
	}
	return rt;
}
queryNode *Syntax::expression(int *proc, queryNode *root) {
	static std::vector<enum OPERATOR> status;
	static std::vector<queryNode *> rslt;
	if (rslt.size() == 0)rslt.push_back(NULL);

	if (*proc >= (int)content.size())return NULL;

	queryNode *node = new queryNode();
	switch (content[*proc].type) {
	case TT_OP:
		node->type = QT_VALUE;
		switch (content[*proc].id) {
		case OP_SEMI:
			return root;
		case OP_LBRACE:
			rslt.push_back(NULL);
			status.push_back(OP_LBRACE);
			node = expression(&(++*proc), root);
			if (rslt[rslt.size() - 1] == NULL) {
				rslt[rslt.size() - 1] = node;
				queryNode *tmp;
				while (tmp = expression(&(++*proc), rslt[rslt.size() - 1]))
					rslt[rslt.size() - 1] = tmp;
				queryNode *rt = rslt[rslt.size() - 1];
				rslt.pop_back();
				return rt;
			}
			else {
				return node;
			}
			break;
		case OP_RBRACE:
			status.pop_back();
			return root;
		case OP_PLUS:
		case OP_MINUS:
		case OP_MULTY:
		case OP_DIVIDE:
			node->value = new entityNode(ET_FLOAT, NULL);
			node->op = (OPERATOR)content[*proc].id;
			break;
		case OP_EQUAL:
		case OP_NOTEQ:
		case OP_GREATER:
		case OP_NGREATER:
		case OP_SMALLER:
		case OP_NSMALLER:
		case OP_ANDAND:
		case OP_OROR:
			node->value = new entityNode(ET_BOOL, NULL);
			node->op = (OPERATOR)content[*proc].id;
			break;
		}
		node->left = root;
		root = node;
		status.push_back((OPERATOR)content[*proc].id);
		root->right = expression(&(++*proc), root->right);
		++*proc;
		while (content[*proc].type == TT_OP && operator>((OPERATOR)content[*proc].id, status[status.size() - 1])) {
			root->right = expression(proc, root->right);
			if (content[*proc].type == TT_OP&&content[*proc].id == OP_RBRACE) {
				status.pop_back();
				return root;
			}
			++*proc;
			if (*proc >= (int)content.size())break;
		}
		if(content[*proc - 1].type != TT_OP || content[*proc - 1].id != OP_RBRACE)
			--*proc;
		status.pop_back();
		break;
	case TT_DATA:
		node->type = QT_VALUE;
		if(content[*proc].s)
			node->value = new entityNode(ET_CHARN, strId[content[*proc].id]);
		else
			node->value = new entityNode(ET_FLOAT, new float(content[*proc].value));
		if (rslt[rslt.size() - 1] == NULL) {
			rslt[rslt.size() - 1] = node;
			queryNode *tmp;
			while (tmp = expression(&(++*proc), rslt[rslt.size() - 1])) {
				rslt[rslt.size() - 1] = tmp;
				if (content[*proc].type == TT_OP && content[*proc].id == OP_RBRACE)
					break;
				if (content[*proc - 1].type == TT_OP && content[*proc - 1].id == OP_RBRACE)
					*proc--;
			}
			queryNode *rt = rslt[rslt.size() - 1];
			rslt.pop_back();
			return rt;
		}
		else {
			return node;
		}
		break;
	case TT_USER:
		node->type = QT_VALUE;
		node->value = new entityNode(ET_USER, strId[content[*proc].id]);
		if (rslt[rslt.size() - 1] == NULL) {
			rslt[rslt.size() - 1] = node;
			queryNode *tmp;
			while (tmp = expression(&(++*proc), rslt[rslt.size() - 1])) {
				rslt[rslt.size() - 1] = tmp;
				if (content[*proc].type == TT_OP && content[*proc].id == OP_RBRACE)
					break;
				if ((content[*proc - 1].type == TT_OP && content[*proc - 1].id == OP_RBRACE)&&
					!(content[*proc].type == TT_OP && content[*proc].id == OP_SEMI))
					--*proc;
			}
			queryNode *rt = rslt[rslt.size() - 1];
			rslt.pop_back();
			return rt;
		}
		else {
			return node;
		}
		break;
	default:
		error(strId[content[*proc].id], SE_PRELESS);
	}
	return root;
}
void Syntax::error(const char *inst, int type) {
	switch (type) {
	case SE_INCOMPLETE:
		throw new SyntaxException(std::string(inst) + "语句不完整");
	case SE_PRELESS:
		throw new SyntaxException(std::string(inst) + "无此语法");
	case SE_USERID:
		throw new SyntaxException(std::string(inst) + "非用户标识符");
	case SE_EXPSEMI:
		throw new SyntaxException(std::string(inst) + "缺少分号");
	case SE_EXPCOMMA:
		throw new SyntaxException(std::string(inst) + "缺少逗号");
	case SE_EXPBRACE:
		throw new SyntaxException(std::string(inst) + "括号配对错误");
	case SE_REDEF:
		throw new SyntaxException(std::string(inst) + "重定义");
	case SE_INVALIDTYPE:
		throw new SyntaxException(std::string(inst) + "操作对象类型错误");
	case SE_UNKNOWN:
		throw new SyntaxException(std::string(inst) + "未知错误");
	case SE_UNSUPPORT:
		throw new SyntaxException(std::string(inst) + "暂不支持");
	}
}
