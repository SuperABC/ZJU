#include <winsgl.h>
#include "lexeme.h"

void elementInput(widgetObj *w, int x, int y, int status) {
	mouseClickDefault(w, x, y, status);
	if (w->status&WIDGET_PASS) {
		if (strcmp((char *)w->content, "clear") == 0) {
			strcpy((char *)getWidgetByName("input")->content, "");
			return;
		}
		if (strcmp((char *)w->content, "ans") == 0) {
			return;
		}
		strcat((char *)getWidgetByName("input")->content, (char *)w->content);
	}
}
void calculate(widgetObj *w, int x, int y, int status) {
	mouseClickDefault(w, x, y, status);
	if (w->status&WIDGET_PASS) {

	}
}
void initWidgets() {
	widgetObj *b0, *bdot, *bcomma, *b1, *b2, *b3, *b4, *b5, *b6, *b7, *b8, *b9;
	widgetObj *bplus, *bminus, *bmulty, *bdevide, *blbrace, *brbrace;
	widgetObj *bexp, *blog, *broot, *bmod;
	widgetObj *input, *equal, *ans, *clear;
	widgetObj *base, *bin, *oct, *dec, *hex;

	input = newWidget(SG_INPUT, (SGstring)"input");
	input->pos.x = 40;
	input->pos.y = 20;
	input->size.x = 460;
	input->size.y = 60;
	strcpy((char *)input->content, "");
	registerWidget(input);
	free(input);

	equal = newWidget(SG_BUTTON, (SGstring)"equal");
	equal->pos.x = 520;
	equal->pos.y = 20;
	equal->size.x = 80;
	equal->size.y = 80;
	strcpy((char *)equal->content, "����");
	registerWidget(equal);
	free(input);

	b0 = newWidget(SG_BUTTON, (SGstring)"zero");
	b0->pos.x = 360;
	b0->pos.y = 390;
	b0->size.x = 60;
	b0->size.y = 60;
	strcpy((char *)b0->content, "0");
	b0->mouseClick = (mouseClickCall)elementInput;
	registerWidget(b0);
	free(b0);

	bcomma = newWidget(SG_BUTTON, (SGstring)"comma");
	bcomma->pos.x = 450;
	bcomma->pos.y = 390;
	bcomma->size.x = 60;
	bcomma->size.y = 60;
	strcpy((char *)bcomma->content, ",");
	bcomma->mouseClick = (mouseClickCall)elementInput;
	registerWidget(bcomma);
	free(b0);

	bdot = newWidget(SG_BUTTON, (SGstring)"point");
	bdot->pos.x = 540;
	bdot->pos.y = 390;
	bdot->size.x = 60;
	bdot->size.y = 60;
	strcpy((char *)bdot->content, ".");
	bdot->mouseClick = (mouseClickCall)elementInput;
	registerWidget(bdot);
	free(bdot);

	b1 = newWidget(SG_BUTTON, (SGstring)"one");
	b1->pos.x = 360;
	b1->pos.y = 300;
	b1->size.x = 60;
	b1->size.y = 60;
	strcpy((char *)b1->content, "1");
	b1->mouseClick = (mouseClickCall)elementInput;
	registerWidget(b1);
	free(b1);

	b2 = newWidget(SG_BUTTON, (SGstring)"two");
	b2->pos.x = 450;
	b2->pos.y = 300;
	b2->size.x = 60;
	b2->size.y = 60;
	strcpy((char *)b2->content, "2");
	b2->mouseClick = (mouseClickCall)elementInput;
	registerWidget(b2);
	free(b2);

	b3 = newWidget(SG_BUTTON, (SGstring)"three");
	b3->pos.x = 540;
	b3->pos.y = 300;
	b3->size.x = 60;
	b3->size.y = 60;
	strcpy((char *)b3->content, "3");
	b3->mouseClick = (mouseClickCall)elementInput;
	registerWidget(b3);
	free(b3);

	b4 = newWidget(SG_BUTTON, (SGstring)"four");
	b4->pos.x = 360;
	b4->pos.y = 210;
	b4->size.x = 60;
	b4->size.y = 60;
	strcpy((char *)b4->content, "4");
	b4->mouseClick = (mouseClickCall)elementInput;
	registerWidget(b4);
	free(b4);

	b5 = newWidget(SG_BUTTON, (SGstring)"five");
	b5->pos.x = 450;
	b5->pos.y = 210;
	b5->size.x = 60;
	b5->size.y = 60;
	strcpy((char *)b5->content, "5");
	b5->mouseClick = (mouseClickCall)elementInput;
	registerWidget(b5);
	free(b5);

	b6 = newWidget(SG_BUTTON, (SGstring)"six");
	b6->pos.x = 540;
	b6->pos.y = 210;
	b6->size.x = 60;
	b6->size.y = 60;
	strcpy((char *)b6->content, "6");
	b6->mouseClick = (mouseClickCall)elementInput;
	registerWidget(b6);
	free(b6);

	b7= newWidget(SG_BUTTON, (SGstring)"seven");
	b7->pos.x = 360;
	b7->pos.y = 120;
	b7->size.x = 60;
	b7->size.y = 60;
	strcpy((char *)b7->content, "7");
	b7->mouseClick = (mouseClickCall)elementInput;
	registerWidget(b7);
	free(b7);

	b8 = newWidget(SG_BUTTON, (SGstring)"eight");
	b8->pos.x = 450;
	b8->pos.y = 120;
	b8->size.x = 60;
	b8->size.y = 60;
	strcpy((char *)b8->content, "8");
	b8->mouseClick = (mouseClickCall)elementInput;
	registerWidget(b8);
	free(b8);

	b9 = newWidget(SG_BUTTON, (SGstring)"nine");
	b9->pos.x = 540;
	b9->pos.y = 120;
	b9->size.x = 60;
	b9->size.y = 60;
	strcpy((char *)b9->content, "9");
	b9->mouseClick = (mouseClickCall)elementInput;
	registerWidget(b9);
	free(b9);

	bplus = newWidget(SG_BUTTON, (SGstring)"plus");
	bplus->pos.x = 220;
	bplus->pos.y = 390;
	bplus->size.x = 60;
	bplus->size.y = 60;
	strcpy((char *)bplus->content, "+");
	bplus->mouseClick = (mouseClickCall)elementInput;
	registerWidget(bplus);
	free(bplus);

	bminus = newWidget(SG_BUTTON, (SGstring)"minus");
	bminus->pos.x = 220;
	bminus->pos.y = 300;
	bminus->size.x = 60;
	bminus->size.y = 60;
	strcpy((char *)bminus->content, "-");
	bminus->mouseClick = (mouseClickCall)elementInput;
	registerWidget(bminus);
	free(bminus);

	bmulty = newWidget(SG_BUTTON, (SGstring)"multy");
	bmulty->pos.x = 220;
	bmulty->pos.y = 210;
	bmulty->size.x = 60;
	bmulty->size.y = 60;
	strcpy((char *)bmulty->content, "*");
	bmulty->mouseClick = (mouseClickCall)elementInput;
	registerWidget(bmulty);
	free(bmulty);

	bdevide = newWidget(SG_BUTTON, (SGstring)"devide");
	bdevide->pos.x = 220;
	bdevide->pos.y = 120;
	bdevide->size.x = 60;
	bdevide->size.y = 60;
	strcpy((char *)bdevide->content, "/");
	bdevide->mouseClick = (mouseClickCall)elementInput;
	registerWidget(bdevide);
	free(bdevide);

	blbrace = newWidget(SG_BUTTON, (SGstring)"lbrace");
	blbrace->pos.x = 40;
	blbrace->pos.y = 120;
	blbrace->size.x = 60;
	blbrace->size.y = 60;
	strcpy((char *)blbrace->content, "(");
	blbrace->mouseClick = (mouseClickCall)elementInput;
	registerWidget(blbrace);
	free(blbrace);

	brbrace = newWidget(SG_BUTTON, (SGstring)"rbrace");
	brbrace->pos.x = 130;
	brbrace->pos.y = 120;
	brbrace->size.x = 60;
	brbrace->size.y = 60;
	strcpy((char *)brbrace->content, ")");
	brbrace->mouseClick = (mouseClickCall)elementInput;
	registerWidget(brbrace);
	free(brbrace);

	bexp = newWidget(SG_BUTTON, (SGstring)"exp");
	bexp->pos.x = 40;
	bexp->pos.y = 210;
	bexp->size.x = 60;
	bexp->size.y = 60;
	strcpy((char *)bexp->content, "exp");
	bexp->mouseClick = (mouseClickCall)elementInput;
	registerWidget(bexp);
	free(bexp);

	blog = newWidget(SG_BUTTON, (SGstring)"log");
	blog->pos.x = 130;
	blog->pos.y = 210;
	blog->size.x = 60;
	blog->size.y = 60;
	strcpy((char *)blog->content, "log");
	blog->mouseClick = (mouseClickCall)elementInput;
	registerWidget(blog);
	free(blog);

	broot = newWidget(SG_BUTTON, (SGstring)"root");
	broot->pos.x = 40;
	broot->pos.y = 300;
	broot->size.x = 60;
	broot->size.y = 60;
	strcpy((char *)broot->content, "root");
	broot->mouseClick = (mouseClickCall)elementInput;
	registerWidget(broot);
	free(broot);

	bmod = newWidget(SG_BUTTON, (SGstring)"mod");
	bmod->pos.x = 130;
	bmod->pos.y = 300;
	bmod->size.x = 60;
	bmod->size.y = 60;
	strcpy((char *)bmod->content, "mod");
	bmod->mouseClick = (mouseClickCall)elementInput;
	registerWidget(bmod);
	free(bmod);

	clear = newWidget(SG_BUTTON, (SGstring)"clear");
	clear->pos.x = 40;
	clear->pos.y = 390;
	clear->size.x = 60;
	clear->size.y = 60;
	strcpy((char *)clear->content, "clear");
	clear->mouseClick = (mouseClickCall)elementInput;
	registerWidget(clear);
	free(clear);

	ans = newWidget(SG_BUTTON, (SGstring)"ans");
	ans->pos.x = 130;
	ans->pos.y = 390;
	ans->size.x = 60;
	ans->size.y = 60;
	strcpy((char *)ans->content, "ans");
	ans->mouseClick = (mouseClickCall)elementInput;
	registerWidget(ans);
	free(ans);

	base = newWidget(SG_LABEL, (SGstring)"base");
	base->pos.x = 48;
	base->pos.y = 88;
	strcpy((char *)base->content, "base:");
	registerWidget(base);
	free(base);

	bin = newWidget(SG_CHECK, (SGstring)"bin");
	bin->pos.x = 100;
	bin->pos.y = 88;
	bin->size.x = 40;
	bin->size.y = 20;
	strcpy((char *)bin->content, "bin");
	registerWidget(bin);
	free(bin);

	oct = newWidget(SG_CHECK, (SGstring)"oct");
	oct->pos.x = 160;
	oct->pos.y = 88;
	oct->size.x = 40;
	oct->size.y = 20;
	strcpy((char *)oct->content, "oct");
	registerWidget(oct);
	free(oct);

	dec = newWidget(SG_CHECK, (SGstring)"dec");
	dec->pos.x = 220;
	dec->pos.y = 88;
	dec->size.x = 40;
	dec->size.y = 20;
	strcpy((char *)dec->content, "dec");
	registerWidget(dec);
	free(dec);

	hex = newWidget(SG_CHECK, (SGstring)"hex");
	hex->pos.x = 280;
	hex->pos.y = 88;
	hex->size.x = 40;
	hex->size.y = 20;
	strcpy((char *)hex->content, "hex");
	registerWidget(hex);
	free(hex);
}

void sgSetup() {
	initWindow(640, 480, "Calculator", BIT_MAP);
	initKey();
	initMouse(SG_COORDINATE);
	initWidgets();
}
void sgLoop() {
	static bool first = true;
	if (first) {
		setColor(223, 223, 223);
		clearScreen();
		first = false;
	}
}