#pragma once

struct Vector4f {
	float x;
	float y;
	float z;
	float w;


public:
	Vector4f() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {};

	Vector4f make_vector4f(float a, float b, float c, float d);
	Vector4f normalize(Vector4f v);

	int getX();
	int getY();
	int getZ();
	int getW();

	void printVector();
	void reset() {	x = 0; y = 0; z = 0; w = 0;	}

	Vector4f operator+(const Vector4f& other) const;
	Vector4f operator-(const Vector4f& other) const;	
	float operator*(const Vector4f& other) const;		
	Vector4f operator*(const float& other) const;		//multplicacion escalar
	Vector4f operator&(const Vector4f& other) const;	//multpilicacion vectorial
};