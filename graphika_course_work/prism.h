#pragma once
#include <stdio.h>
#include "point.h"
#include "plane.h"



class prism
{
	
public:
	point* mid;
	int num;
	point* points[6];
	point* points_shadow[6];
	plane* sides[10];
	int side_num;

	void calcMiddle()
	{
		mid->x = 0;
		for (int i = 0; i < num; i++)
			mid->x += points[i]->x;

		mid->x /= (float)num;

		mid->y = 0;
		for (int i = 0; i < num; i++)
			mid->y += points[i]->y;

		mid->y /= (float)num;

		mid->z = 0;
		for (int i = 0; i < num; i++)
			mid->z += points[i]->z;

		mid->z /= (float)num;

		mid->w = 1;
	}


	prism(int s)
	{
		num = 6;

		point * a = new point(0, 20, 0);
		point * b = new point(20, 20, 30);
		point * c = new point(30, 20 , 0);
		point * d = new point(0, 40, 0);
		point * e = new point(20, 40, 30);
		point * f = new point(30, 40, 0);

		plane* abed = new plane(a, b, e, d, 1+  s);
		plane* bcfe = new plane(b, c, f, e, 2 + s);
		plane* cadf = new plane(c, a, d, f, 3 + s);
		plane* abc = new plane (a, c, b, 4 + s);
		plane* def = new plane (d, e, f, 5 + s);
		
		point* sa = new point();
		point* sb = new point();
		point* sc = new point();
		point* sd = new point();
		point* se = new point();
		point* sf = new point();
		plane* sabed = new plane(sa,sb,se,sd, 8);
		plane* sbcfe = new plane(sb, sc, sf, se, 8);
		plane* scadf = new plane(sc, sa, sd, sf, 8);
		plane* sabc = new plane (sa,sc,sb, 8);
		plane* sdef = new plane(sd, se, sf, 8);

		side_num = 10;
		sides[0] = abed;
		sides[1] = bcfe;
		sides[2] = cadf;
		sides[3] = abc;
		sides[4] = def;
		sides[5] = sabed;
		sides[6] = sbcfe;
		sides[7] = scadf;
		sides[8] = sabc;
		sides[9] = sdef;

		points_shadow[0] = sa;
		points_shadow[1] = sb;
		points_shadow[2] = sc;
		points_shadow[3] = sd;
		points_shadow[4] = se;
		points_shadow[5] = sf;

		points[0] = a;
		points[1] = b;
		points[2] = c;
		points[3] = d;
		points[4] = e;
		points[5] = f;

		mid = new point;
	}


	void move(double x, double y, double z)
	{
		for (int i = 0; i < num; i++)
			points[i]->move(x, y, z);
	}

	void scale(double x, double y, double z)
	{
		calcMiddle();
		move(-mid->x, -mid->y, -mid->z);
		for (int i = 0; i < num; i++)
			points[i]->scale(x, y, z);
		move(mid->x, mid->y, mid->z);
	}

	void rotateX(double phi)
	{
		calcMiddle();
		move(-mid->x, -mid->y, -mid->z);
		for (int i = 0; i < num; i++)
			points[i]->rotateX(phi);
		move(mid->x, mid->y, mid->z);
	}

	void rotateY(double phi)
	{
		calcMiddle();
		move(-mid->x, -mid->y, -mid->z);
		for (int i = 0; i < num; i++)
			points[i]->rotateY(phi);
		move(mid->x, mid->y, mid->z);
	}

	void rotateZ(double phi)
	{
		calcMiddle();
		move(-mid->x, -mid->y, -mid->z);
		for (int i = 0; i < num; i++)
			points[i]->rotateZ(phi);
		move(mid->x, mid->y, mid->z);
	}

	void create_shadow()
	{
		double y = 350;
		point* L = new point(200, -300, 0);
		for (int i = 0; i < num; i++)
		{
			int t = (y - points[i]->y) / (L->y - points[i]->y);
			int x = (L->x - points[i]->x) * t + points[i]->x;
			int z = (L->z - points[i]->z) * t + points[i]->z;
			points_shadow[i]->x = x;
			points_shadow[i]->y = y;
			points_shadow[i]->z = z;
			points_shadow[i]->rotateX(30);
		}

	}

	void proj()
	{
		for (int i = 0; i < num; i++)
			points[i]->rotateX(30);
	}

	void unproj()
	{
		for (int i = 0; i < num; i++)
			points[i]->rotateX(-30);
	}
};