#include <3ds.h>
#include "parts.h"
#include <stdlib.h>

colors white = { 0xFF, 0xFF, 0xFF};
colors black = {  0x0,  0x0,  0x0};
colors blue  = { 0xFF,  0x0,  0x0};
colors red   = {  0x0,  0x0, 0xFF};

colors snakeGreen = { 13, 215, 13};
colors snakeStripes = { 00, 36, 05};
colors appleRed		= { 0x10, 0x10, 0xf4};
colors appleRed2	= { 0x52, 0x2c, 0xf8};
colors appleBrown	= { 0x02, 0x02, 0x79};

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
	{ 0, 0, 2, 2, 2, 2, 2, 2, 0, 0},
	{ 0, 0, 2, 3, 2, 2, 2, 2, 0, 0},
	{ 0, 0, 2, 2, 3, 2, 2, 2, 0, 0},
	{ 0, 0, 2, 2, 2, 3, 2, 2, 0, 0},
	{ 0, 0, 2, 2, 2, 2, 3, 2, 0, 0},
	{ 0, 0, 2, 2, 2, 2, 2, 2, 0, 0},
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
	{ 0, 0, 2, 2, 2, 2, 2, 2, 0, 0},
};

int turnSprite[10][10] = {
	{ 0, 0, 2, 3, 2, 2, 2, 2, 0, 0},
	{ 0, 0, 2, 2, 3, 2, 2, 2, 0, 0},
	{ 2, 2, 2, 2, 2, 3, 2, 2, 0, 0},
	{ 2, 2, 2, 2, 3, 2, 3, 2, 0, 0},
	{ 2, 2, 2, 3, 2, 2, 3, 2, 0, 0},
	{ 2, 2, 3, 2, 2, 3, 2, 2, 0, 0},
	{ 2, 3, 2, 2, 3, 2, 2, 0, 0, 0},
	{ 3, 2, 2, 2, 2, 2, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int appleSprite[10][10] = {
	{ 0 ,0, 2, 2, 0, 7, 7, 0, 0, 0},
	{ 0, 0, 0, 0, 2, 7, 0, 0, 0, 0},
	{ 0, 5, 5, 5, 7, 0, 5, 5, 5, 0},
	{ 0, 5, 5, 5, 7, 5, 5, 5, 5, 5},
	{ 5, 5, 5, 5, 5, 5, 6, 6, 5, 5},
	{ 5, 5, 5, 5, 5, 5, 6, 6, 5, 5},
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
	{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 0},
	{ 0, 5, 5, 5, 5, 5, 5, 5, 5, 0},
	{ 0, 0, 5, 5, 0, 0, 5, 5, 0, 0},
};

void drawPixel_int2col(u8* fb, int pos, int posY, int posX,  int col){
	switch (col)
	{
		case 1:
			drawPixel( fb, pos, posY, posX, white);
			break;
		case 2:
			drawPixel( fb, pos, posY, posX, snakeGreen);
			break;
		case 3:
			drawPixel( fb, pos, posY, posX, snakeStripes);
			break;
		case 4:
			drawPixel( fb, pos, posY, posX, black);
			break;
			
		case 5:
			drawPixel( fb, pos, posY, posX, appleRed);
			break;
		case 6:
			drawPixel( fb, pos, posY, posX, appleRed2);
			break;
		case 7:
			drawPixel( fb, pos, posY, posX, appleBrown);
			break;
		default:
			break;			
	}
}

void drawSprite(u8* fb, int pos, int direction, int sprite[10][10]){
	int spriteX;
	int spriteY;
	int dispHei;
	int dispWid;
	
	switch (direction) {
		
		case 1:		// Right
			for (spriteY=0 ; spriteY < 10; spriteY++){
				for (spriteX=0; spriteX < 10; spriteX++){
					drawPixel_int2col( fb, pos, spriteY, spriteX, sprite[spriteX][spriteY]);				
				}
			}
			break;
			
		case 2:		// Up
			for (spriteY=0; spriteY < 10; spriteY++){
				dispWid = 9;
				for (spriteX=0; spriteX < 10; spriteX++){
					drawPixel_int2col( fb, pos, spriteY, dispWid, sprite[spriteY][spriteX]);
					dispWid--;				
				}
			}
			break;
			
		case 3:		// Left
			dispHei = 10;
			for (spriteY=0; spriteY < 10; spriteY++){
				dispWid = 10;
				dispHei--;
				for (spriteX=0; spriteX < 10; spriteX++){
					drawPixel_int2col( fb, pos, dispHei, dispWid-1, sprite[spriteX][spriteY]);
					dispWid--;
				}
			}
			break;
			
		case 4:		// Down
			dispHei = 9;
			for (spriteY=0; spriteY < 10; spriteY++){
				dispWid = 0;
				for (spriteX=0; spriteX < 10; spriteX++){
					drawPixel_int2col( fb, pos, dispHei, dispWid, sprite[spriteY][spriteX]);
					dispWid++;
				}
				dispHei--;
			}
			break;
		
		default:
			break;
	}
}


void drawSpriteC(u8* fb, int pos, int direction, int type){
	if (type == 1 && direction){
		drawSprite(fb, pos, direction, headSprite);
	}
	if (type == 2 && direction <= 4){
		drawSprite(fb, pos, direction, partSprite);
	}
	if (type == 3){
		drawSprite(fb, pos, direction, taleSprite);
	}
	if (type == 4){
		if (direction > 4) direction = direction - 4;
		drawSprite(fb, pos, direction, turnSprite);
	} 
	if (type == 5){
		drawSprite(fb, pos, 1, appleSprite);
		
	}
}


void drawPixel( u8* fb, int pos, int heightOffset, int widthOffset, colors color){	
	fb[(pos*3+heightOffset*3+widthOffset*DISPHEIGHT*3)+0] = color.blue;
	fb[(pos*3+heightOffset*3+widthOffset*DISPHEIGHT*3)+1] = color.green;
	fb[(pos*3+heightOffset*3+widthOffset*DISPHEIGHT*3)+2] = color.red;
}


void pixel(u8* fb, int pos, int size, colors color){
	int i = 0;
	for (;i < size; i++){
		int j = 0;
		for (;j < size; j++){
			fb[(pos*3+i*3+j*DISPHEIGHT*3)+0] = color.blue;
			fb[(pos*3+i*3+j*DISPHEIGHT*3)+1] = color.green;
			fb[(pos*3+i*3+j*DISPHEIGHT*3)+2] = color.red;
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


void debugGrid(u8* fb){
  int i = 0;
  int j;
  for (;i<DISPHEIGHT; i=i+10){
	  for (j=0; j<400; j=j+10){
		if (((i/10)%2+(j/10)%2)%2 == 1)
			emtySquare(fb, i+j*DISPHEIGHT, 0);
		else
			emtySquare(fb, i+j*DISPHEIGHT, 0xff);
	  }
  }
}

void emtySquare(u8* fb, int pos, int type){
	int i;
	for (i=0; i<10; i++){ //	|
		fb[pos*3+i*3] 	= type;
		fb[pos*3+i*3+1]	= type;
		fb[pos*3+i*3+2]	= type;
	}
	for (i=0; i<10; i++){//		|_
		fb[pos*3+DISPWIDTH*i*3] 	= type;
		fb[pos*3+DISPWIDTH*i*3+1]	= type;
		fb[pos*3+DISPWIDTH*i*3+2]	= type;
	}
	for (i=0; i<10; i++){//		|_|
		fb[DISPWIDTH*9*3+pos*3+i*3] 	= type;
		fb[DISPWIDTH*9*3+pos*3+i*3+1]	= type;
		fb[DISPWIDTH*9*3+pos*3+i*3+2]	= type;
	}
	for (i=0; i<10; i++){
		fb[27+pos*3+DISPWIDTH*i*3] 	= type;
		fb[27+pos*3+DISPWIDTH*i*3+1]	= type;
		fb[27+pos*3+DISPWIDTH*i*3+2]	= type;
	}	
}



