#include <iostream>
#include "Matrix4x4f.h"
#include "Matrix3x3f.h"
#define PI 3.14159265358979323846

Matrix4x4f Matrix4x4f::make_identify()
{
    Matrix4x4f result;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                result.m[i][j] = 1.0f;
            }
            else {
                result.m[i][j] = 0.0f;
            }
        }
    }
    return result;
}

Matrix4x4f Matrix4x4f::make_translate(float x, float y, float z)
{
    Matrix4x4f result;

    result.m[0][0] = 1;
    result.m[0][3] = x;
    result.m[1][1] = 1;
    result.m[1][3] = y;
    result.m[2][2] = 1;
    result.m[2][3] = z;
    result.m[3][3] = 1;

    return result;
}

Matrix4x4f Matrix4x4f::make_rotate(float angleX, float angleY, float angleZ)
{
    Matrix4x4f matrixX, matrixY, matrixZ;

    // Convertimos los ángulos a radianes
    float radX = angleX * PI / 180.0f;
    float radY = angleY * PI / 180.0f;
    float radZ = angleZ * PI / 180.0f;

    // Matriz de rotación en el eje X
    matrixX.m[0][0] = 1.0f;
    matrixX.m[0][1] = 0.0f;
    matrixX.m[0][2] = 0.0f;
    matrixX.m[0][3] = 0.0f;

    matrixX.m[1][0] = 0.0f;
    matrixX.m[1][1] = std::cos(radX);
    matrixX.m[1][2] = -std::sin(radX);
    matrixX.m[1][3] = 0.0f;

    matrixX.m[2][0] = 0.0f;
    matrixX.m[2][1] = std::sin(radX);
    matrixX.m[2][2] = std::cos(radX);
    matrixX.m[2][3] = 0.0f;

    matrixX.m[3][0] = 0.0f;
    matrixX.m[3][1] = 0.0f;
    matrixX.m[3][2] = 0.0f;
    matrixX.m[3][3] = 1.0f;

    // Matriz de rotación en el eje Y
    matrixY.m[0][0] = std::cos(radY);
    matrixY.m[0][1] = 0.0f;
    matrixY.m[0][2] = std::sin(radY);
    matrixY.m[0][3] = 0.0f;
           
    matrixY.m[1][0] = 0.0f;
    matrixY.m[1][1] = 1.0f;
    matrixY.m[1][2] = 0.0f;
    matrixY.m[1][3] = 0.0f;
           
    matrixY.m[2][0] = -std::sin(radY);
    matrixY.m[2][1] = 0.0f;
    matrixY.m[2][2] = std::cos(radY);
    matrixY.m[2][3] = 0.0f;
           
    matrixY.m[3][0] = 0.0f;
    matrixY.m[3][1] = 0.0f;
    matrixY.m[3][2] = 0.0f;
    matrixY.m[3][3] = 1.0f;

    // Matriz de rotación en el eje Z
    matrixZ.m[0][0] = std::cos(radZ);
    matrixZ.m[0][1] = -std::sin(radZ);
    matrixZ.m[0][2] = 0.0f;
    matrixZ.m[0][3] = 0.0f;
           
    matrixZ.m[1][0] = std::sin(radZ);
    matrixZ.m[1][1] = std::cos(radZ);
    matrixZ.m[1][2] = 0.0f;
    matrixZ.m[1][3] = 0.0f;
           
    matrixZ.m[2][0] = 0.0f;
    matrixZ.m[2][1] = 0.0f;
    matrixZ.m[2][2] = 1.0f;
    matrixZ.m[2][3] = 0.0f;

    matrixZ.m[3][0] = 0.0f;
    matrixZ.m[3][1] = 0.0f;
    matrixZ.m[3][2] = 0.0f;
    matrixZ.m[3][3] = 1.0f;

    // Combinamos las tres matrices de rotación en una sola
    Matrix4x4f matrixRot = matrixZ * matrixY * matrixX;

    return matrixRot;
}

Matrix4x4f Matrix4x4f::make_scale(float x, float y, float z)
{
    Matrix4x4f result;

    result.m[0][0] = x;
    result.m[1][1] = y;
    result.m[2][2] = z;
    result.m[3][3] = 1;

    return result;
}

Matrix3x3f Matrix4x4f::submatrix4x4(int i, int j) const
{
    Matrix3x3f submat;

    // Copy the elements of the 3x3 submatrix from the 4x4 matrix
    int row = 0;
    for (int m = 0; m < 4; m++)
    {
        if (m == i) continue;
        int col = 0;
        for (int n = 0; n < 4; n++)
        {
            if (n == j) continue;
            submat.m[row][col] = this->m[m][n];
            col++;
        }
        row++;
    }
    return submat;
}

float Matrix4x4f::make_determinant()
{
    float det = 0;
    Matrix3x3f submat;

    for (int i = 0; i < 4; i++) {
        submat = submatrix4x4(i, 0);
        det += m[i][0] * submat.Determinant3x3(submat) * ((i % 2 == 0) ? 1 : -1);
    }

    return det;
}

Matrix4x4f Matrix4x4f::make_inverse(Matrix4x4f m)
{
    float det = make_determinant();
    if (det == 0.0f) {
        // Return the identity matrix.
        return Matrix4x4f();
    }

    Matrix4x4f adj;
    Matrix3x3f sub;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            sub = m.submatrix4x4(i, j);
            if ((i+j) % 2 == 0) {
                adj.m[i][j] = sub.Determinant3x3(sub);
            }
            else {
                adj.m[i][j] = - sub.Determinant3x3(sub);
            }
        }
    }

    adj.make_transpose(adj);

    Matrix4x4f result;

    result = adj / det;

    return result;
}

Matrix4x4f Matrix4x4f::make_transpose(Matrix4x4f m)
{
    Matrix4x4f result = m;
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = i + 1; j < 4; j++)
            {
                std::swap(result.m[i][j], result.m[j][i]);
            }
        }
    }

    return result;
}

void Matrix4x4f::printMatrix()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << this->m[i][j] << "\t"; // Use tab to separate the elements
        }
        std::cout << std::endl; // Move to the next line after each row
    }
}

Matrix4x4f Matrix4x4f::operator+(const Matrix4x4f& other) const
{
    Matrix4x4f result;

    result.m[0][0] = m[0][0] + other.m[0][0];
    result.m[0][1] = m[0][1] + other.m[0][1];
    result.m[0][2] = m[0][2] + other.m[0][2];
    result.m[0][3] = m[0][3] + other.m[0][3];
    result.m[1][0] = m[1][0] + other.m[1][0];
    result.m[1][1] = m[1][1] + other.m[1][1];
    result.m[1][2] = m[1][2] + other.m[1][2];
    result.m[1][3] = m[1][3] + other.m[1][3];
    result.m[2][0] = m[2][0] + other.m[2][0];
    result.m[2][1] = m[2][1] + other.m[2][1];
    result.m[2][2] = m[2][2] + other.m[2][2];
    result.m[2][3] = m[2][3] + other.m[2][3];
    result.m[3][0] = m[3][0] + other.m[3][0];
    result.m[3][1] = m[3][1] + other.m[3][1];
    result.m[3][2] = m[3][2] + other.m[3][2];
    result.m[3][3] = m[3][3] + other.m[3][3];

    return result;
}

Matrix4x4f Matrix4x4f::operator-(const Matrix4x4f& other) const
{
    Matrix4x4f result;

    result.m[0][0] = m[0][0] - other.m[0][0];
    result.m[0][1] = m[0][1] - other.m[0][1];
    result.m[0][2] = m[0][2] - other.m[0][2];
    result.m[0][3] = m[0][3] - other.m[0][3];
    result.m[1][0] = m[1][0] - other.m[1][0];
    result.m[1][1] = m[1][1] - other.m[1][1];
    result.m[1][2] = m[1][2] - other.m[1][2];
    result.m[1][3] = m[1][3] - other.m[1][3];
    result.m[2][0] = m[2][0] - other.m[2][0];
    result.m[2][1] = m[2][1] - other.m[2][1];
    result.m[2][2] = m[2][2] - other.m[2][2];
    result.m[2][3] = m[2][3] - other.m[2][3];
    result.m[3][0] = m[3][0] - other.m[3][0];
    result.m[3][1] = m[3][1] - other.m[3][1];
    result.m[3][2] = m[3][2] - other.m[3][2];
    result.m[3][3] = m[3][3] - other.m[3][3];

    return result;
}

Matrix4x4f Matrix4x4f::operator·(const float& other) const
{
    Matrix4x4f result;

    result.m[0][0] = m[0][0] * other;
    result.m[0][1] = m[0][1] * other;
    result.m[0][2] = m[0][2] * other;
    result.m[0][3] = m[0][3] * other;
    result.m[1][0] = m[1][0] * other;
    result.m[1][1] = m[1][1] * other;
    result.m[1][2] = m[1][2] * other;
    result.m[1][3] = m[1][3] * other;
    result.m[2][0] = m[2][0] * other;
    result.m[2][1] = m[2][1] * other;
    result.m[2][2] = m[2][2] * other;
    result.m[2][3] = m[2][3] * other;
    result.m[3][0] = m[3][0] * other;
    result.m[3][1] = m[3][1] * other;
    result.m[3][2] = m[3][2] * other;
    result.m[3][3] = m[3][3] * other;

    return result;
}

Matrix4x4f Matrix4x4f::operator/(const float& other) const
{
    Matrix4x4f result;

    result.m[0][0] = m[0][0] / other;
    result.m[0][1] = m[0][1] / other;
    result.m[0][2] = m[0][2] / other;
    result.m[0][3] = m[0][3] / other;
    result.m[1][0] = m[1][0] / other;
    result.m[1][1] = m[1][1] / other;
    result.m[1][2] = m[1][2] / other;
    result.m[1][3] = m[1][3] / other;
    result.m[2][0] = m[2][0] / other;
    result.m[2][1] = m[2][1] / other;
    result.m[2][2] = m[2][2] / other;
    result.m[2][3] = m[2][3] / other;
    result.m[3][0] = m[3][0] / other;
    result.m[3][1] = m[3][1] / other;
    result.m[3][2] = m[3][2] / other;
    result.m[3][3] = m[3][3] / other;

    return result;
}

Vector4f Matrix4x4f::operator*(const Vector4f& other) const
{
    Vector4f result;

    result.x = (other.x * m[0][0]) + (other.y * m[0][1]) + (other.z * m[0][2]);
    result.y = (other.x * m[1][0]) + (other.y * m[1][1]) + (other.z * m[1][2]);
    result.z = (other.x * m[2][0]) + (other.y * m[2][1]) + (other.z * m[2][2]);

    return result;
}

Matrix4x4f Matrix4x4f::operator*(const Matrix4x4f& other) const
{
    Matrix4x4f result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = 0.0f;
            for (int k = 0; k < 4; k++) {
                result.m[i][j] += m[i][k] * other.m[k][j];
            }
        }
    }
    return result;
}
