#pragma once
#include <vector>
#include <iostream>

#define RATIO .8f

using std::cout;
using std::endl;
using std::vector;

float variant(vector<float> &std, vector<float> &cal);
float clamp(float floor, float ceil, float d);

class Grad {
public:
	Grad(int paraNum, float initStep, float funcDiff, vector<float>(*predFunc)(vector<float> &para),
		bool debug, bool randGen = true, int maxRound = INT_MAX,
		float(*lossFunc)(vector<float> &, vector<float> &) = variant,
		float(*miniStep)(float var, float step) = NULL, bool(*breakCond)(float var) = NULL);
	
	void prepare();
	void standard(vector<float> &std);
	long desc();
	void print();

private:
	bool randGen;
	bool debug;

	int paraNum;
	float funcDiff;
	float descStep;
	int tmpRound, maxRound;
	float tmpLoss, minLoss = INFINITY;

	vector<float> tmpPara, resPara;
	vector<float> tmpDiff, oldDiff;
	vector<float> tmpVel, oldVel;
	vector<int> mostShrink;

	vector<float> stdOpt, calOpt;
	vector<float> (*predFunc)(vector<float> &);
	float(*lossFunc)(vector<float> &, vector<float> &);
	float(*miniStep)(float var, float step);
	bool(*breakCond)(float var);
};

