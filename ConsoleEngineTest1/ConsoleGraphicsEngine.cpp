#include "ConsoleGraphicsEngine.h"
#include <chrono>

ConsoleGraphicsEngine::ConsoleGraphicsEngine(const int width1, const int height1, const int fontSizeX, const int fontSizeY) {
	
	
	setFont(fontSizeX, fontSizeY);
	window = GetStdHandle(STD_OUTPUT_HANDLE);
	width = width1;
	height = height1;



	writeArea = { 0, 0, (short)(width-1), (short)(height-1) };

	

	SetConsoleScreenBufferSize(window, { width, height });
	SetConsoleWindowInfo(window, TRUE, &writeArea);
	
	if (GetConsoleScreenBufferInfo(window, &csbi)) {

		display = (CHAR_INFO*)malloc(sizeof(CHAR_INFO) * width * height);

	}
	else {
		display = nullptr;
		std::cout << "Something went wrong" << std::endl;
	}
	
}

void ConsoleGraphicsEngine::updateKeyState() {
	for (int i = 0; i < 256; i++) {
		keys[i] = GetAsyncKeyState(i); //GetAsyncKeyState returns a boolean value depending on if the key in the parameter is held. (represented as an int)
	}
}

void ConsoleGraphicsEngine::setFont(const double width, const double height) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = width;					//character width
	cfi.dwFontSize.Y = height;					//character height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");	// Choose your font (Terminal)(consolas)
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &cfi);

	
}

void ConsoleGraphicsEngine::render() {
	WriteConsoleOutput(window, display, { width, height }, { 0, 0 }, &writeArea);
};

void ConsoleGraphicsEngine::clear(const char c) {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {

			//ever try displaying 2d image in 1d array? Someone thought it was a good idea because the WriteConsoleOutput() function
			//takes in a 1d array of CHAR_INFO
																			//    0  1  2
			//y*width+x brings you to correct location in 1d array			// 0 [0][1][2]	<-- 1d array drawn in 2D
			display[y * width + x].Char.UnicodeChar = c;					// 1 [3][4][5]		y*width+x = arr index	
			display[y * width + x].Attributes = color;						// 2 [6][7][8]
		}
	}
}

void ConsoleGraphicsEngine::setPixel(int x, int y, const int c) {

	// modified for asteroids to make seamless screen wrapping 
	// (if a pixel is drawn out of frame, it will be transformed to the other side)
	if (x > width - 1) {
		x -= width;
	}
	if (x < 0) {
		x += width;
	}
	if (y > height - 1) {
		y -= height;
	}
	if (y < 0) {
		y += height;
	}
	if (x >= 0 && y >= 0 && x < width && y < height) {	//checks to make sure it is in bounds (will do nothing otherwise)
		display[y * width + x].Char.UnicodeChar = c;
		display[y * width + x].Attributes = color;		//thats right, the CHAR_INFO struct contains color
	}

}

void ConsoleGraphicsEngine::drawRectangle(const int x, const int y, const int width, const int height, const int c) {
	// nested for loop loops through a rectangle to draw it to the screen
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			setPixel(x + j, y + i, c);
		}
	}
}

void ConsoleGraphicsEngine::drawString(const int x, const int y, const string& str) {

	int tempX = 0;
	int tempY = 0;

	for (int i = 0; i < str.size(); i++) {	//loops throught string putting 1 char on 1 pixel on the screen

		if (str[i] == '\n') { //handles \n (goes back to original x position and goes down a line. allows you to use ASCII "sprites")
			tempY++;
			tempX = 0;

		}
		else if (str[i] == ' ') { //will not print spaces
			tempX++;
			continue;
		}
		else {					//sets pixel to char

			// inseted code to make drawing the score easier (sorry, bad practice magically
				// mapping 1 and 0 to white and black pixels for no reason)
			if (str[i] == '1') {
				color = COLOR(FG_WHITE) + COLOR(BG_WHITE);
			}
			else if (str[i] == '0') {
				color = COLOR(FG_BLACK) + COLOR(BG_BLACK);
			}
			setPixel(x + tempX, y + tempY, str[i]);
			tempX++;
		}
	}
}

void ConsoleGraphicsEngine::drawLine(int x1, int y1, int x2, int y2, const char c) {

	double m;
	double b;
	double disTraversed;


	// make point1 (x1, x2) be on the left
	if (x2 < x1) {
		swap(x1, x2);
		swap(y1, y2);
	}
	// if the line is not vertical, find the slope of the line and the vertical offset from the origin (y = mx + b)
	if (x1 != x2) {
		m = (y2 - y1) / (double)(x2 - x1);
		b = y1 - m * x1 + .5;

		// if the magnitude of the slope is greater than one, the x distance per step will be less than one
		// otherwise, you can assume the line will step one pixel across the x axis
		if (abs(m) > 1) {
			disTraversed = 1 / (abs(m));
		}
		else {
			disTraversed = 1;
		}

		// loop through drawing pixels untill the x value that would be drawn 
		// to is greater than the x2 parameter (the right point)
		for (double x = x1; x <= x2 + disTraversed / 2; x += disTraversed) {

			setPixel(x + .5, m * x + b, c);
		}
	}
	else {
		// since the line is vertical in this branch, loop from the bottom point to the top point
		if (y1 > y2) {
			for (int i = y2; i <= y1; i++) {
				setPixel(x1, i, c);
			}
		}
		else {
			for (int i = y1; i <= y2; i++) {
				setPixel(x1, i, c);
			}
		}
	}
}

void ConsoleGraphicsEngine::drawLine(Vec2 point1, Vec2 point2, char c) {
	drawLine(point1.x, point1.y, point2.x, point2.y, c);
}

void ConsoleGraphicsEngine::setColor(int charColor, int backroundColor) {
	color = charColor + backroundColor;
}

void ConsoleGraphicsEngine::setColor(int color1) {
	color = color1;
}
