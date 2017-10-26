#pragma once
#include <string>
#define PIE 3.1415926535

class vector {
public:
	vector() {
		x = y = z = 0;
	}
	vector(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	vector(float src[3]) {
		x = src[0];
		y = src[1];
		z = src[3];
	}
	vector(vector &v) {
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}
	vector &operator=(vector &v) {
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
		return *this;
	}

	float &operator[](int i) {
		return (&x)[i];
	}

	vector &plus(vector &v) {
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
		return *this;
	}
	vector operator+(vector &v) {
		return vector(this->x + v.x, this->y + v.y, this->z + v.z);
	}
	vector &operator+=(vector &v) {
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
		return *this;
	}
	vector &minus(vector &v) {
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
		return *this;
	}
	vector operator-(vector &v){
		return vector(this->x - v.x, this->y - v.y, this->z - v.z);
	}
	vector &operator-=(vector &v) {
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
		return *this;
	}

	vector &multy(float m) {
		x *= m;
		y *= m;
		z *= m;
		return *this;
	}
	vector operator*(float m) {
		return vector(x*m, y*m, z*m);
	}
	vector &operator*=(float m) {
		x *= m;
		y *= m;
		z *= m;
		return *this;
	}
	vector &divide(float d) {
		x /= d;
		y /= d;
		z /= d;
		return *this;
	}
	vector operator/(float d) {
		return vector(x / d, y / d, z / d);
	}
	vector &operator/=(float d) {
		x /= d;
		y /= d;
		z /= d;
		return *this;
	}

	vector raster() {
		return vector(int(x), int(y), int(z));
	}
private:
	float x, y, z;
};

class matrix {
public:
	matrix() {
		mat[0][0] = mat[1][1] = mat[2][2] = 1;
		mat[0][1] = mat[0][2] = mat[1][0] = 0;
		mat[1][2] = mat[2][0] = mat[2][1] = 0;
	}
	matrix(float xx, float xy, float xz,
		float yx, float yy, float yz,
		float zx, float zy, float zz) {
		mat[0][0] = xx;
		mat[0][1] = xy;
		mat[0][2] = xz;
		mat[1][0] = yx;
		mat[1][1] = yy;
		mat[1][2] = yz;
		mat[2][0] = zx;
		mat[2][1] = zy;
		mat[2][2] = zz;
	}
	matrix(float src[3][3]) {
		memcpy(mat, src, 3 * 3 * sizeof(float));
	}
	matrix(matrix &m) {
		memcpy(mat, m.mat, 3 * 3 * sizeof(float));
	}
	matrix &operator=(matrix &m) {
		memcpy(mat, m.mat, 3 * 3 * sizeof(float));
		return *this;
	}

	matrix &plus(matrix &m) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				mat[i][j] += m.mat[i][j];
			}
		}
		return *this;
	}
	matrix operator+(matrix m) {
		return matrix(mat[0][0] + m.mat[0][0], mat[0][1] + m.mat[0][1], mat[0][2] + m.mat[0][2],
			mat[1][0] + m.mat[1][0], mat[1][1] + m.mat[1][1], mat[1][2] + m.mat[1][2],
			mat[2][0] + m.mat[2][0], mat[2][1] + m.mat[2][1], mat[2][2] + m.mat[2][2]);
	}
	matrix &operator+=(matrix m) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				mat[i][j] += m.mat[i][j];
			}
		}
		return *this;
	}
	matrix &minus(matrix &m) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				mat[i][j] -= m.mat[i][j];
			}
		}
		return *this;
	}
	matrix operator-(matrix m) {
		return matrix(mat[0][0] - m.mat[0][0], mat[0][1] - m.mat[0][1], mat[0][2] - m.mat[0][2],
			mat[1][0] - m.mat[1][0], mat[1][1] - m.mat[1][1], mat[1][2] - m.mat[1][2],
			mat[2][0] - m.mat[2][0], mat[2][1] - m.mat[2][1], mat[2][2] - m.mat[2][2]);
	}
	matrix &operator-=(matrix m) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				mat[i][j] -= m.mat[i][j];
			}
		}
		return *this;
	}

	vector operator*(vector v) {
		return vector(mat[0][0] * v[0] + mat[0][1] * v[1] + mat[0][2] * v[2],
			mat[1][0] * v[0] + mat[1][1] * v[1] + mat[1][2] * v[2],
			mat[2][0] * v[0] + mat[2][1] * v[1] + mat[2][2] * v[2]);
	}

	matrix &multy(matrix m) {
		mat[0][0] = mat[0][0] * m.mat[0][0] + mat[0][1] * m.mat[1][0] + mat[0][2] * m.mat[2][0];
		mat[0][1] = mat[0][0] * m.mat[0][1] + mat[0][1] * m.mat[1][1] + mat[0][2] * m.mat[2][1];
		mat[0][2] = mat[0][0] * m.mat[0][2] + mat[0][1] * m.mat[1][2] + mat[0][2] * m.mat[2][2];
		mat[1][0] = mat[1][0] * m.mat[0][0] + mat[1][1] * m.mat[1][0] + mat[1][2] * m.mat[2][0];
		mat[1][1] = mat[1][0] * m.mat[0][1] + mat[1][1] * m.mat[1][1] + mat[1][2] * m.mat[2][1];
		mat[1][2] = mat[1][0] * m.mat[0][2] + mat[1][1] * m.mat[1][2] + mat[1][2] * m.mat[2][2];
		mat[2][0] = mat[2][0] * m.mat[0][0] + mat[2][1] * m.mat[1][0] + mat[2][2] * m.mat[2][0];
		mat[2][1] = mat[2][0] * m.mat[0][1] + mat[2][1] * m.mat[1][1] + mat[2][2] * m.mat[2][1];
		mat[2][2] = mat[2][0] * m.mat[0][2] + mat[2][1] * m.mat[1][2] + mat[2][2] * m.mat[2][2];
		return *this;
	}
	matrix operator*(matrix m) {
		return matrix(mat[0][0] * m.mat[0][0] + mat[0][1] * m.mat[1][0] + mat[0][2] * m.mat[2][0],
			mat[0][0] * m.mat[0][1] + mat[0][1] * m.mat[1][1] + mat[0][2] * m.mat[2][1],
			mat[0][0] * m.mat[0][2] + mat[0][1] * m.mat[1][2] + mat[0][2] * m.mat[2][2],
			mat[1][0] * m.mat[0][0] + mat[1][1] * m.mat[1][0] + mat[1][2] * m.mat[2][0],
			mat[1][0] * m.mat[0][1] + mat[1][1] * m.mat[1][1] + mat[1][2] * m.mat[2][1],
			mat[1][0] * m.mat[0][2] + mat[1][1] * m.mat[1][2] + mat[1][2] * m.mat[2][2],
			mat[2][0] * m.mat[0][0] + mat[2][1] * m.mat[1][0] + mat[2][2] * m.mat[2][0],
			mat[2][0] * m.mat[0][1] + mat[2][1] * m.mat[1][1] + mat[2][2] * m.mat[2][1],
			mat[2][0] * m.mat[0][2] + mat[2][1] * m.mat[1][2] + mat[2][2] * m.mat[2][2]);
	}
	matrix &operator*=(matrix m) {
		mat[0][0] = mat[0][0] * m.mat[0][0] + mat[0][1] * m.mat[1][0] + mat[0][2] * m.mat[2][0];
		mat[0][1] = mat[0][0] * m.mat[0][1] + mat[0][1] * m.mat[1][1] + mat[0][2] * m.mat[2][1];
		mat[0][2] = mat[0][0] * m.mat[0][2] + mat[0][1] * m.mat[1][2] + mat[0][2] * m.mat[2][2];
		mat[1][0] = mat[1][0] * m.mat[0][0] + mat[1][1] * m.mat[1][0] + mat[1][2] * m.mat[2][0];
		mat[1][1] = mat[1][0] * m.mat[0][1] + mat[1][1] * m.mat[1][1] + mat[1][2] * m.mat[2][1];
		mat[1][2] = mat[1][0] * m.mat[0][2] + mat[1][1] * m.mat[1][2] + mat[1][2] * m.mat[2][2];
		mat[2][0] = mat[2][0] * m.mat[0][0] + mat[2][1] * m.mat[1][0] + mat[2][2] * m.mat[2][0];
		mat[2][1] = mat[2][0] * m.mat[0][1] + mat[2][1] * m.mat[1][1] + mat[2][2] * m.mat[2][1];
		mat[2][2] = mat[2][0] * m.mat[0][2] + mat[2][1] * m.mat[1][2] + mat[2][2] * m.mat[2][2];
		return *this;
	}

	static matrix translate(float deltaX, float deltaY) {
		return matrix(1, 0, deltaX, 0, 1, deltaY, 0, 0, 1);
	}
	static matrix scale(float scaleX, float scaleY) {
		return matrix(scaleX, 0, 0, 0, scaleY, 0, 0, 0, 1);
	}
	static matrix rotate(float theta) {
		return matrix(cosf(theta), -sinf(theta), 0, sinf(theta), cosf(theta), 0, 0, 0, 1);
	}
	static matrix shear(float shearX, float shearY) {
		return matrix(1, shearX, 0, shearY, 1, 0, 0, 0, 1);
	}
private:
	float mat[3][3];
};