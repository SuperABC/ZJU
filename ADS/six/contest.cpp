#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;

struct Problem {
	string name;
	int codeTime;
	int debugTime;
	Problem(string n, int c, int d) : name(n), codeTime(c), debugTime(d) {};
};

vector<bool> finished;
vector<Problem> probs;
vector<int> stack;
vector<int> result;

int timeLimit, totalProbs, readTime;
int endNum, endTime;

void deepFirst(int num, int time, int score);
void updateRes(int num, int time);

int main() {
	string name;
	int code, debug;

	cin >> timeLimit;
	while (timeLimit > 0) {
		cin >> totalProbs >> readTime;
		endNum = endTime = 0;
		probs.clear();
		stack.clear();
		result.clear();
		finished.clear();

		for (int i = 0; i < totalProbs; i++) {
			cin >> name >> code >> debug;
			probs.push_back(Problem(name, code, debug));
			finished.push_back(false);
		}

		for (int i = 0; i < totalProbs; i++) {
			finished[i] = true;
			stack.push_back(i);
			deepFirst(0, readTime, 0);
			stack.pop_back();
			finished[i] = false;
		}

		cout << "Total Time = " << endTime << endl;
		for (auto &iter : result) {
			cout << probs[iter].name << endl;
		}

		cin >> timeLimit;
	}
	return 0;
}

void deepFirst(int num, int time, int score) {
	Problem tmpProb = probs[stack[stack.size() - 1]];
	int debug = (time + tmpProb.codeTime - 1) / 60;
	int preScore = score;
	time += tmpProb.codeTime + tmpProb.debugTime*debug;
	score += time + debug * 20;

	if (time <= 60 * timeLimit) {
		if (++num < totalProbs) {
			for (int i = 0; i < totalProbs; i++) {
				if (!finished[i]) {
					finished[i] = true;
					stack.push_back(i);
					deepFirst(num, time, score);
					stack.pop_back();
					finished[i] = false;
				}
			}
		}
		else updateRes(num, score);
	}
	else updateRes(num, preScore);
}
void updateRes(int num, int score) {
	if (num < endNum) return;
	else if (num == endNum && score >= endTime) return;

	endNum = num;
	endTime = score;
	result.clear();
	for (int i = 0; i < num; i++) {
		result.push_back(stack[i]);
	}
}