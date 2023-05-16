#pragma once
#include "Vector4f.h"
#include "Matrix3x3f.h"

struct Matrix4x4f {
	float m[4][4];

public:
	Matrix4x4f() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m[i][j] = 0.0f;
			}
		}
	}

	Matrix4x4f(float a11, float a12, float a13, float a14,
		float a21, float a22, float a23, float a24,
		float a31, float a32, float a33, float a34,
		float a41, float a42, float a43, float a44)
	{
		m[0][0] = a11; m[0][1] = a12; m[0][2] = a13; m[0][3] = a14;
		m[1][0] = a21; m[1][1] = a22; m[1][2] = a23; m[1][3] = a24;
		m[2][0] = a31; m[2][1] = a32; m[2][2] = a33; m[2][3] = a34;
		m[3][0] = a41; m[3][1] = a42; m[3][2] = a43; m[3][3] = a44;
	}

	Matrix4x4f make_identify();
	Matrix4x4f make_translate(float x, float y, float z);
	Matrix4x4f make_rotate(float angleX, float angleY, float angleZ);
	Matrix4x4f make_scale(float x, float y, float z);
	Matrix3x3f submatrix4x4(int i, int j) const;
	float make_determinant();
	Matrix4x4f make_inverse(Matrix4x4f m);
	Matrix4x4f make_transpose(Matrix4x4f m);
	void printMatrix();

	Matrix4x4f operator+(const Matrix4x4f& other) const;
	Matrix4x4f operator-(const Matrix4x4f& other) const;
	Matrix4x4f operator·(const float& other) const;
	Matrix4x4f operator/(const float& other) const;
	Vector4f operator*(const Vector4f& other) const;
	Matrix4x4f operator*(const Matrix4x4f& other) const;	
};