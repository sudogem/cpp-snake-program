/* Turbo C Final Project */
/* Simple snake program  */
#include <iostream.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>
#include <time.h>

#define TOPBORDER     3
#define BOTTOMBORDER 22
#define LEFTBORDER   10
#define RIGHTBORDER  70
#define BORDER      219


#define MAX          50
#define INITLENGTH   10

#define LEFT         75
#define RIGHT        77
#define UP           72
#define DOWN         80

#define FRUITPIC     15
#define HEADPIC       2
#define HORPIC      205
#define DLPIC       187
#define ULPIC       188
#define URPIC       200
#define DRPIC       201
#define VERPIC      186
#define TAILPIC       4
#define NONE         32

#define YES           1
#define NO            0

#define GAMEOVER      0
#define GOOD          1

class Snake{

	private:
		struct Body{
			int x;
			int y;
			int IsPart;
			char Pic;
		}SnakeSegment[MAX];

		int  PrevDirection;
		void InitSnake(void);
		void EraseSnake(void);
		void Shift(void);
		int  XIsOut(int x);
		int  YIsOut(int y);
		int  IsTouching(int x,int y);
		void CheckDirection(void);

	public:
		friend int PosIsVacant(int x, int y);
		int  Direction;
		Snake(void);
		void DisplaySnake(void);
		int Move(void);
		void MoveLeft(void);
		void MoveRight(void);
		void MoveUp(void);
		void MoveDown(void);
		void AddSegment(void);
};

Snake::Snake(void){
	InitSnake();
}

void Snake::InitSnake(void){
	int i,j;

	Direction=PrevDirection=RIGHT;

	j=40-(INITLENGTH/2);
	for(i=0;i<INITLENGTH;i++,j--){
		SnakeSegment[i].x=j;
		SnakeSegment[i].y=BOTTOMBORDER-5;
		SnakeSegment[i].Pic=HORPIC;
		SnakeSegment[i].IsPart=YES;
	}

	SnakeSegment[0].Pic=HEADPIC;
	SnakeSegment[INITLENGTH-1].Pic=TAILPIC;

	for(i=INITLENGTH,j=35;i<=MAX-1;i++,j++){
		SnakeSegment[i].x=1;
		SnakeSegment[i].y=1;
		SnakeSegment[i].Pic=NONE;
		SnakeSegment[i].IsPart=NO;
	}
}

void Snake::DisplaySnake(void){
	int i;

	textcolor(YELLOW);
	i=0;
	gotoxy(SnakeSegment[i].x,SnakeSegment[i].y);
	putch(SnakeSegment[i].Pic);
	i++;
	textcolor(GREEN);
	while(SnakeSegment[i].IsPart==YES && i<MAX){
		gotoxy(SnakeSegment[i].x,SnakeSegment[i].y);
		putch(SnakeSegment[i].Pic);
		i++;
	}
}

void Snake::EraseSnake(void){
	int i;
	i=0;
	while(SnakeSegment[i].IsPart==YES && i<MAX){
		//gotoxy(SnakeSegment[i].x,SnakeSegment[i].y);
		//putch(NONE);
		i++;
	}
	//gotoxy(SnakeSegment[0].x,SnakeSegment[0].y);
	//putch(NONE);

	gotoxy(SnakeSegment[i-1].x,SnakeSegment[i-1].y);
	putch(NONE);


}
int Snake::XIsOut(int x){
	if (x>=RIGHTBORDER || x<=LEFTBORDER){
		return YES;
	}
	else return NO;
}

int Snake::YIsOut(int y){
	if (y>=BOTTOMBORDER || y<=TOPBORDER){
		return YES;
	}
	else return NO;
}

int Snake::IsTouching(int x, int y){
	int i=1;
	while(SnakeSegment[i].IsPart==YES || i<MAX){
		if (SnakeSegment[i].x==x && SnakeSegment[i].y==y) return YES;
		i++;
	}
	return NO;
}


void Snake::Shift(void){
	int LastSegment,j;

	EraseSnake();
	LastSegment=1;
	//Get the last segment
	while(SnakeSegment[LastSegment].IsPart==YES && LastSegment<MAX){
		++LastSegment;
	}
	--LastSegment;
	j=LastSegment;
	for(;j>0;j--){
		SnakeSegment[j].x=SnakeSegment[j-1].x;
		SnakeSegment[j].y=SnakeSegment[j-1].y;
		SnakeSegment[j].Pic=SnakeSegment[j-1].Pic;
	}
	SnakeSegment[LastSegment].Pic=TAILPIC;

}

//Note AddSegment Before Shifting
void Snake::AddSegment(void){
	int i;
	i=7;
	while(SnakeSegment[i].IsPart==YES && i<MAX){
		++i;
	}
	SnakeSegment[i].x=SnakeSegment[i-1].x;
	SnakeSegment[i].y=SnakeSegment[i-1].y;
	SnakeSegment[i].Pic=TAILPIC;
	SnakeSegment[i].IsPart=YES;
}

void Snake::CheckDirection(void){
	switch(Direction){
		case LEFT: { if (PrevDirection==RIGHT) Direction=RIGHT; break;}
		case RIGHT:{ if (PrevDirection==LEFT) Direction=LEFT; break;}
		case UP:   { if (PrevDirection==DOWN) Direction=DOWN; break;}
		case DOWN: { if (PrevDirection==UP) Direction=UP; break;}
	}
}

int Snake::Move(void){
	int x,y;
	//static int count=0;

	x=SnakeSegment[0].x;
	y=SnakeSegment[0].y;

	CheckDirection();
	sound(500);
	switch(Direction){
		case LEFT: {  if (XIsOut(x-1)==YES) goto myExit;//return GAMEOVER;
									if (IsTouching(x-1,y)==YES) goto myExit; //return GAMEOVER;
									MoveLeft();	break;
							 }
		case RIGHT:{ if (XIsOut(x+1)==YES) goto myExit; //return GAMEOVER;
								 if (IsTouching(x+1,y)==YES) goto myExit; //return GAMEOVER;
								 MoveRight(); break;
							 }
		case UP:   { if (YIsOut(y-1)==YES) goto myExit;//return GAMEOVER;
								 if (IsTouching(x,y-1)==YES) goto myExit; //return GAMEOVER;
								 MoveUp(); break;
							 }
		case DOWN: { if (YIsOut(y+1)==YES) goto myExit; //return GAMEOVER;
								 if (IsTouching(x,y+1)==YES) goto myExit;  //return GAMEOVER;
								 MoveDown(); break;
							 }
	}
	DisplaySnake();
	nosound();
	return GOOD;
	myExit:
	nosound();
	return GAMEOVER;
}


void Snake::MoveLeft(void){
	Shift();
	SnakeSegment[0].x=SnakeSegment[0].x-1;
	switch(PrevDirection){
		case LEFT:
		case RIGHT:{
				SnakeSegment[1].Pic=HORPIC;
				break;
			}
		case UP:{
				SnakeSegment[1].Pic=DLPIC;
				break;
			}
		case DOWN:{
				SnakeSegment[1].Pic=ULPIC;
				break;
			}
	}
	PrevDirection=LEFT;
	return;
}

void Snake::MoveRight(void){
	Shift();
	SnakeSegment[0].x=SnakeSegment[0].x+1;
	switch(PrevDirection){
		case LEFT:
		case RIGHT:{
				SnakeSegment[1].Pic=HORPIC;
				break;
			}
		case UP:{
				SnakeSegment[1].Pic=DRPIC;
				break;
			}
		case DOWN:{
				SnakeSegment[1].Pic=URPIC;
				break;
		}
	}
	PrevDirection=RIGHT;
	return;
}

void Snake::MoveUp(void){
	Shift();
	SnakeSegment[0].y=SnakeSegment[0].y-1;
	switch(PrevDirection){
		case DOWN:
		case UP:{
				SnakeSegment[1].Pic=VERPIC;
				break;
			}
		case LEFT:{
				SnakeSegment[1].Pic=URPIC;
				break;
			}
		case RIGHT:{
				SnakeSegment[1].Pic=ULPIC;
				break;
		}
	}
	PrevDirection=UP;
	return;
}

void Snake::MoveDown(void){
	Shift();
	SnakeSegment[0].y=SnakeSegment[0].y+1;
	switch(PrevDirection){
		case UP:
		case DOWN:{
				SnakeSegment[1].Pic=VERPIC;
				break;
		}
		case LEFT:{
				SnakeSegment[1].Pic=DRPIC;
				break;
			}
		case RIGHT:{
				SnakeSegment[1].Pic=DLPIC;
				break;
		}
	}
	PrevDirection=DOWN;
	return;
}

class Fruit{
	private:
		void GenerateCoords(void);
		int  GenerateX(void);
		int  GenerateY(void);
		//int  CheckCoords(int xCoord, int yCoord);
	public:
		int  x;
		int  y;
		char Pic;
		Fruit(void);
		void GenerateFruit(void);
		void DisplayFruit(void);
		int  IsVacant(int CurX,int CurY);
};

Fruit::Fruit(void){
	x=40;
	y=10;
	Pic=FRUITPIC;
}

void Fruit::GenerateCoords(void){
	int xTemp;
	int yTemp;
	do{
		xTemp=GenerateX();
		yTemp=GenerateY();
	}while(IsVacant(xTemp,yTemp)==NO);
	x=xTemp;
	y=yTemp;
}

int  Fruit::IsVacant(int CurX,int CurY){
	int result;
	int PosIsVacant(int x,int y);

	result=PosIsVacant(CurX,CurY);
	return result;
}

int Fruit::GenerateX(void){
	int xtemp;
	randomize();
	do{
		xtemp=LEFTBORDER+random(RIGHTBORDER-LEFTBORDER)+1;
	}while(xtemp<=LEFTBORDER || xtemp>=RIGHTBORDER);
	return xtemp;
}

int Fruit::GenerateY(void){
	int ytemp;
	randomize();
	do{
		ytemp=TOPBORDER+random(BOTTOMBORDER-TOPBORDER)+1;
	}while(ytemp<=TOPBORDER || ytemp>=BOTTOMBORDER);
	return ytemp;
}

void Fruit::GenerateFruit(void){
	GenerateCoords();
	DisplayFruit();
}

void Fruit::DisplayFruit(void){
	gotoxy(x,y);
	textcolor(RED);
	putch(FRUITPIC);

}

class Interval{
	private:
		long milliseconds;
	public:
		Interval(void);
		void SetTime(int ms);
		void DelayIt(void);
		void Faster(void);
};

Interval::Interval(void){
	milliseconds=100;
}

void Interval::SetTime(int ms){
	milliseconds=ms;
}

void Interval::DelayIt(void){
	delay(milliseconds);
}

void Interval::Faster(void){
	milliseconds=milliseconds-100;
}

Snake MySnake;
Fruit MyFruit;
Interval MyInterval;

int PosIsVacant(int x,int y){
	int i;

	i=0;
	while(MySnake.SnakeSegment[i].IsPart==YES && i<MAX){
		if(MySnake.SnakeSegment[i].x==x && MySnake.SnakeSegment[i].y==y) return NO;
		i++;
	}
	return YES;
}

void main(){
	int Status;

	int MoveSnake(void);
	void ShowBorder(void);
	void MsgBox(void);

	textmode(C80);
	textbackground(BLACK);
	textcolor(LIGHTGRAY);
	clrscr();

	_setcursortype(_NOCURSOR);

	ShowBorder();

	MyFruit.DisplayFruit();
	MySnake.DisplaySnake();

	do{
		Status=MoveSnake();
		MyInterval.DelayIt();
	}while (Status==GOOD);
	MsgBox();
	textcolor(LIGHTGRAY);
	return;
}

int MoveSnake(void){
	int Direction;
	int Outcome;
	if(kbhit()){
		if((Direction=getch())==0){
			Direction=getch();
			switch(Direction){
				case LEFT:{ MySnake.Direction=LEFT; break;}
				case RIGHT:{ MySnake.Direction=RIGHT; break;}
				case UP:{ MySnake.Direction=UP; break;}
				case DOWN:{ MySnake.Direction=DOWN; break;}
			}
		}
	}
	Outcome=MySnake.Move();
	return Outcome;
}

void ShowBorder(void){
	int i;
	textcolor(BLUE);
	gotoxy(LEFTBORDER-1,TOPBORDER);
	for(i=LEFTBORDER-1;i<=RIGHTBORDER+1;i++){
		putch(BORDER);
	}

	for(i=TOPBORDER+1;i<BOTTOMBORDER;i++){
		gotoxy(LEFTBORDER-1,i);
		putch(BORDER);putch(BORDER);
	}

	for(i=TOPBORDER+1;i<BOTTOMBORDER;i++){
		gotoxy(RIGHTBORDER,i);
		putch(BORDER);putch(BORDER);
	}

	gotoxy(LEFTBORDER-1,BOTTOMBORDER);
	for(i=LEFTBORDER-1;i<=RIGHTBORDER+1;i++){
		putch(BORDER);
	}
}

#define T        10
#define B        14
#define L        35
#define R        45

void MsgBox(void){
	void DrawBoxBorder(void);

	DrawBoxBorder();
	textbackground(WHITE);
	textcolor(RED+BLINK);
	gotoxy(36,((B-T)/2+T));
	cprintf(" GAMEOVER");
	textbackground(BLACK);
	textcolor(LIGHTGRAY);
	while(getch()!=13);
}

void DrawBoxBorder(void){
	int i,j;

	gotoxy(L,T);
	textbackground(RED);
	textcolor(WHITE);
	for (i=L;i<=R+1;i++){
		putch(220);
	}
	textbackground(WHITE);
	textcolor(BLACK);
	for (i=L;i<=R+1;i++){
		for(j=T+1;j<=B;j++){
			gotoxy(i,j);
			putch(32);
		}
	}
	textbackground(BLACK);
	textcolor(LIGHTGRAY);
}