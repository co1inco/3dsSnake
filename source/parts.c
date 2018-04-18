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

void drawSprite(u8* fb, int pos, int direction, int sprite[10][10]){
	int spriteX;
	int spriteY;
	int dispHei;
	int dispWid;
	
	switch (direction) {
		
		case 1:		// Right
			for (spriteY=0 ; spriteY < 10; spriteY++){
				for (spriteX=0; spriteX < 10; spriteX++){
					if (sprite[spriteX][spriteY] == 1){
						drawPixel( fb, pos, spriteY, spriteX, white);
					} 
					if (sprite[spriteX][spriteY] == 2){
						drawPixel( fb, pos, spriteY, spriteX, snakeGreen);
					} 
					if (sprite[spriteX][spriteY] == 3){
						drawPixel( fb, pos, spriteY, spriteX, snakeStripes);
					} 
					if (sprite[spriteX][spriteY] == 4){
						drawPixel( fb, pos, spriteY, spriteX, black);
					}				
				}
			}
			break;
			
		case 2:		// Up
			for (spriteY=0; spriteY < 10; spriteY++){
				dispWid = 9;
				for (spriteX=0; spriteX < 10; spriteX++){
					if (sprite[spriteY][spriteX] == 1){
						drawPixel( fb, pos, spriteY, dispWid, white);
					} 
					if (sprite[spriteY][spriteX] == 2){
						drawPixel( fb, pos, spriteY, dispWid, snakeGreen);
					} 
					if (sprite[spriteY][spriteX] == 3){
						drawPixel( fb, pos, spriteY, dispWid, snakeStripes);
					} 
					if (sprite[spriteY][spriteX] == 4){
						drawPixel( fb, pos, spriteY, dispWid, black);
					}
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
					if (sprite[spriteX][spriteY] == 1){
						drawPixel( fb, pos, dispHei, dispWid-1, white);
					} 
					if (sprite[spriteX][spriteY] == 2){
						drawPixel( fb, pos, dispHei, dispWid-1, snakeGreen);
					} 
					if (sprite[spriteX][spriteY] == 3){
						drawPixel( fb, pos, dispHei, dispWid-1, snakeStripes);
					} 
					if (sprite[spriteX][spriteY] == 4){
						drawPixel( fb, pos, dispHei, dispWid-1, black);
					}
					dispWid--;
				}
			}
			break;
			
		case 4:		// Down
			dispHei = 9;
			for (spriteY=0; spriteY < 10; spriteY++){
				dispWid = 0;
				for (spriteX=0; spriteX < 10; spriteX++){
					if (sprite[spriteY][spriteX] == 1){
						drawPixel( fb, pos, dispHei, dispWid, white);
					} 
					if (sprite[spriteY][spriteX] == 2){
						drawPixel( fb, pos, dispHei, dispWid, snakeGreen);
					} 
					if (sprite[spriteY][spriteX] == 3){
						drawPixel( fb, pos, dispHei, dispWid, snakeStripes);
					} 
					if (sprite[spriteY][spriteX] == 4){
						drawPixel( fb, pos, dispHei, dispWid, black);
					}
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

void drawPixel( u8* fb, int pos, int heightOffset, int widthOffset, colors color){
	fb[(pos*3+heightOffset*3+widthOffset*240*3)+0] = color.blue;
	fb[(pos*3+heightOffset*3+widthOffset*240*3)+1] = color.green;
	fb[(pos*3+heightOffset*3+widthOffset*240*3)+2] = color.red;
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


void debugGrid(u8* fb){
  int i = 0;
  int j;
  for (;i<240; i=i+10){
	  for (j=0; j<400; j=j+10){
		if (((i/10)%2+(j/10)%2)%2 == 1)
			emtySquare(fb, i+j*240, 0);
		else
			emtySquare(fb, i+j*240, 0xff);
	  }
  }
}

void emtySquare(u8* fb, int pos, int type){
	
	int i;
	for (i=0; i<10; i++){ //	|
		fb[pos*3+i*3] 	= 0xff;
		fb[pos*3+i*3+1]	= type;
		fb[pos*3+i*3+2]	= type;
	}
	for (i=0; i<10; i++){//		|_
		fb[pos*3+240*i*3] 	= 0xff;
		fb[pos*3+240*i*3+1]	= type;
		fb[pos*3+240*i*3+2]	= type;
	}
	for (i=0; i<10; i++){//		|_|
		fb[240*9*3+pos*3+i*3] 	= 0xff;
		fb[240*9*3+pos*3+i*3+1]	= type;
		fb[240*9*3+pos*3+i*3+2]	= type;
	}
	for (i=0; i<10; i++){
		fb[27+pos*3+240*i*3] 	= 0xff;
		fb[27+pos*3+240*i*3+1]	= type;
		fb[27+pos*3+240*i*3+2]	= type;
	}	
}



