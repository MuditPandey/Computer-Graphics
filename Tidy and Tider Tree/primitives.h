#pragma once
class primitives
{
	/* !X coordinate of first point*/
	int x1;
	/*! Y coordinate of first point*/
	int y1;
	/*! X coordinate of second point*/
	int x2;
	/*! Y coordinate of second point*/
	int y2;
	/*! X coordinate of center of circle*/
	int cx;
	/*! Y coordinate of center of circle*/
	int cy;
	/*! Radius of circle*/
	int radius;
public:
	/*! This function sets the object to be used as a circle with center coordinates and radius*/
	void use_as_circle(int, int, int);
	/*! This function sets the object to be used as a line between two points(given their x,y coordinates) */
	void use_as_line(int, int, int, int);
	/*!This function draws the line*/
	void draw_line();
	/*!This function draws the circle*/
	void draw_circle();
};

