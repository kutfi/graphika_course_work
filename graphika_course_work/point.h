#pragma once
#include "stdio.h"
#include "math.h"
#define X 0
#define Y 1
#define Z 2
#define W 3
#define M_PI 3.1415

class point
{
	float* multiplication(float mtx[4][4])
	{
		float x_ = x;
		float y_ = y;
		float z_ = z;
		float w_ = w;
		float temp[4] = { x, y, z, w };
		float res[4] = { 0,0,0,0 };

		res[X] = temp[0] * mtx[0][0] + temp[1] * mtx[1][0] + temp[2] * mtx[2][0] + temp[3] * mtx[3][0];
		res[Y] = temp[0] * mtx[0][1] + temp[1] * mtx[1][1] + temp[2] * mtx[2][1] + temp[3] * mtx[3][1];
		res[Z] = temp[0] * mtx[0][2] + temp[1] * mtx[1][2] + temp[2] * mtx[2][2] + temp[3] * mtx[3][2];
		res[W] = temp[0] * mtx[0][3] + temp[1] * mtx[1][3] + temp[2] * mtx[2][3] + temp[3] * mtx[3][3];

		x = res[X];
		y = res[Y];
		z = res[Z];
		w = res[W];
		return res;
	}


public:

	float x, y, z, w;
	point(int _x, int _y, int _z) : x(_x), y(_y), z(_z)
	{
		w = 1;
	}
	point()
	{
		x = 0; y = 0; z = 0; w = 1;
	}


	void move(float _x, float _y, float _z)
	{
		float matrix[4][4] = {
			1,  0,  0,  0,	0,  1,  0,  0,
			0,  0,  1,  0,	_x, _y, _z, 1 };

		multiplication(matrix);
	}

	void scale(float _x, float _y, float _z) {
		float matrix[4][4] = {
			_x, 0, 0, 0, 0, _y, 0, 0,
			0, 0, _z, 0, 0, 0, 0, 1 };

		multiplication(matrix);
	}


	void rotateX(float phi) {
		phi *= M_PI / 180;

		float matrix[4][4] = {
			1, 0, 0, 0,	0, cos(phi), -sin(phi), 0,
			0, sin(phi), cos(phi), 0, 0, 0, 0, 1 };
		multiplication(matrix);
	}

	void rotateY(float phi) {
		phi *=  M_PI / 180;

		float matrix[4][4] = {
			cos(phi), 0, -sin(phi), 0,0, 1, 0, 0,
			sin(phi), 0, cos(phi), 0,	0, 0, 0, 1 };
		multiplication(matrix);
	}

	void rotateZ(float phi) {
		phi *= M_PI / 180;

		float matrix[4][4] = {
			cos(phi), -sin(phi), 0, 0,	sin(phi), cos(phi), 0, 0,
			0, 0, 1, 0,		0, 0, 0, 1 };
		multiplication(matrix);
	}

};