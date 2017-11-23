#pragma once
#include <iostream>
#include <vector>
#include "camera.h"
#include "light.h"

#define LIGHT_SIZE 10240
#define PI 3.1415926535

glm::vec3 normalize(glm::vec3 v);
float length(glm::vec3 v);

class para_brdf {
private:
	float n1, n2, t, ax, ay, pd, ps;
	std::vector<float> brdf;

public:
	para_brdf() :
		n1(0), n2(0), t(0), ax(0), ay(0), pd(0), ps(0), brdf(std::vector<float>(LIGHT_SIZE)){}
	para_brdf(const float n1, const float n2, const float t_index,
		const float ax, const float ay, const float pd, const float ps,
		const std::vector<float>& brdf) :
		n1(n1), n2(n2), t(t_index), ax(ax), ay(ay), pd(pd), ps(ps), brdf(brdf) {}
	float *get_para() { return &n1; }
	std::vector<float> get_brdf() { return brdf; }

	void output(const int i) {
		std::cout << "n1 = " << n1 << " n2 = " << n2 << " t_rotate = " << t << " "
			<< "ax = " << ax << " ay = " << ay << " pd = " << pd << " ps = " << ps << std::endl
			<< "brdf[" << i << "] = " << brdf[i] << std::endl;
	}

	void write(FILE *fp) {
		fwrite(&n1, sizeof(float), 1, fp);
		fwrite(&n2, sizeof(float), 1, fp);
		fwrite(&t, sizeof(float), 1, fp);
		fwrite(&ax, sizeof(float), 1, fp);
		fwrite(&ay, sizeof(float), 1, fp);
		fwrite(&pd, sizeof(float), 1, fp);
		fwrite(&ps, sizeof(float), 1, fp);
		for (int i = 0; i < LIGHT_SIZE; i++) {
			fwrite(&brdf[i], sizeof(float), 1, fp);
		}
	}
	void read(FILE *fp) {
		fread(&n1, sizeof(float), 1, fp);
		fread(&n2, sizeof(float), 1, fp);
		fread(&t, sizeof(float), 1, fp);
		fread(&ax, sizeof(float), 1, fp);
		fread(&ay, sizeof(float), 1, fp);
		fread(&pd, sizeof(float), 1, fp);
		fread(&ps, sizeof(float), 1, fp);
		for (int i = 0; i < LIGHT_SIZE; i++) {
			fread(&brdf[i], sizeof(float), 1, fp);
		}
	}
};

void read_cam_and_light(const char* file,
	cam_coord_system& cam, light_system& light) {
	FILE *fp;
	fopen_s(&fp, file, "rt");
	cam.load(fp);
	light.load(fp);
	fclose(fp);
}
void compute_wiwo(const int u, const int v,
	const cam_coord_system& cam, const light_system& light,
	std::vector<glm::vec3>& wi, glm::vec3& wo) {
	glm::vec3 campos, dirc, pos;
	cam.get_campos(campos);
	cam.gen_ray(dirc, glm::vec2(u, v));
	float tmp = -campos.z / dirc.z;
	pos = campos + dirc*tmp;
	dirc = -dirc; // dir 指向相机位置

	wo = dirc;
	wi.resize(LIGHT_SIZE);
	for (int i = 0; i < LIGHT_SIZE; i++) {
		glm::vec3 lp, ln, lt;
		light.get_light(lp, ln, lt, i);
		wi[i] = lp - pos;
		wi[i] = normalize(wi[i]);
	}
}

void dimention_map(glm::vec3 &result, glm::vec2 &dir) {
	glm::vec2 p = (dir - glm::vec2(0.5f, 0.5f));
	p *= 2;

	result.x = (p.x + p.y) / 2;
	result.y = (p.y - p.x) / 2;
	result.z = 1 - abs(result.x) - abs(result.y);
	result = normalize(result);
}
void build_frame_f(const glm::vec3& n, glm::vec3& t, glm::vec3& b) {
	if (n.z != 1 && n.z != -1)
		t = glm::vec3(0, 0, 1);
	else
		t = glm::vec3(1, 0, 0);
	b = glm::cross(n, t);
	b = normalize(b);
	t = glm::cross(b, n);
}
void sample_T(const glm::vec3& n, const float rotate, glm::vec3& t) {
	glm::vec3 tangent, binormal;
	build_frame_f(n, tangent, binormal);
	t = (tangent *= cos(rotate * PI / 2)) + (binormal *= sin(rotate * PI / 2));
	t = normalize(t);
}
float form_factor(const glm::vec3& p, const glm::vec3& n,
	const glm::vec3& lp, const glm::vec3& ln) {
	glm::vec3 ldir = lp - p;
	float dist = length(ldir);
	ldir = normalize(ldir);
	return __max(glm::dot(ldir, n), 0.f)*__max(glm::dot(-ldir, ln), 0.f) / (dist*dist);
}
float ggx_G1_aniso(const glm::vec3& v, const float& ax, const float& ay) {
	if (v.z <= 0)
		return 0;

	glm::vec3 vv(v.x*ax, v.y*ay, v.z);
	return 2 * v.z / (v.z + length(vv));
}
float ggx_brdf_aniso(const glm::vec3 &wi, const glm::vec3 &wo, const float ax, const float ay) {
	assert(ax >= 0 && ay >= 0);

	if (wi.z <= 0 || wo.z <= 0)
		return 0;

	float denom = 4 * wi.z * wo.z;

	glm::vec3 vhalf = wi + wo;
	vhalf = normalize(vhalf);

	//F
	float F;
	{
		const float F0 = 0.04f;
		float temp = __min(__max(0, 1 - glm::dot(wi, vhalf)), 1);
		F = F0 + (1 - F0)*temp*temp*temp*temp*temp;
	}

	//D
	vhalf.x /= ax;
	vhalf.y /= ay;
	float len = length(vhalf)* length(vhalf);
	float D = 1.0f / (PI*ax*ay*len*len);

	return D*F*ggx_G1_aniso(wi, ax, ay)*ggx_G1_aniso(wo, ax, ay) / denom;
}
void light_brdf(const int u, const int v,
	const cam_coord_system& cam, const light_system& light,
	const float* params, std::vector<float>& brdf) {
	glm::vec3 campos, dirc, pos;
	cam.get_campos(campos);
	cam.gen_ray(dirc, glm::vec2(u, v));
	float tmp = -campos.z / dirc.z;
	pos = campos + dirc*tmp;
	dirc = -dirc; // dir 指向相机位置

	glm::vec3 n, t;
	dimention_map(n, glm::vec2(params[0], params[1]));
	sample_T(n, params[2], t);

	brdf.clear();
	brdf.resize(LIGHT_SIZE, 0);
	std::vector<glm::vec3> wi(LIGHT_SIZE);
	glm::vec3 b(glm::cross(n, t)), wo(glm::dot(dirc, t), glm::dot(dirc, b), glm::dot(dirc, n));
	wo = normalize(wo);

#pragma omp parallel for
	for (int i = 0; i < LIGHT_SIZE; i++) {
		glm::vec3 lp, ln, lt;
		light.get_light(lp, ln, lt, i);

		wi[i] = lp - pos;
		wi[i] = normalize(wi[i]);
		wi[i] = glm::vec3(glm::dot(wi[i], t), glm::dot(wi[i], b), glm::dot(wi[i], n));

		float factor = form_factor(pos, n, lp, ln);
		brdf[i] = factor * params[5] +
			ggx_brdf_aniso(wi[i], wo, params[3], params[4]) * factor * params[6];
	}
}
 