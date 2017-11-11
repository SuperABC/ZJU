#pragma once
#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/matrix.hpp"

#define DELTA 0.0001f
#define STEP .005f

extern cam_coord_system Cam;
extern light_system Light;

float clamp(float floor, float ceil, float d) {
	if (d < floor)return floor;
	if (d > ceil)return ceil;
	return d;
}
float variant(std::vector<float> &v1, std::vector<float> &v2) {
	float res = 0.f;
	for (int i = 0; i < LIGHT_SIZE; i++) {
		res += (v1[i] - v2[i])*(v1[i] - v2[i]);
	}
	return res;
}
void gradient(std::vector<glm::vec3> wi, glm::vec3 wo, std::vector<float> brdf, float *res) {
	float para[7] = { .1f, .4f, .1f, .2f, .1f, .1f, .1f };
	float dn1, dn2, dt, dax, day, dpd, dps;

	std::vector<float> tmp;
	float var, len;

	while (1) {
		light_brdf(1000, 1000, Cam, Light, para, tmp);
		var = variant(tmp, brdf);

		para[0] += DELTA;
		light_brdf(1000, 1000, Cam, Light, para, tmp);
		dn1 = (variant(tmp, brdf) - var) / DELTA;
		para[0] -= DELTA;
		para[1] += DELTA;
		light_brdf(1000, 1000, Cam, Light, para, tmp);
		dn2 = (variant(tmp, brdf) - var) / DELTA;
		para[1] -= DELTA;
		para[2] += DELTA;
		light_brdf(1000, 1000, Cam, Light, para, tmp);
		dt = (variant(tmp, brdf) - var) / DELTA;
		para[2] -= DELTA;
		para[3] += DELTA;
		light_brdf(1000, 1000, Cam, Light, para, tmp);
		dax = (variant(tmp, brdf) - var) / DELTA;
		para[3] -= DELTA;
		para[4] += DELTA;
		light_brdf(1000, 1000, Cam, Light, para, tmp);
		day = (variant(tmp, brdf) - var) / DELTA;
		para[4] -= DELTA;
		para[5] += DELTA;
		light_brdf(1000, 1000, Cam, Light, para, tmp);
		dpd = (variant(tmp, brdf) - var) / (DELTA * 20);
		para[5] -= DELTA;
		para[6] += DELTA;
		light_brdf(1000, 1000, Cam, Light, para, tmp);
		dps = (variant(tmp, brdf) - var) / DELTA;
		para[6] -= DELTA;

		if (para[0] == 0.f&&dn1 > 0)dn1 = 0;
		if (para[0] == 1.f&&dn1 < 0)dn1 = 0;
		if (para[1] == 0.f&&dn2 > 0)dn2 = 0;
		if (para[1] == 1.f&&dn2 < 0)dn2 = 0;
		if (para[2] == 0.f&&dt > 0)dt = 0;
		if (para[2] == 1.f&&dt < 0)dt = 0;
		if (para[3] == 0.f&&dax > 0)dax = 0;
		if (para[3] == 1.f&&dax < 0)dax = 0;
		if (para[4] == 0.f&&day > 0)day = 0;
		if (para[4] == 1.f&&day < 0)day = 0;
		if (para[5] == 0.f&&dpd > 0)dpd = 0;
		if (para[5] == 1.f&&dpd < 0)dpd = 0;
		if (para[6] == 0.f&&dps > 0)dps = 0;
		if (para[6] == 1.f&&dps < 0)dps = 0;

		len = sqrt(dn1*dn1 + dn2*dn2 + dt*dt + dax*dax + day*day + dpd*dpd + dps*dps);
		if (len == 0)break;
		dn1 /= len;
		dn2 /= len;
		dt /= len;
		dax /= len;
		day /= len;
		dpd /= len;
		dps /= len;

		para[0] -= dn1 * STEP;
		para[1] -= dn2 * STEP;
		para[2] -= dt * STEP;
		para[3] -= dax * STEP;
		para[4] -= day * STEP;
		para[5] -= dpd * STEP;
		para[6] -= dps * STEP;
		para[0] = clamp(0.f, 1.f, para[0]);
		para[1] = clamp(0.f, 1.f, para[1]);
		para[2] = clamp(0.f, 1.f, para[2]);
		para[3] = clamp(0.f, 1.f, para[3]);
		para[4] = clamp(0.f, 1.f, para[4]);
		para[5] = clamp(0.f, 1.f, para[5]);
		para[6] = clamp(0.f, 1.f, para[6]);

		std::cout << dn1 << " " << dn2 << " " << dt << " " << dax << " " << day << " " << dpd << " " << dps << std::endl <<
			para[0] << " " << para[1] << " " << para[2] << " " << para[3] << " " << para[4] << " " << para[5] << " " << para[6] << std::endl <<
			para[0] - .000f << " " << para[1] - .333f << " " << para[2] - .192f << " " << para[3] - .062f << " " << para[4] - .067f << " " << para[5] - .010f << " " << para[6] - .007f << std::endl <<
			var << std::endl << std::endl;
	}
}