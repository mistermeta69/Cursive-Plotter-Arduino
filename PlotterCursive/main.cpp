// plot cursive letters
//
#define ARDUI 0

#ifndef ARDUI
#include <graphics.h>
#include <conio.h>
#include <dos.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

// may need to adjust for Arduino
#define MSPTDELAY 10
#define SCALE 4
#define XMAX (300 / SCALE * 2)
#define YMAX (255 * SCALE / 2)
#define CHEIGHT (16 * SCALE / 2)

char sentence[] = "the quick brown  fox jumped over the lazy dog ";
int letScale; // for capitalization

// prototypes
unsigned cursive(int x, int y, unsigned c, int l);
unsigned getcoords(unsigned char c);
int initgraphics(void);

#ifdef ARDUI
void setup()
{
	// put your setup code here, to run once:
	initgraphics();
}
#endif

#ifdef ARDUI
void loop()
{
#else
void main()
{
	initgraphics();
#endif

	// draw the letters at a given x y offset
	int x = 0;
	int y = 0;

	char *curchar;
	curchar = sentence;
	unsigned cwidth;
	int l;
	for (l = 0; l < YMAX / CHEIGHT; l++)
	{
		for (x = 0; x < XMAX; x += cwidth)
		{
			if (*curchar == '\x00')
				goto done;
			if (isupper(*curchar))
				letScale = 2;
			else
				letScale = 1;

			cwidth = cursive(x, y, getcoords(*curchar++), l);
		}
	}

done:
#ifndef ARDUI
	getch();
	closegraph();
	return;
#else
loop:
	goto loop;
#endif
}

unsigned xC(char b)
{
	return (unsigned)((0x0F & (b & 0xF0) >> 4));
}

unsigned yC(char b)
{
	return (unsigned)((0x0F & (b & 0x0F)));
}

typedef struct
{
	char *xyPair;
	short numPairs;
} Letter;

Letter alphabet[] =
	{
		{// blank
		 "\x06\x86",
		 2},

		{// a
		 "\x06\x18\x4a\x7a\x88\x44\x25\x18\x25\x44\x88\x95\xa6",
		 13},

		{// b
		 "\x06\x5f\x15\x34\x53\x76\x68\x49\x28\x15\x34\x53\x96",
		 13},

		{// c
		 "\x06\x4a\x69\x77\x69\x4a\x17\x24\x54\x95\xa6",
		 11},

		{// d
		 "\x06\x27\x49\x7b\x8a\x7b\x49\x27\x34\x65\x77\x8a\x9c\xaf\x9c\x8a\x87\x85\x94\xb6",
		 20},

		{// e
		 "\x06\x37\x58\x79\x8a\x7b\x5a\x39\x37\x45\x64\x85\xa6",
		 13},

		{// f
		 "\x06\x29\x4b\x6e\x5f\x4e\x3c\x27\x13\x10\x31\x43\x26\x45\x66",
		 15},

		{// g
		 "\x06\x17\x29\x4b\x6a\x79\x6a\x4b\x29\x17\x26\x57\x79\x66\x54\x42\x20\x10\x11\x23\x55\x86",
		 22},

		{// h
		 "\x06\x27\x49\x6b\x8d\x9e\x9f\x8f\x6d\x5b\x49\x36\x24\x46\x68\x89\x98\x86\x84\xa5\xb6",
		 21},

		{// i
		 "\x06\x17\x28\x3a\x27\x26\x34\x44\x55\x76",
		 10},

		{// j
		 "\x06\x27\x38\x4a\x5c\x59\x46\x32\x10\x00\x01\x23\x55\x76",
		 14},

		{// k
		 "\x06\x28\x4a\x5c\x6e\x6f\x5e\x4c\x39\x26\x14\x26\x39\x6a\x7a\x68\x25\x55\x64\x85\x96",
		 21},

		{// l
		 "\x06\x27\x49\x6c\x7e\x6f\x5e\x4c\x39\x36\x44\x65\x76",
		 13},

		{// m
		 "\x06\x28\x4a\x5b\x48\x34\x48\x6a\x8b\x9a\x87\x74\x87\xaa\xcb\xda\xc8\xb4\xd5\xe6",
		 20},

		{// n
		 "\x06\x28\x4a\x5b\x48\x34\x48\x6a\x8b\x9a\x87\x84\xb6",
		 13},

		{// o
		 "\x06\x28\x4a\x6b\x4a\x28\x26\x34\x64\x85\x97\x99\x8b\x6b\x69\x77\xa6",
		 17},

		{// p
		 "\x06\x27\x49\x6d\x49\x45\x32\x20\x33\x59\x7a\x8a\xa9\x97\x85\x64\x45\x64\x85\xb6",
		 20},

		{// q
		 "\x06\x27\x38\x5a\x8a\x5a\x38\x27\x25\x34\x55\x77\x8a\x77\x40\x62\x74\x65\x85\x96",
		 20},

		{// r
		 "\x06\x28\x3a\x49\x59\x7a\x68\x56\x74\x96",
		 10},

		{// s
		 "\x06\x28\x4a\x49\x58\x66\x54\x44\x25\x44\x54\x86",
		 12},

		{// t
		 "\x06\x28\x4b\x5f\x4b\x1b\x7b\x4b\x26\x34\x65\x86",
		 12},

		{// u
		 "\x06\x28\x4b\x26\x24\x44\x55\x78\x8a\x78\x65\x74\x96",
		 13},

		{// v
		 "\x06\x3a\x54\x8a\xa6",
		 5},

		{// w
		 "\x06\x3a\x44\x68\x74\xaa\xc6",
		 7},

		{// x
		 "\x06\x3a\x66\x22\x99\x66\x84\xb6",
		 8},

		{// y
		 "\x06\x17\x2a\x26\x34\x44\x55\x67\x7a\x67\x55\x30\x10\x11\x22\x54\x86",
		 17},

		{// z
		 "\x06\x27\x38\x4a\x59\x46\x34\x46\x56\x76\x75\x62\x40\x20\x11\x22\x33\x54\x75\xa6",
		 20},

		{"\x00",
		 0}};

#define CWHITE 15

unsigned getcoords(unsigned char c)
{
	int l;
	l = (tolower(c) - 'a') + 1;
	if (l < 0 || l > 26)
		l = 0;
	return (unsigned)l;
}

void toPlotter(int x, int y, int line)
{
	static int prevx = 0;
	static int prevy = 0;
	int msdelay;

	x = SCALE * x;
	y = SCALE * (CHEIGHT / 5 + line * CHEIGHT + (CHEIGHT / 5 * (letScale / 2) + CHEIGHT / 2 - letScale * y));

#ifndef ARDUI
	lineto(x, y);
#else
	int xpin, ypin;
	xpin = 9;
	ypin = 10;
	analogWrite(xpin, x);
	analogWrite(ypin, y);
#endif
	// proportional to distance
	msdelay = MSPTDELAY * sqrt((x - prevx) * (x - prevx) + (y - prevy) * (y - prevy));
	delay(msdelay);
	prevx = x;
	prevy = y;
}

int maxi(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

// returns x offset
unsigned cursive(int x, int y, unsigned coords, int line)
{
	int i;
	unsigned l, xpos = 0;

	l = alphabet[coords].numPairs;

	for (i = 0; i < l; i++)
	{
		char p = alphabet[coords].xyPair[i];
		xpos = maxi(xpos, xC(p));
		toPlotter(x + xC(p), y + yC(p), line);
	}

	return xpos; // max x pos for kerning
}

int initgraphics(void)
{
#ifndef ARDUI
	/* request auto detection */
	int gdriver = DETECT, gmode, errorcode;
	// int maxx, maxy;

	/* initialize graphics and local variables */
	initgraph(&gdriver, &gmode, "c:\\turboc3\\bgi");

	/* read result of initialization */
	errorcode = graphresult();
	if (errorcode != grOk) /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1); /* terminate with an error code */
	}

	// maxx = getmaxx();
	// maxy = getmaxy();

	/* output line with non-default settings */
	/*
	  setlinestyle(DOTTED_LINE, 0, 3); line(0, 0, maxx, maxy);
	  outtextxy(maxx/2, maxy/3, "Before default values are restored.");
	  getch();
	*/
	/* restore default values for everything */
	graphdefaults();

	/* clear the screen */
	cleardevice();
	putpixel(0, 0, 0);
	lineto(0, 0);

	/* output line with default settings */
	/*
	  line(0, 0, maxx, maxy);
	  outtextxy(maxx/2, maxy/3, "After restoring default values.");
	*/
	/* clean up */
	// getch();
	// closegraph();
#endif
	return 0;
}
