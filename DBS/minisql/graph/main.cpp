#include "main.h"
#include "../dbs/database.h"
#include "../dbs/index.h"
#include "../dbs/table.h"
#include "../parser/lexeme.h"
#include "../parser/syntax.h"
#include "../sgl/winsgl.h"

#pragma comment(lib, SG_LIB("sgl/winsgl"))

const static char *pre[] = { "create database zju;",
	"create database library;",
	"use zju;",
	"create table dalao(name char(10), age int, score int, gp float);",
	"insert dalao values('lbxdl', 19, 100, 4.99);",
	"insert dalao values('zz', 22, 100, 5.00);",
	"insert dalao values('ymys', 21, 90, 4.5);",
	"insert dalao values('gaoshen', 21, 101, 5.01);",
	"insert dalao values('ydh', 60, 99, 0);",
	"select name, gp from select * from dalao where name = 'gaoshen';" };

int dbNum = 0;
Database *db[MAXDB] = { 0 };

void loginChange(widgetObj *w, int x, int y, int status);
void executeQuery(widgetObj *w, int x, int y, int status);
void preExecute(const char *c);

void layoutLogin() {
	widgetObj *labelUser;
	widgetObj *inputUser;
	widgetObj *labelPw;
	widgetObj *inputPw;
	widgetObj *buttonLogin;

	labelUser = newWidget(SG_LABEL, SGstring("labelUser"));
	labelPw = newWidget(SG_LABEL, SGstring("labelPw"));
	labelUser->pos.x = 160;
	labelUser->pos.y = 160;
	labelPw->pos.x = 160;
	labelPw->pos.y = 200;
	strcpy((char *)labelUser->content, "ÓÃ»§Ãû£º");
	strcpy((char *)labelPw->content, "ÃÜÂë£º");
	registerWidget(labelUser);
	registerWidget(labelPw);
	free(labelUser);
	free(labelPw);

	buttonLogin = newWidget(SG_BUTTON, SGstring("buttonLogin"));
	buttonLogin->pos.x = 160;
	buttonLogin->pos.y = 240;
	buttonLogin->size.x = 320;
	buttonLogin->size.y = 80;
	strcpy((char *)buttonLogin->content, "µÇ    Â¼");
	buttonLogin->mouseClick = mouseClickCall(loginChange);
	registerWidget(buttonLogin);
	free(buttonLogin);

	inputPw = newWidget(SG_INPUT, SGstring("inputPw"));
	inputPw->pos.x = 220;
	inputPw->pos.y = 200;
	inputPw->size.x = 260;
	inputPw->size.y = 24;
	inputPw->associate = getWidgetByName("buttonLogin");
	registerWidget(inputPw);
	free(inputPw);

	inputUser = newWidget(SG_INPUT, SGstring("inputUser"));
	inputUser->pos.x = 220;
	inputUser->pos.y = 160;
	inputUser->size.x = 260;
	inputUser->size.y = 24;
	inputUser->associate = getWidgetByName("inputPw");
	registerWidget(inputUser);
	free(inputUser);

}
void layoutQuery() {
	widgetObj *input;
	widgetObj *query;
	widgetObj *output;
	widgetObj *error;

	ceaseWidget("labelUser");
	ceaseWidget("labelPw");
	ceaseWidget("inputUser");
	ceaseWidget("inputPw");
	ceaseWidget("buttonLogin");

	query = newWidget(SG_BUTTON, SGstring("query"));
	query->pos.x = 540;
	query->pos.y = 40;
	query->size.x = 60;
	query->size.y = 24;
	strcpy((char *)query->content, "Ö´ÐÐ");
	query->mouseClick = (mouseClickCall)executeQuery;
	registerWidget(query);
	free(query);

	input = newWidget(SG_INPUT, SGstring("input"));
	input->pos.x = 40;
	input->pos.y = 40;
	input->size.x = 480;
	input->size.y = 24;
	input->associate = getWidgetByName("query");
	registerWidget(input);
	free(input);

	output = newWidget(SG_OUTPUT, SGstring("output"));
	output->pos.x = 40;
	output->pos.y = 80;
	output->size.x = 560;
	output->size.y = 360;
	registerWidget(output);
	free(output);

	error = newWidget(SG_DIALOG, SGstring("error"));
	error->pos.x = 160;
	error->pos.y = 120;
	error->size.x = 320;
	error->size.y = 200;
	strcpy((char *)error->content, "Óï¾ä²»·ûºÏÒªÇó£¬Çë¼ì²é¡£");
	registerWidget(error);
	free(error);
}
void sgSetup() {
	initWindow(640, 480, "miniSQL", BIT_MAP);
	initKey();
	initMouse(SG_COORDINATE);
	layoutLogin();
	load();
}
void sgLoop() {
	return;
}

void loginChange(widgetObj *w, int x, int y, int status) {
	mouseClickDefault(w, x, y, status);
	if (w->status & WIDGET_SELECTED) {
		try {
			std::string loginUse = std::string("use _user;");
			std::string loginQuery = std::string("select * from account where ");

			Lexeme *parser1 = new Lexeme((const SGstring)loginUse.c_str());
			Syntax *querier1 = new Syntax(parser1->strId, parser1->parse());
			queryNode *q1 = querier1->parse();
			Database::create(q1, false);

			Lexeme *parser2 = new Lexeme(
				(const SGstring)(loginQuery + "id = '" +
				(char *)getWidgetByName("inputUser")->content +
					"' && password = '" +
					(char *)getWidgetByName("inputPw")->content + "';").c_str());
			Syntax *querier2 = new Syntax(parser2->strId, parser2->parse());
			queryNode *q2 = querier2->parse();
			for (int i = 0; i < MAXDB; i++) {
				if (db[i] && db[i]->focused()) {
					Table *rslt = db[i]->execute(q2, false);
					if (rslt->getTuple()->size()) {
						layoutQuery();
						return;
					}
				}
			}
		}
		catch (LexemeException) {
			return;
		}
		catch (SyntaxException) {
			return;
		}
	}
}
void executeQuery(widgetObj *w, int x, int y, int status) {
	mouseClickDefault(w, x, y, status);
	if (w->status & WIDGET_SELECTED) {
		try {
			Lexeme *parser = new Lexeme(getWidgetByName("input")->content);
			Syntax *querier = new Syntax(parser->strId, parser->parse());
			queryNode *q = querier->parse();
			if (!Database::create(q)) {
				for (int i = 0; i < MAXDB; i++) {
					if (db[i] && db[i]->focused()) {
						Table *rslt = db[i]->execute(q);
						if (rslt)Table::showTable(rslt);
						break;
					}
				}
			}
			for (int i = 0; i < 16; i++) {
				if (db[i])save(db[i]);
			}
		}
		catch (LexemeException *e) {
			strcpy((char *)getWidgetByName("error")->content, "´Ê·¨´íÎó£º\n");
			strcat((char *)getWidgetByName("error")->content, e->message());
			showWidget("error");
			delete e;
		}
		catch (SyntaxException *e) {
			strcpy((char *)getWidgetByName("error")->content, "Óï·¨´íÎó£º\n");
			strcat((char *)getWidgetByName("error")->content, e->message());
			showWidget("error");
			delete e;
		}
	}
}
void preExecute(const char *c) {
	try {
		Lexeme *parser = new Lexeme((const SGstring)c);
		Syntax *querier = new Syntax(parser->strId, parser->parse());
		queryNode *q = querier->parse();
		if (!Database::create(q)) {
			for (int i = 0; i < MAXDB; i++) {
				if (db[i] && db[i]->focused()) {
					Table *rslt = db[i]->execute(q);
					if (rslt)Table::showTable(rslt);
					break;
				}
			}
		}
		for (int i = 0; i < 16; i++) {
			if (db[i])save(db[i]);
		}
	}
	catch (LexemeException *e) {
		strcpy((char *)getWidgetByName("error")->content, "´Ê·¨´íÎó£º\n");
		strcat((char *)getWidgetByName("error")->content, e->message());
		showWidget("error");
		delete e;
	}
	catch (SyntaxException *e) {
		strcpy((char *)getWidgetByName("error")->content, "Óï·¨´íÎó£º\n");
		strcat((char *)getWidgetByName("error")->content, e->message());
		showWidget("error");
		delete e;
	}
}
