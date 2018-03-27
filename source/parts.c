#include <3ds.h>
#include "parts.h"
#include <stdlib.h>

colors white = { 0xFF, 0xFF, 0xFF};
colors black = {  0x0,  0x0,  0x0};
colors blue  = { 0xFF,  0x0,  0x0};
colors red   = {  0x0,  0x0, 0xFF};

colors snakeGreen = { 13, 215, 13};
colors snakeStripes = { 00, 36, 05};

int headSprite[10][10] = {
	{ 0, 0, 2, 3, 2, 2, 2, 2, 0, 0},
	{ 0, 0, 2, 2, 3, 2, 2, 2, 0, 0},
	{ 0, 2, 2, 2, 2, 2, 2, 2, 2, 0},
	{ 0, 2, 1, 1, 2, 2, 1, 1, 2, 0},
	{ 0, 2, 1, 4, 2, 2, 4, 1, 2, 0},
	{ 0, 2, 2, 2, 2, 2, 2, 2, 2, 0},
	{ 0, 2, 2, 2, 2, 2, 2, 2, 2, 0},
	{ 0, 0, 2, 4, 2, 2, 4, 2, 0, 0},
	{ 0, 0, 0, 2, 2, 2, 2, 0, 0, 0},
	{ 0, 0, 0, 0, 2, 2, 0, 0, 0, 0},
};

int partSprite[10][10] = {
	{ 0, 0, 2, 3, 2, 2, 2, 2, 0, 0},
	{ 0, 0, 2, 2, 3, 2, 2, 2, 0, 0},
	{ 0, 0, 2, 2, 2, 3, 2, 2, 0, 0},
	{ 0, 0, 2, 2, 2, 2, 3, 2, 0, 0},
	{ 0, 0, 3, 2, 2, 2, 2, 3, 0, 0},
	{ 0, 0, 2, 3, 2, 2, 2, 2, 0, 0},
	{ 0, 0, 2, 2, 3, 2, 2, 2, 0, 0},
	{ 0, 0, 2, 2, 2, 3, 2, 2, 0, 0},
	{ 0, 0, 2, 2, 2, 2, 3, 2, 0, 0},
	{ 0, 0, 3, 2, 2, 2, 2, 3, 0, 0},
};

int taleSprite[10][10] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 2, 2, 0, 0, 0, 0},
	{ 0, 0, 0, 2, 1, 2, 2, 0, 0, 0},		
	{ 0, 0, 0, 2, 2, 3, 2, 0, 0, 0},
	{ 0, 0, 2, 3, 2, 2, 3, 2, 0, 0},
	{ 0, 0, 2, 2, 3, 2, 2, 2, 0, 0},
	{ 0, 0, 2, 2, 2, 3, 2, 2, 0, 0},
	{ 0, 0, 2, 2, 2, 2, 3, 2, 0, 0},
	{ 0, 0, 3, 2, 2, 2, 2, 3, 0, 0},
};

int turnSprite[10][10] = {
	{ 0, 0, 2, 3, 2, 2, 2, 2, 0, 0},
	{ 0, 0, 2, 2, 3, 2, 2, 2, 0, 0},
	{ 3, 2, 2, 2, 2, 3, 2, 2, 0, 0},
	{ 2, 2, 2, 2, 3, 2, 3, 2, 0, 0},
	{ 2, 2, 2, 3, 2, 2, 3, 3, 0, 0},
	{ 2, 2, 3, 2, 2, 3, 2, 2, 0, 0},
	{ 2, 3, 2, 2, 3, 2, 2, 0, 0, 0},
	{ 3, 2, 2, 2, 2, 2, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

void drawSprite(u8* fb, int pos, int direction, int sprite[10][10]){
	int x = 0;
	int y = 0;
	int j = 10;
	
	if (direction == 2){			//up  turn: mirror vertical fix?
		while ( y < 10){
			j = 10;
			x = 0;
			for (; x < 10; x++){
				if (sprite[y][x] == 1){
					drawPixel( fb, pos, y, j, white);
				} 
				if (sprite[y][x] == 2){
					drawPixel( fb, pos, y, j, snakeGreen);
				} 
				if (sprite[y][x] == 3){
					drawPixel( fb, pos, y, j, snakeStripes);
				} 
				if (sprite[y][x] == 4){
					drawPixel( fb, pos, y, j, black);
				}
				j--;
				//if (headSprite[y][x] == 0) drawPixel( fb, pos, y, x, white); 
				
			}
		y++;
		}
	}
	
	if (direction == 1){			//up	turn 90* left
		for (; y < 10; y++){
			x = 0;
			for (; x < 10; x++){
				if (sprite[x][y] == 1){
					drawPixel( fb, pos, y, x, white);
				} 
				if (sprite[x][y] == 2){
					drawPixel( fb, pos, y, x, snakeGreen);
				} 
				if (sprite[x][y] == 3){
					drawPixel( fb, pos, y, x, black);
				} 
				//if (headSprite[y][x] == 0) drawPixel( fb, pos, y, x, white); 
				
			}
		}
	}
	
	if (direction == 4){	//	turn: mirror horizontal
		int i = 9;
		int j =10;
		for (; y < 10; y++){
			
			x = 0;
			j = 0;
			for (; x < 10; x++){
				if (sprite[y][x] == 1){
					drawPixel( fb, pos, i, j, white);
				} 
				if (sprite[y][x] == 2){
					drawPixel( fb, pos, i, j, snakeGreen);
				} 
				if (sprite[y][x] == 3){
					drawPixel( fb, pos, i, j, black);
				}
				j++;
			}
		i--;
		}
	}
	
	if (direction == 3){ //turn 90* left
		int i = 10;
		int j =10;
		for (; y < 10; y++){
			i--;
			x = 0;
			for (; x < 10; x++){
				if (sprite[x][y] == 1){
					drawPixel( fb, pos, i, j, white);
				} 
				if (sprite[x][y] == 2){
					drawPixel( fb, pos, i, j, snakeGreen);
				} 
				if (sprite[x][y] == 3){
					drawPixel( fb, pos, i, j, black);
				}
			j--;
			}
		j = 10;
		}
	}
}

void drawSpriteC(u8* fb, int pos, int direction, int type){
	if (type == 1 && direction){
		drawSprite(fb, pos, direction, headSprite);
	}
	if (type == 4){
		if (direction > 4) direction = direction - 4;
		drawSprite(fb, pos, direction, turnSprite);
	} 
	if (type == 2 && direction <= 4){
		drawSprite(fb, pos, direction, partSprite);
	}
	if (type == 3){
		drawSprite(fb, pos, direction, taleSprite);
	}

}

void drawPixel( u8* fb, int pos, int i, int j, colors color){
	fb[(pos*3+i*3+j*240*3)+0] = color.blue;
	fb[(pos*3+i*3+j*240*3)+1] = color.green;
	fb[(pos*3+i*3+j*240*3)+2] = color.red;
}

void pixel(u8* fb, int pos, int size, colors color){
	int i = 0;
	for (;i < size; i++){
		int j = 0;
		for (;j < size; j++){
			fb[(pos*3+i*3+j*240*3)+0] = color.blue;
			fb[(pos*3+i*3+j*240*3)+1] = color.green;
			fb[(pos*3+i*3+j*240*3)+2] = color.red;
		}
	}
}

part* newPart(int posX, int posY, int d, int t){
	part *p = malloc(sizeof(part));
	p ->x = posX;
	p ->y = posY;
	p ->direction = d;
	p ->turn = t;
	p ->next = NULL;
	return p;
}

part* newPartTail(int posX, int posY, int d, part *oldTail){
	part *p = malloc(sizeof(part));
	p ->x = posX;
	p ->y = posY;
	p ->direction = d;
	p ->turn = d;
	p ->next = oldTail;
//	oldTail ->next = p;
	return p;
}
