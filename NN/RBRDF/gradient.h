#pragma once
#include <fstream>
#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/matrix.hpp"

#define DELTA 0.0001f
#define RATE .8f

extern cam_coord_system Cam;
extern light_system Light;

float para[7] = { .5f, .5f, .5f, .5f, .5f, .5f, .5f };

float clamp(float floor, float ceil, float d) {
	if (d < floor)return floor;
	if (d > ceil)return ceil;
	return d;
}
float variant(std::vector<float> &v1, std::vector<float> &v2) {
	float res = 0.f;

#pragma omp parallel for
	for (int i = 0; i < LIGHT_SIZE; i++) {
		res += (v1[i] - v2[i])*(v1[i] - v2[i]);
	}
	return res;
}
float expand(std::vector<float> &tmp, std::vector<float> &pre, std::vector<float> &std) {
	float res = 0.f;

#pragma omp parallel for
	for (int i = 0; i < LIGHT_SIZE; i++) {
		res += (pre[i] - std[i])*(tmp[i] - pre[i]);
	}
	return res;
}
bool gradient(std::vector<glm::vec3> &wi, glm::vec3 &wo, std::vector<float> &brdf, float *res, bool r = false) {
	float dn1, dn2, dt, dax, day, dpd, dps;
	float odn1 = 0, odn2 = 0, odt = 0, odax = 0, oday = 0, odpd = 0, odps = 0;
	float vn1 = 0, vn2 = 0, vt = 0, vax = 0, vay = 0, vpd = 0, vps = 0;
	float ovn1 = 0, ovn2 = 0, ovt = 0, ovax = 0, ovay = 0, ovpd = 0, ovps = 0;
	int pn1 = 0, pn2 = 0, pt = 0, pax = 0, pay = 0, ppd = 0, pps = 0;


	float step = 0.01f;

	std::vector<float> pre, tmp;
	float var, min = INFINITE, round = 0, len;

	if (r) {
		para[0] = para[1] = para[2] = para[3] = para[4] = para[5] = para[6] = (float(rand() % 10)) / 10;
	}
	else {
		para[0] = para[1] = para[2] = para[3] = para[4] = para[5] = para[6] = 0.5;
	}

	while (1) {
		light_brdf(1386, 1096, Cam, Light, para, pre);
		var = variant(pre, brdf);
		if (var < min) {
			min = var;
			memcpy(res, para, 7 * sizeof(float));
			round = 0;
		}
		else {
			round++;
			if (round > 100)break;
		}

		para[0] += DELTA;
		light_brdf(1386, 1096, Cam, Light, para, tmp);
		dn1 = (variant(tmp, brdf) - var) / DELTA;
		if (dn1 == 0) dn1 = expand(tmp, pre, brdf) / DELTA;
		para[0] -= DELTA;
		para[1] += DELTA;
		light_brdf(1386, 1096, Cam, Light, para, tmp);
		dn2 = (variant(tmp, brdf) - var) / DELTA;
		if (dn2 == 0) dn2 = expand(tmp, pre, brdf) / DELTA;
		para[1] -= DELTA;
		para[2] += DELTA;
		light_brdf(1386, 1096, Cam, Light, para, tmp);
		dt = (variant(tmp, brdf) - var) / DELTA;
		if (dt == 0) dt = expand(tmp, pre, brdf) / DELTA;
		para[2] -= DELTA;
		para[3] += DELTA;
		light_brdf(1386, 1096, Cam, Light, para, tmp);
		dax = (variant(tmp, brdf) - var) / DELTA;
		if (dax == 0) dax = expand(tmp, pre, brdf) / DELTA;
		para[3] -= DELTA;
		para[4] += DELTA;
		light_brdf(1386, 1096, Cam, Light, para, tmp);
		day = (variant(tmp, brdf) - var) / DELTA;
		if (day == 0) day = expand(tmp, pre, brdf) / DELTA;
		para[4] -= DELTA;
		para[5] += DELTA;
		light_brdf(1386, 1096, Cam, Light, para, tmp);
		dpd = (variant(tmp, brdf) - var) / (DELTA * 20);
		if (dpd == 0) dpd = expand(tmp, pre, brdf) / (DELTA * 20);
		para[5] -= DELTA;
		para[6] += DELTA;
		light_brdf(1386, 1096, Cam, Light, para, tmp);
		dps = (variant(tmp, brdf) - var) / DELTA;
		if (dps == 0) dps = expand(tmp, pre, brdf) / DELTA;
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

		if (pn1)dn1 /= 1 << (pn1 * 2);
		if (pn2)dn2 /= 1 << (pn2 * 2);
		if (pt)dt /= 1 << (pt * 2);
		if (pax)dax /= 1 << (pax * 2);
		if (pay)day /= 1 << (pay * 2);
		if (ppd)dpd /= 1 << (ppd * 2);
		if (pps)dps /= 1 << (pps * 2);

		len = sqrt(dn1*dn1 + dn2*dn2 + dt*dt + dax*dax + day*day + dpd*dpd + dps*dps);
		if (len == 0)break;
		dn1 /= len;
		dn2 /= len;
		dt /= len;
		dax /= len;
		day /= len;
		dpd /= len;
		dps /= len;

		if (odn1 > 0.5&&dn1 < -0.5&&abs(odn1 + dn1)<.01f)
			if (var<1e-11)pn1 += 3;
			else if (var < 5e-9)pn1 += 2;
			else pn1++;
		if (odn2 > 0.5&&dn2 < -0.5&&abs(odn2 + dn2)<.01f)
			if (var<1e-11)pn2 += 3;
			else if (var < 5e-9)pn2 += 2;
			else pn2++;
		if (odt > 0.5&&dt < -0.5&&abs(odt + dt)<.01f)
			if (var<1e-11)pt += 3;
			else if (var < 5e-9)pt += 2;
			else pt++;
		if (odax > 0.5&&dax < -0.5&&abs(odax + dax)<.01f)
			if (var<1e-11)pax += 3;
			else if (var < 5e-9)pax += 2;
			else pax++;
		if (oday > 0.5&&day < -0.5&&abs(oday + day)<.01f)
			if (var<1e-11)pay += 3;
			else if (var < 5e-9)pay += 2;
			else pay++;
		if (odpd > 0.5&&dpd < -0.5&&abs(odpd + dpd)<.01f)
			if (var<1e-11)ppd += 3;
			else if (var < 5e-9)ppd += 2;
			else ppd++;
		if (odps > 0.5&&dps < -0.5&&abs(odps + dps)<.01f)
			if (var<1e-11)pps += 3;
			else if (var < 5e-9)pps += 2;
			else pps++;

		odn1 = dn1;
		odn2 = dn2;
		odt = dt;
		odax = dax;
		oday = day;
		odpd = dpd;
		odps = dps;
		ovn1 = vn1;
		ovn2 = vn2;
		ovt = vt;
		ovax = vax;
		ovay = vay;
		ovpd = vpd;
		ovps = vps;

		vn1 = RATE * vn1 - step * dn1;
		vn2 = RATE * vn2 - step * dn2;
		vt = RATE * vt - step * dt;
		vax = RATE * vax - step * dax;
		vay = RATE * vay - step * day;
		vpd = RATE * vpd - step * dpd;
		vps = RATE * vps - step * dps;

		para[0] += vn1 + RATE * (vn1 - ovn1);
		para[1] += vn2 + RATE * (vn2 - ovn2);
		para[2] += vt + RATE * (vt - ovt);
		para[3] += vax + RATE * (vax - ovax);
		para[4] += vay + RATE * (vay - ovay);
		para[5] += vpd + RATE * (vpd - ovpd);
		para[6] += vps + RATE * (vps - ovps);
		para[0] = clamp(0.f, 1.f, para[0]);
		para[1] = clamp(0.f, 1.f, para[1]);
		para[2] = clamp(0.f, 1.f, para[2]);
		para[3] = clamp(0.f, 1.f, para[3]);
		para[4] = clamp(0.f, 1.f, para[4]);
		para[5] = clamp(0.f, 1.f, para[5]);
		para[6] = clamp(0.f, 1.f, para[6]);

		std::cout << dn1 << " " << dn2 << " " << dt << " " << dax << " " << day << " " << dpd << " " << dps << std::endl <<
			para[0] << " " << para[1] << " " << para[2] << " " << para[3] << " " << para[4] << " " << para[5] << " " << para[6] << std::endl <<
			var << std::endl << std::endl;

		if (var < 1e-11) {
			if (step == 0.01f)
				step = 0.001f;
		}
		if (var < 3e-13) {
			if (step == 0.001f)
				step = 0.0001f;
		}
		if (var < 5e-14)
			break;
	}
	if (var > 2e-13)return true;
	else {
		std::ofstream fouttmp, foutstd;
		fouttmp.open("outtmp.txt", 0);
		foutstd.open("outstd.txt", 0);
		for (int i = 0; i < LIGHT_SIZE; i++) {
			fouttmp << pre[i] << std::endl;
			foutstd << brdf[i] << std::endl;
		}
		fouttmp.close();
		foutstd.close();
		return false;
	}
}
