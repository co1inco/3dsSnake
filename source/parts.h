#define DISPWIDTH (400)
#define DISPHEIGHT (240)

typedef struct {
	int blue;
	int green;
	int red;
} colors;

typedef struct sakeparts{
	int x;
	int y;
	int direction;
	int turn;
	struct snakeparts *next;
} part;



void drawSpriteC(u8* fb, int pos, int direction, int type);
void pixel(u8* fb, int pos, int size, colors color);
void drawPixel( u8* fb, int pos, int i, int j, colors color);

part* newPart(int psX, int posY, int d, int t);
part* newPartTail(int posX, int posY, int d, part *oldTail);

void newPartTest(int posX, int posY, int d, int t, part *lastPart);

void debugGrid(u8* fb);