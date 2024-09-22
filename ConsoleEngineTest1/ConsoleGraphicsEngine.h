#pragma once

#include<windows.h>;
#include<memory.h>;
#include <iostream>
#include "Vec2.h"

using namespace std;
//enum color stores the color values to insert to the set color method (MUCH EASIER)
enum COLOR
{
	FG_BLACK = 0x0000,
	FG_DARK_BLUE = 0x0001,
	FG_DARK_GREEN = 0x0002,
	FG_DARK_CYAN = 0x0003,
	FG_DARK_RED = 0x0004,
	FG_DARK_MAGENTA = 0x0005,
	FG_DARK_YELLOW = 0x0006,
	FG_GREY = 0x0007, 
	FG_DARK_GREY = 0x0008,
	FG_BLUE = 0x0009,
	FG_GREEN = 0x000A,
	FG_CYAN = 0x000B,
	FG_RED = 0x000C,
	FG_MAGENTA = 0x000D,
	FG_YELLOW = 0x000E,
	FG_WHITE = 0x000F,
	BG_BLACK = 0x0000,
	BG_DARK_BLUE = 0x0010,
	BG_DARK_GREEN = 0x0020,
	BG_DARK_CYAN = 0x0030,
	BG_DARK_RED = 0x0040,
	BG_DARK_MAGENTA = 0x0050,
	BG_DARK_YELLOW = 0x0060,
	BG_GREY = 0x0070,
	BG_DARK_GREY = 0x0080,
	BG_BLUE = 0x0090,
	BG_GREEN = 0x00A0,
	BG_CYAN = 0x00B0,
	BG_RED = 0x00C0,
	BG_MAGENTA = 0x00D0,
	BG_YELLOW = 0x00E0,
	BG_WHITE = 0x00F0,
};
// KEY stores the values for certain keys
enum KEY {LSHIFT = 160, LCONTROL = 162, RSHIFT = 161, RCONTROL = 163, UP = 38, LEFT = 37, DOWN = 40, RIGHT = 39, ESC = 27};

/*
*	class used to draw to the console as well as access infomation about
*	which keys are pressed
*/
class ConsoleGraphicsEngine
{
	
		
public:
	short width, height;				//dimensions of screen
	CHAR_INFO* display = nullptr;		//contains character information to display to screen
	HANDLE window;						
	SMALL_RECT writeArea;				//struct that contains sides of rectangle(area you write to)
	WORD color = 15;					//C O L O R
	CONSOLE_SCREEN_BUFFER_INFO csbi;	//contains information about a console screen buffer 
	
	bool keys[256] = {0};						//store state of all keys (pressed or not)

	/* 
	* Constructor that sets up for the console being used as
	* a real time graphics display
	* 
	* @param width1 : The width (in characters) of the console
	* @param height1 : The height (in characters) of the console
	* @param fontSizeX : The Width of every character
	* @param fontSizeY : The Height of every character
	*/
	ConsoleGraphicsEngine(const int width1, const int height1, const int fontSizeX, const int fontSizeY);

	/*
	* updates the array that holds the current state of keys being held
	*/
	void updateKeyState();

	/*
	* changes font size in the console
	* 
	* @param width : changes the width (pixels) of each character in the console
	* @param height : changes the height (pixels) of each character in the console
	*/ 
	void setFont(const double width, const double height);

	/*
	* updates the console (displays currently drawn screen)
	*/ 
	void render();

	/*
	* sets every "pixel" of screen to one char(used to clear the screen at the beginning of every draw)
	* 
	* @param : c character that the background will be replaced with
	*/	
	void clear(const char c);

	/*
	* sets space in array to a certain char (modified for asteroids, pixels placed out
	* of the screen will wrap to the other side)
	* 
	* @param : x the x position of the pixel
	* @param : y the y position of the pixel 
	* @param : c the character that will be drawn
	*/
	void setPixel(int x, int y, const int c);

	/*
	* draws rectangle
	*
	* @param : x the left of the rectangle
	* @param : y the top of the rectangle
	* @param : width the width of the rectangle
	* @param : height the height of the rectangle
	* @param : c the character that will be drawn
	*/
	void drawRectangle(const int x, const int y, const int width, const int height, const int c);

	/*
	* writes a string to the screen (top left = (x,y))
	* sidenote, \n will continue to write the string on the next line	(useful ASCII Art)
	* 
	* @param x  : the x position of the beggining of the string
	* @param y  : the y position of the beggining of the string
	* @param str : the string being drawn (the \n character will draw more of the string on the
	*	next line)
	*/
	void drawString(const int x, const int y, const string& str);

	/* 
	* draws line from point (x1, y1) to (x2, y2)
	* 
	* @param x1 : the x position of point 1
	* @param x1 : the y position of point 1
	* @param x2 : the y position of point 2
	* @param x2 : the x position of point 2
	* @param c : the character being drawn
	*/
	void drawLine(int x1, int y1, int x2, int y2, const char c);

	/*
	* draws line using vectors as parameters
	*
	* @param point1 : the first point of the line
	* @param point2 : the second point of the line
	* @param c : the character being drawn
	*/
	void drawLine(Vec2 point1, Vec2 point2, char c);

	/*
	* sets the curent color selected for drawing (all draw methods will use the currently
	* selected color)
	* 
	* @param charColor : color of the character
	* @param backgroundColor : background(Highlight) color of the character 
	*/
	void setColor(int charColor, int backroundColor);

	/*
	* sets the curent color selected for drawing (all draw methods will use the currently
	* selected color)
	*
	* @param color1 : The color of the character that will be used for drawing
	* (Adding a background color and character color together will set them both in
	* this method)
	*/
	void setColor(int color1);
	
};


