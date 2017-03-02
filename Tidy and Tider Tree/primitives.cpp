#include "primitives.h"
#include <math.h>
#include <gl/glew.h>
#include <GL/GL.h>
#include <GL/glut.h>

/*! Draws a pixel using OpenGL
*/
void draw_pixel(GLint x, GLint y)
{
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0);
	glBegin(GL_POINTS);
	glVertex2i(x, 480 - y);
	glEnd();
}
void draw_line1(int x1, int y1, int x2, int y2)
{
	int k = y2 > y1 ? 1 : -1;
	int dx = x2 - x1;
	int dy = abs(y2 - y1);
	int d = 2 * dy - dx;
	int incrE = 2 * dy;
	int incrNE = 2 * (dy - dx);
	int x = x1;
	int y = y1;
	draw_pixel(x, y);
	while (x < x2)
	{
		if (d <= 0)
			d += incrE;
		else
		{
			d += incrNE;
			y += k;
		}
		x += 1;
		draw_pixel(x, y);
	}
}

void draw_line2(int x1, int y1, int x2, int y2)
{
	int k = x2 > x1 ? 1 : -1;
	int dx = abs(x2 - x1);
	int dy = y2 - y1;
	int d = 2 * dx - dy;
	int incrE = 2 * dx;
	int incrNE = 2 * (dx - dy);
	int x = x1;
	int y = y1;
	draw_pixel(x, y);
	while (y < y2)
	{
		if (d <= 0)
			d += incrE;
		else
		{
			d += incrNE;
			x += k;
		}
		y += 1;
		draw_pixel(x, y);
	}
}
/*! Bresenham Algorithm for drawing line*/
void line(int x1, int y1, int x2, int y2)
{
	if ((x2 >= x1) && (y2 >= y1))
	{
		if (x2 - x1 > y2 - y1)
			draw_line1(x1, y1, x2, y2);
		else
			draw_line2(x1, y1, x2, y2);
	}
	else if ((x2 >= x1) && (y2 < y1))
	{
		if (x2 - x1 > y1 - y2)
			draw_line1(x1, y1, x2, y2);
		else
			draw_line2(x2, y2, x1, y1);
	}
	else
		line(x2, y2, x1, y1);
}
void primitives::draw_line(void)
{
	//glClear(GL_COLOR_BUFFER_BIT);
	line(x1, y1,x2,y2);
	//draw_pixel(10, 10);
	glFlush();
}

void plot_circle(int x, int y, int cx, int cy)
{
	draw_pixel(cx + x, cy + y);
	draw_pixel(cx - x, cy + y);
	draw_pixel(cx + x, cy - y);
	draw_pixel(cx - x, cy - y);
	draw_pixel(cx + y, cy + x);
	draw_pixel(cx - y, cy + x);
	draw_pixel(cx + y, cy - x);
	draw_pixel(cx - y, cy - x);
}
/*! Mid-point algorithm*/
void circle(int cx, int cy, int r)
{
	int x = 0;
	int y = r;
	int d = 1 - r;
	int deltaE = 3;
	int deltaSE = -2 * r + 5;
	plot_circle(x, y, cx, cy);
	while (y > x)
	{
		if (d < 0)
		{
			d += deltaE;
			deltaE += 2;
			deltaSE += 2;
		}
		else
		{
			d += deltaSE;
			deltaE += 2;
			deltaSE += 4;
			--y;
		}
		++x;
		plot_circle(x, y, cx, cy);
	}
}
/*!This function draws the circle*/
void primitives::draw_circle(void)
{
	//glClear(GL_COLOR_BUFFER_BIT);
	circle(cx, cy, radius);
	glFlush();
}
/*! This function sets the object to be used as a line between two points(given their x,y coordinates) */
void primitives::use_as_line(int sx1, int sy1, int sx2, int sy2)
{
	x1 = sx1;
	x2 = sx2;
	y1 = sy1;
	y2 = sy2;
	cx = 0;
	cy = 0;
	radius = 0;
}
/*! This function sets the object to be used as a circle with center coordinates and radius*/
void primitives::use_as_circle(int scx, int scy, int sradius)
{
	cx = scx;
	cy = scy;
	radius = sradius;
	x1 = 0;
	x2 = 0;
	y1 = 0;
	y2 = 0;
}
