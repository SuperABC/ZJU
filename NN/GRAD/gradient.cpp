#include "gradient.h"
#include "time.h"

Grad::Grad(int paraNum, float initStep, float funcDiff, vector<float>(*predFunc)(vector<float> &para), bool debug, bool randGen, int maxRound,
	float(*lossFunc)(vector<float> &, vector<float> &), float(*miniStep)(float var, float step), bool(*breakCond)(float var)) {
	this->paraNum = paraNum;
	this->descStep = initStep;
	this->funcDiff = funcDiff;
	this->predFunc = predFunc;
	this->randGen = randGen;
	this->debug = debug;
	this->maxRound = maxRound;
	this->lossFunc = lossFunc;
	this->miniStep = miniStep;
	this->breakCond = breakCond;

	tmpPara = vector<float>(paraNum);
	resPara = vector<float>(paraNum);
	tmpDiff = vector<float>(paraNum);
	oldDiff = vector<float>(paraNum);
	tmpVel = vector<float>(paraNum);
	oldVel = vector<float>(paraNum);
	mostShrink = vector<int>(paraNum);
}

void Grad::prepare() {
	if (randGen)
		for (float &i : tmpPara)i = float(rand() % 11) / 10;
	else
		for (float &i : tmpPara)i = .5f;

	for (int i = 0; i < paraNum; i++) {
		tmpDiff[i] = oldDiff[i] = tmpVel[i] = oldVel[i] = resPara[i] = .0f;
		mostShrink[i] = 0;
	}

	tmpRound = 0;
}
void Grad::standard(vector<float> &std) {
	stdOpt = std;
}
long Grad::desc() {
	clock_t t = clock();

	while (1) {
		if(debug)print();
		calOpt = predFunc(tmpPara);
		tmpLoss = lossFunc(stdOpt, calOpt);
		if (tmpLoss < minLoss) {
			minLoss = tmpLoss;
			resPara = tmpPara;
			tmpRound = 0;
		}
		else {
			tmpRound++;
			if (tmpRound > maxRound)break;
		}

		for (int i = 0; i < paraNum; i++) {
			tmpPara[i] += funcDiff;
			calOpt = predFunc(tmpPara);
			tmpDiff[i] = (lossFunc(stdOpt, calOpt) - tmpLoss) / funcDiff;
			tmpPara[i] -= funcDiff;
			if (tmpPara[i] == 0.f&&tmpDiff[i] > 0)tmpDiff[i] = 0.f;
			if (tmpPara[i] == 1.f&&tmpDiff[i] < 0)tmpDiff[i] = 0.f;
			tmpDiff[i] /= 1 << (mostShrink[i] * 2);
		}

		float len = 0;
		for (float &d : tmpDiff)len += d*d;
		if (len == 0)break;
		len = sqrt(len);
		for (float &d : tmpDiff)d /= len;

		for (int i = 0; i < paraNum; i++) {
			if (oldDiff[i] > 0.5&&tmpDiff[i] < -0.5&&abs(oldDiff[i] + tmpDiff[i])<.01f)
				mostShrink[i]++;
			if (oldDiff[i] < 0.5&&tmpDiff[i] > -0.5&&abs(oldDiff[i] + tmpDiff[i])<.01f)
				mostShrink[i]++;

			oldDiff[i] = tmpDiff[i];
			oldVel[i] = tmpVel[i];
		}

		for (int i = 0; i < paraNum; i++) {
			tmpVel[i] = RATIO * tmpVel[i] - descStep * tmpDiff[i];
			tmpPara[i] += tmpVel[i] + RATIO * (tmpVel[i] - oldVel[i]);
			tmpPara[i] = clamp(0.f, 1.f, tmpPara[i]);
		}

		if(miniStep != NULL)descStep = miniStep(tmpLoss, descStep);
		if (breakCond != NULL && breakCond(tmpLoss))break;
	}
	return clock() - t;
}
void Grad::print() {
	for (float p : tmpPara)cout << p << " ";
	cout << endl;
}

float variant(vector<float> &std, vector<float> &cal) {
	float res = 0.f;

#pragma omp parallel for
	for (unsigned int i = 0; i < std.size(); i++) {
		res += (std[i] - cal[i])*(std[i] - cal[i]);
	}
	return res;
}
float clamp(float floor, float ceil, float d) {
	if (d < floor)return floor;
	if (d > ceil)return ceil;
	return d;
}