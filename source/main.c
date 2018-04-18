#include <stdio.h>
#include <3ds.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "parts.h"

int game(){
  u32 kDown;        // keys down

  consoleInit(GFX_BOTTOM, NULL);
  u8* fb = gfxGetFramebuffer(GFX_TOP, GFX_RIGHT, NULL, NULL); 
  int y_resolution = 400;
  memset(fb, 0, y_resolution*240*3);
  
  int direction = 1;
  int pos_x		= 240/2;
  int pos_y		= y_resolution/2;
  int score 	= 0;
  int speed     = 15; //smaller = faster
  bool hitEnd = false;
  int acceleration = 0;
  int accelerationNext = 5;
  int size = 10;
  int wait = 0;
  
  bool debugMode = false;
  
  int oldDirection = 0;
  int partDirection = 0;
  int turn = 0;
  int partTurn = 0;

  int restart = 0;
  bool pause = true;
  
  int appleY = (rand() % y_resolution/size) * size;
  int appleX = (rand() % 240/size) * size;
  
/*  
colors white = { 0xFF, 0xFF, 0xFF};
colors black = {  0x0,  0x0,  0x0};
colors blue  = { 0xFF,  0x0,  0x0};*/
colors red   = {  0x0,  0x0, 0xFF};/*
colors snakeGreen = { 13, 215, 13};
colors snakeStripes = { 00, 36, 05};*/
  
  part *start = NULL;
  part *i = NULL;
  part *last = NULL;
  part *q = NULL;
  part *r = NULL;
  part *next = NULL;
  
 last = newPart(pos_x,pos_y, direction, direction);
 if (start == NULL) start = last;
 if (i != NULL) i ->next = last;
 i = last;
 last = newPart(pos_x,pos_y, direction, direction);
 if (start == NULL) start = last;
 if (i != NULL) i ->next = last;
 i = last;
  
  printf("Hello World\n");

  // Main loop
  while (aptMainLoop())
  {

    hidScanInput();
    kDown = hidKeysDown();

	if (kDown & KEY_START) pause = !pause;
  
	if (hitEnd) pause = true;
	
	if (!pause){
		
		memset(fb, 5, y_resolution*240*3);
		
		if ((kDown & KEY_RIGHT) && oldDirection != 3) direction = 1;
		if ((kDown & KEY_UP	  ) && oldDirection != 4) direction = 2;
		if ((kDown & KEY_LEFT ) && oldDirection != 1) direction = 3;
		if ((kDown & KEY_DOWN ) && oldDirection != 2) direction = 4;
		
		//Speed control
		if (acceleration == accelerationNext){
			if (speed > 5) speed = speed - 2;
			acceleration = 0;
			accelerationNext = accelerationNext + 2;
		}
		
		if (debugMode == true) {
			if (kDown & KEY_A){					//add new element
				last = newPart(pos_x,pos_y, direction, direction);
				if (start == NULL) start = last;
				if (i != NULL) i ->next = last;
				i = last;
				score++;
				acceleration++;
			} 
			if (kDown & KEY_B) speed--; //speed up
		}
		
		
		if (wait > speed && !hitEnd){
			//move forward and border detection
			switch(direction){
				case (1):
					pos_y = pos_y + size;			  // move "size" forward
					if (pos_y > y_resolution - size){ // check if head hit the border
						pos_y = y_resolution - size;
						hitEnd = true;
					}
					break;
				case (2):
					pos_x = pos_x + size;
					if (pos_x > 240-size){
						pos_x = 240-size;
						hitEnd = true;
					}
					break;
				case (3):
					pos_y = pos_y - size;
					if (pos_y < 0){
						pos_y = 0;
						hitEnd = true;
					}
					break;
				case(4):
					pos_x = pos_x - size;
					if (pos_x < 0){
						pos_x = 0;
						hitEnd = true;
					}
					break;
				default:
					break;
			}

		//testfor hit self
			r = start;
			if (score > 1){
				for (; r != NULL; r = next){
					if (pos_x == r ->x && pos_y == r ->y) hitEnd = true;
					next = r ->next;
				}	 
			}
		
			//testfor apple
			if (pos_x == appleX && pos_y == appleY) {
				start = newPartTail(start ->x,start ->y, start ->direction, start);
//				if (start == NULL) start = last;
//				if (i != NULL) i ->next = last;
//				i = last;
				score++;
				acceleration++;
			
				srand(time(NULL));
				appleY = (rand() % y_resolution/size) * size;
				appleX = (rand() % 240/size) * size;
			}
			
			turn = direction;
			if (direction != oldDirection){
				if (direction == 1){
					if (oldDirection == 2) turn = 6;
					if (oldDirection == 4) turn = 7;
				} else if (direction == 2){
					if (oldDirection == 1) turn = 8;
					if (oldDirection == 3) turn = 7;
				} else if (direction == 3){
					if (oldDirection == 2) turn = 5;
					if (oldDirection == 4) turn = 8;
				} else if (direction == 4){
					if (oldDirection == 1) turn = 5;
					if (oldDirection == 3) turn = 6;
				}
				last ->turn = turn;
				last ->direction = direction;
			//	q = last;
			//	last = q ->next;
			//	q ->t = partDirection;
			}
			last = newPart(pos_x, pos_y, direction, direction); // last => first/head
			if (start == NULL) start = last;
			if (i != NULL) i ->next = last;
			i = last;
			
//			q = last;
//			last = q ->next;
//			q ->t = partDirection;
		
			q = start;							//remove tail
			start = q ->next;
			free(q);
			
			wait = 0;		
			oldDirection = direction;

		}
		
		//Draw Snake
		r = start;
		drawSpriteC(fb, r ->x+r->y*240 , r ->direction, 3);
		r = r ->next;
		for (; r != NULL; r = next){
			partDirection = r ->direction;
			partTurn = r ->turn;
//			if (r ->t > 4) partDirection = r ->t;
			next = r ->next;
			if (next != NULL) {
				if (partDirection != partTurn) drawSpriteC(fb, r ->x+r->y*240 , partTurn, 4);
				else drawSpriteC(fb, r ->x+r->y*240 , partDirection, 2);
			}
			if (next == NULL) drawSpriteC(fb, r ->x + r->y*240 , direction, 1);
		}
		
		pixel(fb, appleX + appleY * 240, size, red);
	
		wait++;
		
		consoleClear;
		printf("\e[1;1H\e[2J");
		
		printf("\x1b[1;0H SCORE: %i", score);
		
		if (debugMode == true) {
			printf("\x1b[2;0H X:    	%i  ", pos_x);
			printf("\x1b[3;0H Y:    	%i  ", pos_y);
			printf("\x1b[4;0H End:  	%i  ", hitEnd);
			printf("\x1b[5;0H Score:	%i  ", score);
			printf("\x1b[6;0H Speed:	%i  ", speed);
			printf("\x1b[7;0H SpeedNext:%i	", accelerationNext);
			printf("\x1b[8;0H ApplX:	%i  ", appleX);
			printf("\x1b[9;0H ApplY:	%i  ", appleY);
			printf("\x1b[10;0H Debug:	%i	", debugMode);
		}
//		printf("\x1b[11;%iH         ", (y_resolution/8)/2-3*8);
//		printf("\x1b[12;%iH                            ", (y_resolution/8)/6);
//		printf("\x1b[13;%iH                            ", (y_resolution/8)/6);
	}
	
	else {
		printf("\x1b[12;%iH [PAUSE] ", (y_resolution/8)/6+3); //22
		if (!hitEnd)
			printf("\x1b[14;%iH Press [START]  to continue", (y_resolution/8)/8);
		printf("\x1b[15;%iH Press [SELECT] to exit", (y_resolution/8)/8);
		if (hitEnd)
			printf("\x1b[16;%iH Press [START] or (A) to restart", (y_resolution/8)/8);
		else
			printf("\x1b[16;%iH Press (A) to restart", (y_resolution/8)/8);
		
		if (kDown & KEY_SELECT){
			restart = 0;
			break;
		}
		
		if (kDown & KEY_A){
			restart = 1;
			break;
		}
		
		if (kDown & KEY_X){
			debugMode = !debugMode;
		}
		
		if ((kDown & KEY_START) && hitEnd) {
			restart = 1;
			break;
		}
	}
		
	
		// Flush and swap framebuffers
    gfxFlushBuffers();
    gfxSwapBuffers();
    gspWaitForVBlank();
  }
  
  //Cleanup list
  q = start;
  next = NULL;
  for (; q != NULL; q = next){
	  next = q ->next;
	  free(q);
  }
  return restart;
}

int main()
{
  // Initializations
  srvInit();        // services
  aptInit();        // applets
  hidInit();    // input
  gfxInitDefault(); // graphics
//  gfxSet3D(false);  // stereoscopy (true: enabled / false: disabled)
  gfxSetDoubleBuffering(GFX_TOP, false); //turn of double framebuffer
  
  int play = 1;
	
	while (play){
		play = game();
	}
	

  // Exit
  gfxExit();
  hidExit();
  aptExit();
  srvExit();

  // Return to hbmenu
  return 0;
}





