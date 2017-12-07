#include <ctime>
#include "camera.h"
#include "light.h"
#include "brdf.h"
#include "gradient.h"

#define PI 3.1415926535

para_brdf Data;
cam_coord_system Cam;
light_system Light;

int x = 1368, y = 1096;

glm::vec3 normalize(glm::vec3 v) {
	float len = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	return glm::vec3(v.x / len, v.y / len, v.z / len);
}
float length(glm::vec3 v) {
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

int main() {
	read_cam_and_light("cam_and_light.txt", Cam, Light);

	FILE *fp;
	//fopen_s(&fp, "tmp.txt", "rb+");
	fopen_s(&fp, "test.txt", "rb+");

	int size;
	fread(&size, sizeof(int), 1, fp);
	std::vector<para_brdf> para_value(size);
	for (int i = 0; i < size; i++) {
		para_value[i].read(fp);
	}
	fclose(fp);

	std::vector<glm::vec3>wi;
	glm::vec3 wo;

	compute_wiwo(x, y, Cam, Light, wi, wo);

	clock_t g = clock();
	std::vector<para_brdf> para_res(size);
	for (int i = 0; i < 1000; i++) {
		clock_t t = clock();
		if (gradient(wi, wo, x, y, para_value[i].get_brdf(), para_res[i].get_para())) {
			while (gradient(wi, wo, x, y, para_value[i].get_brdf(), para_res[i].get_para(), true)) {

#ifndef DEBUG
				if (clock() - t > 4000) {
					std::cout << "fail ";
					break;
				}
#endif 

			}
		}
		std::cout << clock() - t << std::endl;

#ifdef DEBUG
		std::cout << para_value[i].get_para()[0] << " " << 
			para_res[i].get_para()[1] << " " <<
			para_res[i].get_para()[2] << " " <<
			para_res[i].get_para()[3] << " " <<
			para_res[i].get_para()[4] << " " <<
			para_res[i].get_para()[5] << " " <<
			para_res[i].get_para()[6] << std::endl <<
			para_value[i].get_para()[0] - para_res[i].get_para()[0] << " " <<
			para_value[i].get_para()[1] - para_res[i].get_para()[1] << " " <<
			para_value[i].get_para()[2] - para_res[i].get_para()[2] << " " <<
			para_value[i].get_para()[3] - para_res[i].get_para()[3] << " " <<
			para_value[i].get_para()[4] - para_res[i].get_para()[4] << " " <<
			para_value[i].get_para()[5] - para_res[i].get_para()[5] << " " <<
			para_value[i].get_para()[6] - para_res[i].get_para()[6] << std::endl << std::endl;

		system("pause");
#endif

	}
	std::cout << clock() - g << std::endl;
	system("pause");

	return 0;
}