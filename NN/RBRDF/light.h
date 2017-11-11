#pragma once
#include <windows.h>
#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/matrix.hpp"

const float LED_size = 4.75f;

glm::vec3 normalize(glm::vec3 v);
void LED_light_pos(glm::vec3 &pos, glm::vec3 &normal, glm::vec3 &tangent, const int x, const int y, const glm::mat4 &T) {
	glm::vec3 p(LED_size*x, LED_size*y, 0);
	glm::vec3 pn(LED_size*x, LED_size*y, -1);
	glm::vec3 pt(LED_size*x + 1, LED_size*y, 0);

	pos = glm::vec3(T*glm::vec4(p, 1));
	glm::vec3 posn = glm::vec3(T*glm::vec4(pn, 1));
	glm::vec3 post = glm::vec3(T*glm::vec4(pt, 1));

	normal = posn - pos;
	normal = normalize(normal);
	tangent = post - pos;
	tangent = normalize(tangent);
}
void convert_LED_idx(int &bb, int &xx, int &yy, const int idx) {
	int b, x, y;
	b = idx / (64 * 16);
	x = idx % 64;
	y = (idx / 64) % 16;

	switch (b)
	{
	case 0:
		bb = 2;
		xx = x;
		yy = (15 - y) + 16;
		break;
	case 1:
		bb = 4;
		xx = 63 - x;
		yy = y;
		break;
	case 2:
		bb = 3;
		xx = 63 - x;
		yy = y;
		break;
	case 3:
		bb = 5;
		xx = x;
		yy = (15 - y) + 16;
		break;
	case 4:
		bb = 0;
		xx = x;
		yy = 15 - y;
		break;
	case 5:
		bb = 1;
		xx = x;
		yy = 15 - y;
		break;
	case 6:
		bb = 2;
		xx = x;
		yy = 15 - y;
		break;
	case 7:
		bb = 4;
		xx = 63 - x;
		yy = y + 16;
		break;
	case 8:
		bb = 3;
		xx = 63 - x;
		yy = y + 16;
		break;
	case 9:
		bb = 5;
		xx = x;
		yy = 15 - y;
		break;
	}
}
float eval_light_distr(const float cos_theta, const glm::vec3 &inten_dist) {
	return __max(inten_dist.x*cos_theta*cos_theta + inten_dist.y*cos_theta + inten_dist.z, 0.f);
}

class light_system {
private:
	std::vector<glm::vec3>	pos, normal, tangent;
	glm::vec3	inten_dist;
	std::vector<glm::mat4> trans;

public:
	void init(const glm::vec3 &light_coef,
		const std::vector<glm::mat4> &transform) {
		inten_dist = light_coef;
		trans = transform;

		pos.clear();
		normal.clear();
		tangent.clear();

		for (int idx = 0; idx < 64 * 16 * 10; idx++) {
			int b, x, y;
			convert_LED_idx(b, x, y, idx);

			glm::vec3 p, n, t;
			LED_light_pos(p, n, t, x, y, transform[b]);
			pos.push_back(p);
			normal.push_back(n);
			tangent.push_back(t);
		}
	}

	void load(FILE *fp) {
		int num;
		fscanf_s(fp, "%d\n", &num);
		std::vector<glm::mat4> transform(num);
		for (int i = 0; i < transform.size(); i++)
		{
			fscanf_s(fp, "%g %g %g %g\n", &transform[i][0][0], &transform[i][1][0], &transform[i][2][0], &transform[i][3][0]);
			fscanf_s(fp, "%g %g %g %g\n", &transform[i][0][1], &transform[i][1][1], &transform[i][2][1], &transform[i][3][1]);
			fscanf_s(fp, "%g %g %g %g\n", &transform[i][0][2], &transform[i][1][2], &transform[i][2][2], &transform[i][3][2]);
			fscanf_s(fp, "%g %g %g %g\n", &transform[i][0][3], &transform[i][1][3], &transform[i][2][3], &transform[i][3][3]);
		}
		init(glm::vec3(0, 0, 0), transform);
	}

	int num_lights() const {
		return 64 * 16 * 10;
	}
	float eval_distr(const float cos_theta) const {
		return eval_light_distr(cos_theta, inten_dist);
	}
	void get_light(glm::vec3 &p, glm::vec3 &n, glm::vec3 &t, const int idx) const {
		p = pos[idx];
		n = normal[idx];
		t = tangent[idx];
	}
};