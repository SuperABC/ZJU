#pragma once
#include <stdio.h>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/matrix.hpp"
class cam_coord_system {
private:
	glm::mat4	matcam, matP, invmatP;
	glm::vec3	campos;
public:
	void init(const glm::mat4 &mcam, const glm::mat4 &mP) {
	//printf_s("%f %f %f %f\n", mcam._11, mcam._12, mcam._13, mcam._14);
	//printf_s("%f %f %f %f\n", mcam._21, mcam._22, mcam._23, mcam._24);
	//printf_s("%f %f %f %f\n", mcam._31, mcam._32, mcam._33, mcam._34);
	//printf_s("%f %f %f %f\n", mcam._41, mcam._42, mcam._43, mcam._44);
	//printf_s("%f %f %f %f\n", mP._11, mP._12, mP._13, mP._14);
	//printf_s("%f %f %f %f\n", mP._21, mP._22, mP._23, mP._24);
	//printf_s("%f %f %f %f\n", mP._31, mP._32, mP._33, mP._34);
	//printf_s("%f %f %f %f\n", mP._41, mP._42, mP._43, mP._44);

	matcam = mcam;
	matP = mP;
	invmatP = glm::inverse(matP);
	campos = glm::vec3(invmatP * glm::vec4(0, 0, 0, 1));
}
	void get_campos(glm::vec3 &pos) const {
		pos = campos;
	}
	void gen_ray(glm::vec3 &dir, const glm::vec2 &raycoord) const {
		glm::vec3 pdir;
		pdir.x = (raycoord.x - matcam[2][0]) / matcam[0][0];
		pdir.y = (raycoord.y - matcam[2][1]) / matcam[1][1];
		pdir.z = 1;
		pdir = glm::vec3(invmatP * glm::vec4(pdir, 1));
		dir = pdir - campos;
		dir /= dir.length();
	}
	void project(glm::vec2 &imgcoord, const glm::vec3 &p) const {
		glm::vec3 q = glm::vec3(matP*glm::vec4(p, 1));
		q.x /= q.z;
		q.y /= q.z;

		imgcoord.x = q.x*matcam[0][0] + matcam[2][0];
		imgcoord.y = q.y*matcam[1][1] + matcam[2][1];
	}

	void load(FILE *fp) {
		glm::mat4	 m, mp;
		fscanf_s(fp, "%g %g %g %g ", &m[0][0], &m[1][0], &m[2][0], &m[3][0]);
		fscanf_s(fp, "%g %g %g %g ", &m[0][1], &m[1][1], &m[2][1], &m[3][1]);
		fscanf_s(fp, "%g %g %g %g ", &m[0][2], &m[1][2], &m[2][2], &m[3][2]);
		fscanf_s(fp, "%g %g %g %g ", &m[0][3], &m[1][3], &m[2][3], &m[3][3]);
		fscanf_s(fp, "%g %g %g %g ", &mp[0][0], &mp[1][0], &mp[2][0], &mp[3][0]);
		fscanf_s(fp, "%g %g %g %g ", &mp[0][1], &mp[1][1], &mp[2][1], &mp[3][1]);
		fscanf_s(fp, "%g %g %g %g ", &mp[0][2], &mp[1][2], &mp[2][2], &mp[3][2]);
		fscanf_s(fp, "%g %g %g %g ", &mp[0][3], &mp[1][3], &mp[2][3], &mp[3][3]);
		fscanf_s(fp, "\n");

		init(m, mp);
	}
};