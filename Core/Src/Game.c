#include "Game.h"

// global position variables
uint16_t x_pos = 120;
uint16_t y_pos = 0;

#define XSTEP	24
#define YSTEP	24

// what shape is active
int shape_is = 0;
int time_seconds = 0;

void gameDelay()
{
	HAL_Delay(500);
}

// main menu
void screenOne()
{
	TIM6_Start();
	// TETRIS Press the Screen to Begin
	LCD_Clear(0, LCD_COLOR_WHITE);
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font16x24);
	LCD_DisplayChar(100,40,'T');
	LCD_DisplayChar(115,40,'E');
	LCD_DisplayChar(130,40,'T');
	LCD_DisplayChar(140,40,'R');
	LCD_DisplayChar(150,40,'I');
	LCD_DisplayChar(160,40,'S');

	LCD_DisplayChar(100,60,'P');
	LCD_DisplayChar(115,60,'r');
	LCD_DisplayChar(125,60,'e');
	LCD_DisplayChar(135,60,'s');
	LCD_DisplayChar(145,60,'s');

	LCD_DisplayChar(100,80,'t');
	LCD_DisplayChar(110,80,'h');
	LCD_DisplayChar(122,80,'e');

	LCD_DisplayChar(100,100,'S');
	LCD_DisplayChar(115,100,'c');
	LCD_DisplayChar(125,100,'r');
	LCD_DisplayChar(135,100,'e');
	LCD_DisplayChar(145,100,'e');
	LCD_DisplayChar(155,100,'n');

	LCD_DisplayChar(100,120,'t');
	LCD_DisplayChar(110,120,'o');

	LCD_DisplayChar(100,140,'B');
	LCD_DisplayChar(110,140,'e');
	LCD_DisplayChar(125,140,'g');
	LCD_DisplayChar(135,140,'i');
	LCD_DisplayChar(145,140,'n');
/*
	drawSquare(0, 296, LCD_COLOR_BLUE);
	drawSquare(24, 296, LCD_COLOR_BLUE);
	drawSquare(48, 296, LCD_COLOR_BLUE);
	drawSquare(72, 296, LCD_COLOR_BLUE);
	drawSquare(96, 296, LCD_COLOR_BLUE);
	drawSquare(120, 296, LCD_COLOR_BLUE);
	drawSquare(144, 296, LCD_COLOR_BLUE);
	drawSquare(168, 296, LCD_COLOR_BLUE);
	drawSquare(192, 296, LCD_COLOR_BLUE);
	drawSquare(216, 296, LCD_COLOR_BLUE);

	drawSquare(0, 272, LCD_COLOR_RED);
	drawSquare(24, 272, LCD_COLOR_RED);
	drawSquare(48, 272, LCD_COLOR_RED);
	drawSquare(72, 272, LCD_COLOR_RED);
	drawSquare(96, 272, LCD_COLOR_RED);
	drawSquare(120, 272, LCD_COLOR_RED);
	drawSquare(144, 272, LCD_COLOR_RED);
	drawSquare(168, 272, LCD_COLOR_RED);
	drawSquare(192, 272, LCD_COLOR_RED);
	drawSquare(216, 272, LCD_COLOR_RED);
*/
	drawShapeO(0, 272, LCD_COLOR_BLUE);
	drawShapeI(72, 224, LCD_COLOR_RED);
	drawShapeS(0, 224, LCD_COLOR_MAGENTA);
	drawShapeZ(96, 272, LCD_COLOR_GREEN);
	drawShapeL(96, 200, LCD_COLOR_BLUE2);
	drawShapeJ(144, 224, LCD_COLOR_RED);
	drawShapeT(168, 272, LCD_COLOR_YELLOW);
}

void endGameScreen()
{
	LCD_Clear(0, LCD_COLOR_RED);
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font16x24);
	LCD_DisplayChar(100,40,'G');
	LCD_DisplayChar(115,40,'A');
	LCD_DisplayChar(130,40,'M');
	LCD_DisplayChar(145,40,'E');

	LCD_DisplayChar(100,60,'O');
	LCD_DisplayChar(115,60,'V');
	LCD_DisplayChar(125,60,'E');
	LCD_DisplayChar(140,60,'R');

	LCD_DisplayChar(10,100,'T');
	LCD_DisplayChar(20,100,'i');
	LCD_DisplayChar(30,100,'m');
	LCD_DisplayChar(40,100,'e');
	LCD_DisplayChar(50,100,':');

	int num_digits = countDigit(time_seconds);
	char buffer[num_digits + 1];  // +1 for null terminator
	itoa(time_seconds, buffer, 10); // Convert time_seconds to string in base 10

	// Display each character of the buffer
	int holder = 60; // Starting x-position for displaying digits
	for (int i = 0; i <= num_digits; i++) {
		LCD_DisplayChar(holder, 100, buffer[i] + '0');
		holder += 10;
	}
}

int countDigit(int n) { // count digits function from G4G
  // Base case
	if (n == 0)
		return 1;

	int count = 0;

	// Iterate till n has digits remaining
	while (n != 0) {

		// Remove rightmost digit
		n = n / 10;

		// Increment digit count by 1
		++count;
	}
	return count;
}


/*
 *  	BEGIN DRAW ALL SHAPES
 */

void drawWhiteSquare(uint16_t x, uint16_t y)
{
	LCD_Draw_Horizontal_Line(x, y, BLOCK_SIDE_LENGTH, LCD_COLOR_WHITE);
	LCD_Draw_Horizontal_Line(x, y + (BLOCK_SIDE_LENGTH - 1), BLOCK_SIDE_LENGTH, LCD_COLOR_WHITE);
	LCD_Draw_Vertical_Line(x, y, BLOCK_SIDE_LENGTH, LCD_COLOR_WHITE);
	LCD_Draw_Vertical_Line(x + (BLOCK_SIDE_LENGTH - 1), y, BLOCK_SIDE_LENGTH, LCD_COLOR_WHITE);
	for (uint16_t i = x+1; i < ((BLOCK_SIDE_LENGTH - 1) + x); i++)
	 {
		for (uint16_t j = y+1; j < ((BLOCK_SIDE_LENGTH - 1) + y); j++)
		{
			LCD_Draw_Pixel(i, j, LCD_COLOR_WHITE);
		}
	 }
}

// use these to check below bottom of shape

// Used to index shapes to rotate
uint16_t index_count = 0;

void drawShapeO(uint16_t x, uint16_t y, uint16_t color) // SQUARE
{
	drawSquare(x, y, color);
	drawSquare(x+24, y, color);
	drawSquare(x, y+24, color);
	drawSquare(x+24, y+24, color);
	index_count = 1;
}
void removeShapeO(uint16_t x, uint16_t y)
{
	drawWhiteSquare(x, y);
	drawWhiteSquare(x+24, y);
	drawWhiteSquare(x, y+24);
	drawWhiteSquare(x+24, y+24);
}



void drawShapeI(uint16_t x, uint16_t y, uint16_t color) // LINE VERT
{
	//int index = 1;
	drawSquare(x, y, color);
	drawSquare(x, y+24, color);
	drawSquare(x, y+48, color);
	drawSquare(x, y+72, color);
	index_count = 2;
}
void removeShapeI(uint16_t x, uint16_t y)
{
	drawWhiteSquare(x, y);
	drawWhiteSquare(x, y+24);
	drawWhiteSquare(x, y+48);
	drawWhiteSquare(x, y+72);
}
void drawShapeI2(uint16_t x, uint16_t y, uint16_t color) // LINE HORZ
{
	//int index = 2;
	drawSquare(x, y, color);
	drawSquare(x+24, y, color);
	drawSquare(x+48, y, color);
	drawSquare(x+72, y, color);
	index_count = 3;
}
void removeShapeI2(uint16_t x, uint16_t y)
{
	drawWhiteSquare(x, y);
	drawWhiteSquare(x+24, y);
	drawWhiteSquare(x+48, y);
	drawWhiteSquare(x+72, y);
}

void drawShapeS(uint16_t x, uint16_t y, uint16_t color) // S UP
{
	//int index = 1;
	drawSquare(x, y+24, color);
	drawSquare(x+24, y+24, color);
	drawSquare(x+24, y, color);
	drawSquare(x+48, y, color);
	index_count = 4;
}
void removeShapeS(uint16_t x, uint16_t y)
{
	drawWhiteSquare(x, y+24);
	drawWhiteSquare(x+24, y+24);
	drawWhiteSquare(x+24, y);
	drawWhiteSquare(x+48, y);
}
void drawShapeS2(uint16_t x, uint16_t y, uint16_t color) // S
{
	//int index = 2;
	drawSquare(x, y, color);
	drawSquare(x, y+24, color);
	drawSquare(x+24, y+24, color);
	drawSquare(x+24, y+48, color);
	index_count = 5;
}
void removeShapeS2(uint16_t x, uint16_t y)
{
	drawWhiteSquare(x, y);
	drawWhiteSquare(x, y+24);
	drawWhiteSquare(x+24, y+24);
	drawWhiteSquare(x+24, y+48);
}
void drawShapeS3(uint16_t x, uint16_t y, uint16_t color) // S
{
	//int index = 3;
	drawSquare(x, y, color);
	drawSquare(x+24, y, color);
	drawSquare(x+24, y+24, color);
	drawSquare(x+48, y+24, color);
	index_count = 6;
}
void removeShapeS3(uint16_t x, uint16_t y)
{
	drawWhiteSquare(x, y);
	drawWhiteSquare(x+24, y);
	drawWhiteSquare(x+24, y+24);
	drawWhiteSquare(x+48, y+24);
}


void drawShapeZ(uint16_t x, uint16_t y, uint16_t color) // Z
{
	//int index = 2;
	drawSquare(x, y, color);
	drawSquare(x+24, y, color);
	drawSquare(x+24, y+24, color);
	drawSquare(x+48, y+24, color);
	index_count = 7;
}
void removeShapeZ(uint16_t x, uint16_t y)
{
	drawWhiteSquare(x, y);
	drawWhiteSquare(x+24, y);
	drawWhiteSquare(x+24, y+24);
	drawWhiteSquare(x+48, y+24);
}
void drawShapeZ2(uint16_t x, uint16_t y, uint16_t color) // Z
{
	//int index = 0;
	drawSquare(x+24, y, color);
	drawSquare(x+24, y+24, color);
	drawSquare(x, y+24, color);
	drawSquare(x, y+48, color);
	index_count = 8;
}
void removeShapeZ2(uint16_t x, uint16_t y)
{
	drawWhiteSquare(x+24, y);
	drawWhiteSquare(x+24, y+24);
	drawWhiteSquare(x, y+24);
	drawWhiteSquare(x, y+48);
}
void drawShapeZ3(uint16_t x, uint16_t y, uint16_t color) // Z
{
	//int index = 0;
	drawSquare(x, y+24, color);
	drawSquare(x+24, y+24, color);
	drawSquare(x+24, y, color);
	drawSquare(x+48, y, color);
	index_count = 9;
}
void removeShapeZ3(uint16_t x, uint16_t y)
{
	drawWhiteSquare(x, y+24);
	drawWhiteSquare(x+24, y+24);
	drawWhiteSquare(x+24, y);
	drawWhiteSquare(x+48, y);
}



void drawShapeL(uint16_t x, uint16_t y, uint16_t color) // L
{
	drawSquare(x, y, color);
	drawSquare(x, y+24, color);
	drawSquare(x, y+48, color);
	drawSquare(x+24, y+48, color);
	index_count = 10;
}
void removeShapeL(uint16_t x, uint16_t y)
{
	drawWhiteSquare(x, y);
	drawWhiteSquare(x, y+24);
	drawWhiteSquare(x, y+48);
	drawWhiteSquare(x+24, y+48);
}
void drawShapeL2(uint16_t x, uint16_t y, uint16_t color) // L
{
	drawSquare(x, y+24, color);
	drawSquare(x+24, y+24, color);
	drawSquare(x+48, y+24, color);
	drawSquare(x+48, y, color);
	index_count = 11;
}
void removeShapeL2(uint16_t x, uint16_t y)
{
	drawWhiteSquare(x, y+24);
	drawWhiteSquare(x+24, y+24);
	drawWhiteSquare(x+48, y+24);
	drawWhiteSquare(x+48, y);
}
void drawShapeL3(uint16_t x, uint16_t y, uint16_t color) // L
{
	drawSquare(x, y, color);
	drawSquare(x, y+24, color);
	drawSquare(x, y+48, color);
	drawSquare(x+24, y, color);
	index_count = 12;
}
void removeShapeL3(uint16_t x, uint16_t y)
{
	drawWhiteSquare(x, y);
	drawWhiteSquare(x, y+24);
	drawWhiteSquare(x, y+48);
	drawWhiteSquare(x+24, y);
}
void drawShapeL4(uint16_t x, uint16_t y, uint16_t color) // L
{
	drawSquare(x, y, color);
	drawSquare(x, y+24, color);
	drawSquare(x+24, y, color);
	drawSquare(x+48, y, color);
	index_count = 13;
}
void removeShapeL4(uint16_t x, uint16_t y)
{
	drawWhiteSquare(x, y);
	drawWhiteSquare(x, y+24);
	drawWhiteSquare(x+24, y);
	drawWhiteSquare(x+48, y);
}



void drawShapeJ(uint16_t x, uint16_t y, uint16_t color) // J
{
	drawSquare(x+24, y, color);
	drawSquare(x+24, y+24, color);
	drawSquare(x+24, y+48, color);
	drawSquare(x, y+48, color);
	index_count = 14;
}
void removeShapeJ(uint16_t x, uint16_t y)
{
	drawWhiteSquare(x+24, y);
	drawWhiteSquare(x+24, y+24);
	drawWhiteSquare(x+24, y+48);
	drawWhiteSquare(x, y+48);
}
void drawShapeJ2(uint16_t x, uint16_t y, uint16_t color) // J
{
	drawSquare(x, y, color);
	drawSquare(x, y+24, color);
	drawSquare(x+24, y+24, color);
	drawSquare(x+48, y+24, color);
	index_count = 15;
}
void removeShapeJ2(uint16_t x, uint16_t y)
{
	drawWhiteSquare(x, y);
	drawWhiteSquare(x, y+24);
	drawWhiteSquare(x+24, y+24);
	drawWhiteSquare(x+48, y+24);
}
void drawShapeJ3(uint16_t x, uint16_t y, uint16_t color) // J
{
	drawSquare(x, y, color);
	drawSquare(x+24, y, color);
	drawSquare(x, y+24, color);
	drawSquare(x, y+48, color);
	index_count = 16;
}
void removeShapeJ3(uint16_t x, uint16_t y)
{
	drawWhiteSquare(x, y);
	drawWhiteSquare(x+24, y);
	drawWhiteSquare(x, y+24);
	drawWhiteSquare(x, y+48);
}
void drawShapeJ4(uint16_t x, uint16_t y, uint16_t color) // J
{
	drawSquare(x, y, color);
	drawSquare(x+24, y, color);
	drawSquare(x+48, y, color);
	drawSquare(x+48, y+24, color);
	index_count = 17;
}
void removeShapeJ4(uint16_t x, uint16_t y)
{
	drawWhiteSquare(x, y);
	drawWhiteSquare(x+24, y);
	drawWhiteSquare(x+48, y);
	drawWhiteSquare(x+48, y+24);
}



void drawShapeT(uint16_t x, uint16_t y, uint16_t color) // T
{
	drawSquare(x+24, y, color);
	drawSquare(x, y+24, color);
	drawSquare(x+24, y+24, color);
	drawSquare(x+48, y+24, color);
	index_count = 18;
}
void removeShapeT(uint16_t x, uint16_t y)
{
	drawWhiteSquare(x+24, y);
	drawWhiteSquare(x, y+24);
	drawWhiteSquare(x+24, y+24);
	drawWhiteSquare(x+48, y+24);
}
void drawShapeT2(uint16_t x, uint16_t y, uint16_t color) // T
{
	drawSquare(x, y, color);
	drawSquare(x, y+24, color);
	drawSquare(x+24, y+24, color);
	drawSquare(x, y+48, color);
	index_count = 19;
}
void removeShapeT2(uint16_t x, uint16_t y)
{
	drawWhiteSquare(x, y);
	drawWhiteSquare(x, y+24);
	drawWhiteSquare(x+24, y+24);
	drawWhiteSquare(x, y+48);
}
void drawShapeT3(uint16_t x, uint16_t y, uint16_t color) // T
{
	drawSquare(x, y, color);
	drawSquare(x+24, y, color);
	drawSquare(x+48, y, color);
	drawSquare(x+24, y+24, color);
	index_count = 20;
}
void removeShapeT3(uint16_t x, uint16_t y)
{
	drawWhiteSquare(x, y);
	drawWhiteSquare(x+24, y);
	drawWhiteSquare(x+48, y);
	drawWhiteSquare(x+24, y+24);
}
void drawShapeT4(uint16_t x, uint16_t y, uint16_t color) // T
{
	drawSquare(x+24, y, color);
	drawSquare(x+24, y+24, color);
	drawSquare(x+24, y+48, color);
	drawSquare(x, y+24, color);
	index_count = 21;
}
void removeShapeT4(uint16_t x, uint16_t y)
{
	drawWhiteSquare(x+24, y);
	drawWhiteSquare(x+24, y+24);
	drawWhiteSquare(x+24, y+48);
	drawWhiteSquare(x, y+24);
}

/*
 * 		END DRAW ALL SHAPES
 */

void drawRandomShape()
{
	uint32_t num = generateRandomNum();
	num %= 7;
	if (num == 0)
	{
		drawShapeO(120, 0, LCD_COLOR_BLUE);
		shape_is = 1;
	}
	else if (num == 1)
	{
		drawShapeI(120, 0, LCD_COLOR_BLUE);
		shape_is = 2;
	}
	else if (num == 2)
	{
		drawShapeS(120, 0, LCD_COLOR_BLUE);
		shape_is = 3;
	}
	else if (num == 3)
	{
		drawShapeZ(120, 0, LCD_COLOR_BLUE);
		shape_is = 4;
	}
	else if (num == 4)
	{
		drawShapeL(120, 0, LCD_COLOR_BLUE);
		shape_is = 5;
	}
	else if (num == 5)
	{
		drawShapeJ(120, 0, LCD_COLOR_BLUE);
		shape_is = 6;
	}
	else if (num == 6)
	{
		drawShapeT(120, 0, LCD_COLOR_BLUE);
		shape_is = 7;
	}
}

void rotateShape()
{
	if (shape_is == 1)
	{
		switch (index_count)
		{
		default:
			break;
		}
	}
	else if (shape_is == 2)
	{
		switch (index_count)
		{
		case 2:
			removeShapeI(x_pos, y_pos);
			drawShapeI2(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 3:
			removeShapeI2(x_pos, y_pos);
			drawShapeI(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		default:
			break;
		}
	}
	else if (shape_is == 3)
	{
		switch(index_count)
		{
		case 4:
			removeShapeS(x_pos, y_pos);
			drawShapeS2(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 5:
			removeShapeS2(x_pos, y_pos);
			drawShapeS3(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 6:
			removeShapeS3(x_pos, y_pos);
			drawShapeS(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		default:
			break;
		}
	}
	else if (shape_is == 4)
	{
		switch(index_count)
		{
		case 7:
			removeShapeZ(x_pos, y_pos);
			drawShapeZ2(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 8:
			removeShapeZ2(x_pos, y_pos);
			drawShapeZ3(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 9:
			removeShapeZ3(x_pos, y_pos);
			drawShapeZ(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		default:
			break;
		}
	}
	else if (shape_is == 5)
	{
		switch(index_count)
		{
		case 10:
			removeShapeL(x_pos, y_pos);
			drawShapeL2(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 11:
			removeShapeL2(x_pos, y_pos);
			drawShapeL3(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 12:
			removeShapeL3(x_pos, y_pos);
			drawShapeL4(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 13:
			removeShapeL4(x_pos, y_pos);
			drawShapeL(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		default:
			break;
		}
	}
	else if (shape_is == 6)
	{
		switch(index_count)
		{
		case 14:
			removeShapeJ(x_pos, y_pos);
			drawShapeJ2(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 15:
			removeShapeJ2(x_pos, y_pos);
			drawShapeJ3(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 16:
			removeShapeJ3(x_pos, y_pos);
			drawShapeJ4(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 17:
			removeShapeJ4(x_pos, y_pos);
			drawShapeJ(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		default:
			break;
		}
	}
	else if (shape_is == 7)
	{
		switch(index_count)
		{
		case 18:
			removeShapeT(x_pos, y_pos);
			drawShapeT2(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 19:
			removeShapeT2(x_pos, y_pos);
			drawShapeT3(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 20:
			removeShapeT3(x_pos, y_pos);
			drawShapeT4(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 21:
			removeShapeT4(x_pos, y_pos);
			drawShapeT(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		default:
			break;
		}
	}
}

void moveDownOne()
{
	y_pos += YSTEP;
	if (shape_is == 1){
		switch(index_count)
		{
		case 1:
			removeShapeO(x_pos, y_pos - YSTEP);
			drawShapeO(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		}
	}
	else if (shape_is == 2) {
		switch(index_count)
		{
		case 2:
			removeShapeI(x_pos, y_pos - YSTEP);
			drawShapeI(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 3:
			removeShapeI2(x_pos, y_pos - YSTEP);
			drawShapeI2(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		}
	}
	else if (shape_is == 3){
		switch(index_count)
		{
		case 4:
			removeShapeS(x_pos, y_pos - YSTEP);
			drawShapeS(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 5:
			removeShapeS2(x_pos, y_pos - YSTEP);
			drawShapeS2(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 6:
			removeShapeS3(x_pos, y_pos - YSTEP);
			drawShapeS3(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		}
	}
	else if (shape_is == 4){
		switch(index_count)
		{
		case 7:
			removeShapeZ(x_pos, y_pos - YSTEP);
			drawShapeZ(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 8:
			removeShapeZ2(x_pos, y_pos - YSTEP);
			drawShapeZ2(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 9:
			removeShapeZ3(x_pos, y_pos - YSTEP);
			drawShapeZ3(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		}
	}
	else if (shape_is == 5){
		switch(index_count)
		{
		case 10:
			removeShapeL(x_pos, y_pos - YSTEP);
			drawShapeL(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 11:
			removeShapeL2(x_pos, y_pos - YSTEP);
			drawShapeL2(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 12:
			removeShapeL3(x_pos, y_pos - YSTEP);
			drawShapeL3(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 13:
			removeShapeL4(x_pos, y_pos - YSTEP);
			drawShapeL4(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		}

	}
	else if (shape_is == 6){
		switch(index_count)
		{
		case 14:
			removeShapeJ(x_pos, y_pos - YSTEP);
			drawShapeJ(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 15:
			removeShapeJ2(x_pos, y_pos - YSTEP);
			drawShapeJ2(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 16:
			removeShapeJ3(x_pos, y_pos - YSTEP);
			drawShapeJ3(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 17:
			removeShapeJ4(x_pos, y_pos - YSTEP);
			drawShapeJ4(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		}
	}
	else if (shape_is == 7){
		switch(index_count)
		{
		case 18:
			removeShapeT(x_pos, y_pos - YSTEP);
			drawShapeT(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 19:
			removeShapeT2(x_pos, y_pos - YSTEP);
			drawShapeT2(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 20:
			removeShapeT3(x_pos, y_pos - YSTEP);
			drawShapeT3(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 21:
			removeShapeT4(x_pos, y_pos - YSTEP);
			drawShapeT4(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		}
	}
}

void moveOneLeft()
{
	x_pos -= 24;
	if (shape_is == 1){
		switch(index_count)
		{
		case 1:
			removeShapeO(x_pos + 24, y_pos);
			drawShapeO(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		}
	}
	else if (shape_is == 2){
		switch(index_count)
		{
		case 2:
			removeShapeI(x_pos +24, y_pos);
			drawShapeI(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 3:
			removeShapeI2(x_pos+24, y_pos);
			drawShapeI2(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		}

	}
	else if (shape_is == 3){
		switch(index_count)
		{
		case 4:
			removeShapeS(x_pos+24, y_pos );
			drawShapeS(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 5:
			removeShapeS2(x_pos+24, y_pos);
			drawShapeS2(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 6:
			removeShapeS3(x_pos+24, y_pos );
			drawShapeS3(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		}
	}
	else if (shape_is == 4){
		switch(index_count)
		{
		case 7:
			removeShapeZ(x_pos+24, y_pos);
			drawShapeZ(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 8:
			removeShapeZ2(x_pos+24, y_pos);
			drawShapeZ2(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 9:
			removeShapeZ3(x_pos+24, y_pos);
			drawShapeZ3(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		}
	}
	else if (shape_is == 5){
		switch(index_count)
		{
		case 10:
			removeShapeL(x_pos+24, y_pos);
			drawShapeL(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 11:
			removeShapeL2(x_pos+24, y_pos);
			drawShapeL2(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 12:
			removeShapeL3(x_pos+24, y_pos);
			drawShapeL3(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 13:
			removeShapeL4(x_pos+24, y_pos);
			drawShapeL4(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		}

	}
	else if (shape_is == 6){
		switch(index_count)
		{
		case 14:
			removeShapeJ(x_pos+24, y_pos);
			drawShapeJ(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 15:
			removeShapeJ2(x_pos+24, y_pos);
			drawShapeJ2(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 16:
			removeShapeJ3(x_pos+24, y_pos);
			drawShapeJ3(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 17:
			removeShapeJ4(x_pos+24, y_pos);
			drawShapeJ4(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		}
	}
	else if (shape_is == 7){
		switch(index_count)
		{
		case 18:
			removeShapeT(x_pos+24, y_pos);
			drawShapeT(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 19:
			removeShapeT2(x_pos+24, y_pos);
			drawShapeT2(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 20:
			removeShapeT3(x_pos+24, y_pos);
			drawShapeT3(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		case 21:
			removeShapeT4(x_pos+24, y_pos);
			drawShapeT4(x_pos, y_pos, LCD_COLOR_BLUE);
			break;
		}
	}
}

void moveOneRight()
{
	x_pos += 24;
	if (shape_is == 1){
			switch(index_count)
			{
			case 1:
				removeShapeO(x_pos-24, y_pos);
				drawShapeO(x_pos, y_pos, LCD_COLOR_BLUE);
				break;
			}
		}
		else if (shape_is == 2){
			switch(index_count)
			{
			case 2:
				removeShapeI(x_pos-24, y_pos);
				drawShapeI(x_pos, y_pos, LCD_COLOR_BLUE);
				break;
			case 3:
				removeShapeI2(x_pos-24, y_pos );
				drawShapeI2(x_pos, y_pos, LCD_COLOR_BLUE);
				break;
			}

		}
		else if (shape_is == 3){
			switch(index_count)
			{
			case 4:
				removeShapeS(x_pos-24, y_pos );
				drawShapeS(x_pos, y_pos, LCD_COLOR_BLUE);
				break;
			case 5:
				removeShapeS2(x_pos-24, y_pos);
				drawShapeS2(x_pos, y_pos, LCD_COLOR_BLUE);
				break;
			case 6:
				removeShapeS3(x_pos-24, y_pos );
				drawShapeS3(x_pos, y_pos, LCD_COLOR_BLUE);
				break;
			}
		}
		else if (shape_is == 4){
			switch(index_count)
			{
			case 7:
				removeShapeZ(x_pos-24, y_pos);
				drawShapeZ(x_pos, y_pos, LCD_COLOR_BLUE);
				break;
			case 8:
				removeShapeZ2(x_pos-24, y_pos);
				drawShapeZ2(x_pos, y_pos, LCD_COLOR_BLUE);
				break;
			case 9:
				removeShapeZ3(x_pos-24, y_pos);
				drawShapeZ3(x_pos, y_pos, LCD_COLOR_BLUE);
				break;
			}
		}
		else if (shape_is == 5){
			switch(index_count)
			{
			case 10:
				removeShapeL(x_pos-24, y_pos);
				drawShapeL(x_pos, y_pos, LCD_COLOR_BLUE);
				break;
			case 11:
				removeShapeL2(x_pos-24, y_pos);
				drawShapeL2(x_pos, y_pos, LCD_COLOR_BLUE);
				break;
			case 12:
				removeShapeL3(x_pos-24, y_pos);
				drawShapeL3(x_pos, y_pos, LCD_COLOR_BLUE);
				break;
			case 13:
				removeShapeL4(x_pos-24, y_pos);
				drawShapeL4(x_pos, y_pos, LCD_COLOR_BLUE);
				break;
			}
		}
		else if (shape_is == 6){
			switch(index_count)
			{
			case 14:
				removeShapeJ(x_pos-24, y_pos);
				drawShapeJ(x_pos, y_pos, LCD_COLOR_BLUE);
				break;
			case 15:
				removeShapeJ2(x_pos-24, y_pos);
				drawShapeJ2(x_pos, y_pos, LCD_COLOR_BLUE);
				break;
			case 16:
				removeShapeJ3(x_pos-24, y_pos);
				drawShapeJ3(x_pos, y_pos, LCD_COLOR_BLUE);
				break;
			case 17:
				removeShapeJ4(x_pos-24, y_pos);
				drawShapeJ4(x_pos, y_pos, LCD_COLOR_BLUE);
				break;
			}
		}
		else if (shape_is == 7){
			switch(index_count)
			{
			case 18:
				removeShapeT(x_pos-24, y_pos);
				drawShapeT(x_pos, y_pos, LCD_COLOR_BLUE);
				break;
			case 19:
				removeShapeT2(x_pos-24, y_pos);
				drawShapeT2(x_pos, y_pos, LCD_COLOR_BLUE);
				break;
			case 20:
				removeShapeT3(x_pos-24, y_pos);
				drawShapeT3(x_pos, y_pos, LCD_COLOR_BLUE);
				break;
			case 21:
				removeShapeT4(x_pos-24, y_pos);
				drawShapeT4(x_pos, y_pos, LCD_COLOR_BLUE);
				break;
			}
		}
}

bool row_done = false;

void Row_Check_Delete()
{
	int count;
	for (int y=12; y<308; y+=24) {
		count = 0;
		for (int x=12; x<240; x+=24) {
			if (LCD_Read_Pixel(x, y) == LCD_COLOR_BLUE) {count++;}
			if (count == 10)
			{
				row_done = true;
				for(x=0; x<240; x+=24)
				{
					switch(index_count)
					{
					case 1:
						drawWhiteSquare(x, y_pos+24);
						break;
					case 2:
						drawWhiteSquare(x, y_pos+72);
						break;
					case 3:
						drawWhiteSquare(x, y_pos+24);
						break;
					case 4:
						drawWhiteSquare(x, y_pos+48);
						break;
					case 5:
						drawWhiteSquare(x, y_pos+48);
						break;
					case 6:
						drawWhiteSquare(x, y_pos+24);
						break;
					case 7:
						drawWhiteSquare(x, y_pos+24);
						break;
					case 8:
						drawWhiteSquare(x, y_pos+48);
						break;
					case 9:
						drawWhiteSquare(x, y_pos+24);
						break;
					case 10:
						drawWhiteSquare(x, y_pos+48);
						break;
					case 11:
						drawWhiteSquare(x, y_pos+24);
						break;
					case 12:
						drawWhiteSquare(x, y_pos+48);
						break;
					case 13:
						drawWhiteSquare(x, y_pos+24);
						break;
					case 14:
						drawWhiteSquare(x, y_pos+48);
						break;
					case 15:
						drawWhiteSquare(x, y_pos+24);
						break;
					case 16:
						drawWhiteSquare(x, y_pos+48);
						break;
					case 17:
						drawWhiteSquare(x, y_pos+24);
						break;
					case 18:
						drawWhiteSquare(x, y_pos+24);
						break;
					case 19:
						drawWhiteSquare(x, y_pos+48);
						break;
					case 20:
						drawWhiteSquare(x, y_pos+24);
						break;
					case 21:
						drawWhiteSquare(x, y_pos+48);
						break;
					}
				}
			}
		}
	}
}

bool White_Space_Below()
{
	uint16_t color = 0;
	switch(index_count) // each case specifies low point on shape & (y+1) to look one pixel below shape
	{
	case 1:
		color = LCD_Read_Pixel(x_pos+10, y_pos+49);
		break;
	case 2:
		color = LCD_Read_Pixel(x_pos+10, y_pos+98);
		break;
	case 3:
		color = LCD_Read_Pixel(x_pos+10, y_pos+25);
		break;
	case 4:
		color = LCD_Read_Pixel(x_pos+10, y_pos+49);
		break;
	case 5:
		color = LCD_Read_Pixel(x_pos+10, y_pos+73);
		break;
	case 6:
		color = LCD_Read_Pixel(x_pos+10, y_pos+49);
		break;
	case 7:
		color = LCD_Read_Pixel(x_pos+25, y_pos+49);
		break;
	case 8:
		color = LCD_Read_Pixel(x_pos+25, y_pos+73);
		break;
	case 9:
		color = LCD_Read_Pixel(x_pos+10, y_pos+49);
		break;
	case 10:
		color = LCD_Read_Pixel(x_pos+10, y_pos+73);
		break;
	case 11:
		color = LCD_Read_Pixel(x_pos+10, y_pos+49);
		break;
	case 12:
		color = LCD_Read_Pixel(x_pos+10, y_pos+73);
		break;
	case 13:
		color = LCD_Read_Pixel(x_pos+10, y_pos+49);
		break;
	case 14:
		color = LCD_Read_Pixel(x_pos+10, y_pos+73);
		break;
	case 15:
		color = LCD_Read_Pixel(x_pos+10, y_pos+49);
		break;
	case 16:
		color = LCD_Read_Pixel(x_pos+10, y_pos+73);
		break;
	case 17:
		color = LCD_Read_Pixel(x_pos+10, y_pos+49);
		break;
	case 18:
		color = LCD_Read_Pixel(x_pos+10, y_pos+49);
		break;
	case 19:
		color = LCD_Read_Pixel(x_pos+10, y_pos+73);
		break;
	case 20:
		color = LCD_Read_Pixel(x_pos+25, y_pos+49);
		break;
	case 21:
		color = LCD_Read_Pixel(x_pos+10, y_pos+73);
		break;
	}
	if (color == LCD_COLOR_WHITE) {
		return true;
	}
	else {
		return false;
	}
}

bool game_started = false;

void executeGame()
{
	game_started = true;
	y_pos = 0;
	x_pos = 120;
	drawRandomShape();
	while(White_Space_Below() == true)
	{
		moveDownOne();
		gameDelay(); // make this 3000 for submission
		Row_Check_Delete();
		if (row_done == true)
		{
			HAL_Delay(1000);
			TIM6_Stop();
			endGameScreen();
			game_started = false;
			exit(0);
		}
	}
}
TIM_HandleTypeDef htim6;
/////////// TIM6 IRQ HANDLER ///////////////
void TIM6_DAC_IRQHandler()
{
	htim6.Instance = TIM6;
	HAL_TIM_IRQHandler(&htim6);
	time_seconds++;
}
