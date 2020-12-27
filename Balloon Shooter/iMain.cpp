#include "iGraphics.h"





int i,b=0,ballon[10]={0,0,0,0,0,0,0,0,0,0};
int ballon_x[10],ballon_y[10];
int tir_x=200,tir_y=2;
int bullet=0,bullet_x,bullet_y;
int score=0;
char ch[10];
bool page1 = true;
bool page2 = false;
bool page3 = false;



/* 
function iDraw() is called again and again by the system.
*/
void iDraw()
{
	//place your drawing codes here	
	iClear();
	if(page1){
		iShowBMP(0,0,"menu.bmp");
	}
	if(page2){
		iShowBMP(0,0,"bg2.bmp");
		for(i=0;i<10;i++)
			iShowBMP2(ballon_x[i],ballon_y[i],"ballon2.bmp",0);
		iShowBMP2(tir_x,tir_y,"tir2.bmp",255);
		iSetColor(0,0,0);
		itoa(score,ch,10);
		iText(390,551,"Score",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(450,550,ch,GLUT_BITMAP_TIMES_ROMAN_24);
		iFilledEllipse(bullet_x,bullet_y,2,20);
	}
}

/* 
function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/* 
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(bullet==0&&page2)
		{
			bullet=1;
			bullet_x=tir_x+50;
		}
		if(mx>=263&&mx<=341&&my>=(600-213)&&my<=(600-192)&&!page2){
			page1=false;
			page2=true;
		}
		if(mx>=274&&mx<=331&&my>=(600-260)&&my<=(600-237)&&!page2){
			exit(0);
		}
	}
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed. 
*/
void iKeyboard(unsigned char key)
{
	if(key == ' ')
	{
		if(bullet==0)
		{
			bullet=1;
			bullet_x=tir_x+50;
		}
	}
	//place your codes for other keys here
}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use 
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, 
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, 
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT 
*/

void iSpecialKeyboard(unsigned char key)
{
	if(key == GLUT_KEY_LEFT)
	{
		tir_x-=10;
	}
	if(key == GLUT_KEY_RIGHT)
	{
		tir_x+=10;
	}
}

void create_ballon()
{
	if(page2){
		if(ballon[b]==0)
		{
			ballon_x[b]=rand()%500;
			ballon_y[b]=600;
			ballon[b]=1;
			b++;
		}
		if(b==10)
			b=0;
	}
}

void ballon_move()
{
	if(page2)
		for(i=0;i<10;i++)
			if(ballon[i]==1)
				ballon_y[i]-=2;
}

void ballon_die()
{
	if(page2)
		for(i=0;i<10;i++)
			if(ballon_y[i]<=50)
				ballon[i]=0;
}

void position()
{
	if(page2){
		for(i=0;i<10;i++)
			if(ballon[i]==0)
				ballon_y[i]=-100;
		if(tir_x<0)
			tir_x=0;
		if(tir_x>400)
			tir_x=400;
	}
}

void bullet_option()
{
	if(page2){
		if(bullet==0)
			bullet_y=-20;
		else if(bullet==1)
		{
			if(bullet_y>=550)
				exit(0);
			else bullet_y+=5;
		}
	}
}

void die()
{
	if(page2)
		for(i=0;i<10;i++)
			if(bullet_x>=ballon_x[i] && bullet_x<=ballon_x[i]+50)
				if(bullet_y>=ballon_y[i] && bullet_y<=ballon_y[i]+70)
				{
					ballon[i]=0;
					bullet=0;
					bullet_y=-20;
					score+=5;
				}
}

int main()
{
	iSetTimer(1,die);
	iSetTimer(1,bullet_option);
	iSetTimer(1,position);
	iSetTimer(2000,create_ballon);
	iSetTimer(1,ballon_die);
	iSetTimer(1,ballon_move);
	iInitialize(500, 600, "Ballon Shooter");
	return 0;
}