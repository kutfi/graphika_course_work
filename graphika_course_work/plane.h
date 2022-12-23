#pragma once
#include "point.h"

class plane
{

public:
	point** v;
	int point_number;
	int color;
	float A, B, C, D;

	point* middle;

	void calcMIddle()
	{
		middle->x=0;
		middle->y=0;
		middle->z=0;
		for (int i = 0; i < point_number; i++)
		{
			middle->x += v[i]->x;
			middle->y += v[i]->y;
			middle->z += v[i]->z;
		}
		middle->x /= point_number;
		middle->y /= point_number;
		middle->z /= point_number;
		
	}



	plane(point* _A, point* _B, point* _C, int c)
	{
		point_number = 3;
		v = new point * [point_number];
		v[0] = _A;
		v[1] = _B;
		v[2] = _C;

		color = c;
		middle = new point();
		updateCoefs();
	}

	plane(point* _A, point* _B, point* _C, point* _D, int c)
	{
		point_number = 4;
		v = new point * [point_number];
		v[0] = _A;
		v[1] = _B;
		v[2] = _C;
		v[3] = _D;
		middle = new point();
		color = c;
		updateCoefs();
	}



	void updateCoefs()
	{
		int i = 0;
		float M[3] = { v[i]->x, v[i]->y, v[i]->z };
		int ai = i - 1;
		if (ai < 0)
			ai = 2;
		int bi = i + 1;
		if (bi > 2)
			bi = 0;
		float a[3] = { v[ai]->x - v[i]->x, v[ai]->y - v[i]->y, v[ai]->z - v[i]->z };
		float b[3] = { v[bi]->x - v[i]->x, v[bi]->y - v[i]->y, v[bi]->z - v[i]->z };

		A = a[Y] * b[Z] - a[Z] * b[Y];
		B = a[X] * b[Z] - a[Z] * b[X];
		B = -B;
		C = a[X] * b[Y] - a[Y] * b[X];

		D = M[X] * A + M[Y] * B + M[Z] * C;
		D = -D;


	}

};