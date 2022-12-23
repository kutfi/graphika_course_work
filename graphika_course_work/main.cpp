#include "../libwinbgi/src/graphics.h"
#include <stdio.h>
#include "point.h"
#include "plane.h"
#include "prism.h"
#include <stdio.h>
#include <queue>
#include <iostream>

#define DEPTH 0
#define CLR 1
#define SIZE 400


float buffer[SIZE][SIZE][2] = { 0 };

void clean_buffer()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			buffer[i][j][DEPTH] = -1000;
			buffer[i][j][CLR] = 0;
		}
	}
}

void isPointVisible(point* p, point* p1, point* p2, bool* pointSeen)
{
	float rab1 = (p->x - p1->x) * (p2->y - p1->y);
	float rab2 = (p->y - p1->y) * (p2->x - p1->x);
	float rab3 = rab1 - rab2;

	if (rab3 > 0)
		*pointSeen = true;
	else
		*pointSeen = false;

}

point* p1 = new point;
point* p2 = new point;
point* p0 = new point;




bool check_inbox(plane* p, float x, float y)
{
	bool flag = false;
	int j = 0;
	p0->x = x;
	p0->y = y;

	for (int i = 0; i < p->point_number; i++)
	{
		j = i + 1;
		if (i == p->point_number - 1)
			j = 0;
		
		p1->x = p->v[j]->x;
		p1->y = p->v[j]->y;
		p2->x = p->v[i]->x;
		p2->y = p->v[i]->y;

		isPointVisible(p0, p1, p2, &flag);

		if (!flag)
			return (false);

	}
	return (flag);
}

void getZ(plane* p, int x, int y, int* z)
{
	if (p->C == 0)
		for (int i = 1; i < p->point_number; i++)
			*z = max(p->v[i]->z, p->v[i - 1]->z);
	else
		*z = -(p->A * x + p->B * y + p->D) / p->C;

}

using namespace std;
vector< pair<int, int >> stack;

void create_stack(plane* p, int x, int y)
{
	if (!check_inbox(p, x, y))
		return;
	if (x < 0 || y < 0 || x >= SIZE || y >= SIZE)
		return;
	
	stack.push_back(make_pair(x, y));
	if (!(find(stack.begin(), stack.end(), make_pair(x + 1, y)) != stack.end()))
		create_stack(p, x + 1, y);
	if (!(find(stack.begin(), stack.end(), make_pair(x, y + 1)) != stack.end()))
	create_stack(p, x, y + 1);
	if (!(find(stack.begin(), stack.end(), make_pair(x -1, y)) != stack.end()))
		create_stack(p, x - 1, y);
	if (!(find(stack.begin(), stack.end(), make_pair(x, y -1)) != stack.end()))
		create_stack(p, x, y - 1 );
}

void pop_stack(plane* p,  int fill_color)
{
	std::pair<int, int > ptr;
	int z;

	while (stack.size() != 0)
	{
		ptr = stack.back();
		stack.pop_back();
		int x = ptr.first;
		int y = ptr.second;
		getZ(p, x, y, &z);

		if (z > buffer[x][y][DEPTH])
		{
			buffer[x][y][DEPTH] = z;
			buffer[x][y][CLR] = fill_color;
		}

	}
	
}
void check_plane(plane* p, float x, float y, int fill_color)
{
	create_stack(p, x, y);
	pop_stack(p, fill_color);
}



void zbuffer(prism** p, int n)
{
	clean_buffer();
	printf("updating buffer... ");
	for (int i = 0; i < n; i++)
	{
		p[i]->proj();
		p[i]->calcMiddle();
		p[i]->create_shadow();
		
		for (int j = 0; j < p[i]->side_num; j++)
		{
			p[i]->sides[j]->updateCoefs();
			p[i]->sides[j]->calcMIddle();		
			check_plane(p[i]->sides[j], p[i]->sides[j]->middle->x, p[i]->sides[j]->middle->y, p[i]->sides[j]->color);			
		}
		p[i]->unproj();
	}
	printf("updated!\n");
}


void print_buffer()
{
	printf("updating screen... ");
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			putpixel(i, j, buffer[i][j][CLR]);
		}
	}
	printf("updated!\n");
}

void menu_instruction()
{
	printf("USE:\twasdqe and uhjkyi to MOVE\n");
	printf("USE:\t123456 and 7890-= to ROTATE\n");
	printf("USE:\tzx and nm to SCALE\n");
	printf("USE:\t! to EXIT\n");
}

int main()
{
	menu_instruction();
	prism* p1 = new prism(0);
	prism* p2 = new prism(9);
	p1->scale(2, 2, 2);
	p1->move(100, 200, 0);
	p2->scale(2, 2, 2);
	p2->move(250, 200, 10);


	int N = 2;
	prism* arr[2] = { p1, p2};
	
	initwindow(SIZE, SIZE);

	bool toUpdate = true;
	char c;
	while (true)
	{
		if (toUpdate)
		{
			zbuffer(arr, N);
			print_buffer();
		}
		c = getch();
		toUpdate = true;
		switch (c)
		{
		case '!':
			closegraph();
			return 0;

		case 'z':
			p1->scale(2, 2, 2);
			break;
		case 'x':
			p1->scale(0.5, 0.5, 0.5);
			break;
		case 'd':
			p1->move(40, 0, 0);
			break;
		case 'a':
			p1->move(-40, 0, 0);
			break;

		case 'w':
			p1->move(0, -40, 0);
			break;
		case 's':
			p1->move(0, 40, 0);
			break;
		case 'q':
			p1->move(0, 0, 40);
			break;
		case 'e':
			p1->move(0, 0, -40);
			break;

		case '1':
			p1->rotateX(40);
			break;
		case '2':
			p1->rotateX(-40);
			break;
		case '3':
			p1->rotateY(40);
			break;
		case '4':
			p1->rotateY(-40);
			break;
		case '5':
			p1->rotateZ(40);
			break;
		case '6':
			p1->rotateZ(-40);
			break;


		case 'n':
			p2->scale(2, 2, 2);
			break;
		case 'm':
			p2->scale(0.5, 0.5, 0.5);
			break;
		case 'k':
			p2->move(40, 0, 0);
			break;
		case 'h':
			p2->move(-40, 0, 0);
			break;
		case 'u':
			p2->move(0, -40, 0);
			break;
		case 'j':
			p2->move(0, 40, 0);
			break;
		case 'y':
			p2->move(0, 0, 40);
			break;
		case 'i':
			p2->move(0, 0, -40);
			break;
		case '7':
			p2->rotateX(40);
			break;
		case '8':
			p2->rotateX(-40);
			break;
		case '9':
			p2->rotateY(40);
			break;
		case '0':
			p2->rotateY(-40);
			break;
		case '-':
			p2->rotateZ(40);
			break;
		case '=':
			p2->rotateZ(-40);
			break;

		default:
			printf("\tunknown command!\n");
			toUpdate = false;
			break;
		}
	}
	closegraph();


}