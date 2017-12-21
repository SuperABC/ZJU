#include "gradient.h"

vector<float> func(vector<float>& para) {
	vector<float> ret;
	for (float x = 0.f; x < 1.f; x += .1f) {
		for (float y = 0.f; y < 1.f; y += .1f) {
			for (float z = 0.f; z < 1.f; z += .1f) {
				ret.push_back(para[0] * x + para[1] * y + para[2] * z);
			}
		}
	}
	return ret;
}
float minimize(float var, float step) {
	if (var<.1f&&step>.001f)step /= 10;
	if (var<.001f&&step>.0001f)step /= 10;
	if (var<.00001f&&step>.00001f)step /= 10;
	return step;
}
bool quit(float var) {
	if (var < .00000001f)return true;
	else return false;
}

int main() {
	vector<float> p;
	p.push_back(.8f);
	p.push_back(.2f);
	p.push_back(.3f);
	vector<float> s = func(p);

	Grad grad(3, .01f, .0001f, func, true, true, 100, variant, minimize);
	grad.standard(s);
	grad.prepare();
	cout<<grad.desc();

	system("pause");
}