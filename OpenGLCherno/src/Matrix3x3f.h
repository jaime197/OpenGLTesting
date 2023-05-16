#pragma once

struct Matrix3x3f {
	float m[3][3];

public:
	Matrix3x3f() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				m[i][j] = 0.0f;
			}
		}
	}

	float Determinant3x3(Matrix3x3f mat)
	{
		float det = 0.0f;
		det = mat.m[0][0] * (mat.m[1][1] * mat.m[2][2] - mat.m[2][1] * mat.m[1][2]);
		det -= mat.m[0][1] * (mat.m[1][0] * mat.m[2][2] - mat.m[2][0] * mat.m[1][2]);
		det += mat.m[0][2] * (mat.m[1][0] * mat.m[2][1] - mat.m[2][0] * mat.m[1][1]);
		return det;
	}
};