/******************************************************************************************************

                                   *Snake Game 1.0 normal*

******************************************************************************************************/

#include <GL/glut.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#pragma comment(lib,"gdi32.lib") 

#define L 0.04
#define v 0.04
#define MAX_CHAR 128
#define remain 10
#define drop 20

int start, end, p, eaten, pause, isFirstTime, blink;
float a, d, s, w;
float color;
float t, oldt, seconds, endt;
float b[1000][2];
int arr[50][50];
int i, n, k;
long long int score;
int eachscore, j, update;

void keyboard(unsigned char key, int temp1,int temp2);
void DrawIt(void);
void Tick(int n);
void game(void);
void begin(void);
void out(void);
void drawString(const char* str);
void begin_cont(void);
void selectFont(int size, int charset, const char* face);
void getappleposition(void);
void initialwall(void);
void Speed(int n);
void reset(void);
void pausefunc(void);
void drawDigital(int digital, float positionx, float positiony);
void drawNumber(int number, int size, float colorr, float colorg, float colorb, float positionx, float positiony);

void drawDigital(int digital, float positionx, float positiony){    //draw each digital of a number
	switch (digital){
		case 0:
			glRasterPos2f(positionx, positiony);
			drawString("0");
			break;
		case 1:
			glRasterPos2f(positionx, positiony);
			drawString("1");
			break;
		case 2:
			glRasterPos2f(positionx, positiony);
			drawString("2");
			break;
		case 3:
			glRasterPos2f(positionx, positiony);
			drawString("3");
			break;
		case 4:
			glRasterPos2f(positionx, positiony);
			drawString("4");
			break;
		case 5:
			glRasterPos2f(positionx, positiony);
			drawString("5");
			break;
		case 6:
			glRasterPos2f(positionx, positiony);
			drawString("6");
			break;
		case 7:
			glRasterPos2f(positionx, positiony);
			drawString("7");
			break;
		case 8:
			glRasterPos2f(positionx, positiony);
			drawString("8");
			break;
		case 9:
			glRasterPos2f(positionx, positiony);
			drawString("9");
			break;
		}
}

void drawNumber(int number, int size, float colorr, float colorg, float colorb, float positionx, float positiony){   //draw a number
	int n[100], dig, j;
	dig=1;
	while (number / (int) pow(10.0 , dig))
		dig++;
	if (dig <= 4)
		update = 50;
	if (dig == 5)
		update = 500;
	if (dig == 6)
		update = 5000;
	if (dig >= 7)
		update = 50000;
	for (i=1; i<=dig; i++)
		n[i-1] = number / (int)pow(10.0 , i-1) - number / (int)pow(10.0, i) * 10;
	selectFont(size,ANSI_CHARSET,"Comic Sans MS");
	glColor3f(colorr, colorg, colorb);
	j=0;
	for (i=0; i<dig; i++,j++)
		drawDigital(n[i], positionx-j*(float)size/890, positiony);
}

void pausefunc(void){                              //pause when press 'space'
	selectFont(35,ANSI_CHARSET,"Comic Sans MS");
	oldt = t;
	t = 500;
	color = 1;
	initialwall();
	getappleposition();
	glColor3f(0.0, 0.0, 0.0);
	for (i=0; i<k; i++)
		glRectf(b[i][0], b[i][1], b[i][0] + L, b[i][1] - L);
	for (i=k; i<n; i++){
		if (color)
			glColor3f(0.12549, 0.52549, 0.145098);
		else 
			glColor3f(0.0549019, 0.2274509, 0.06274550);
		glRectf(b[i][0], b[i][1], b[i][0] + L, b[i][1] - L);
		color = 1 - color;
	}
	if (blink){
		glColor3f(0.0, 64.0/255, 0.0);
		glRasterPos2f(-0.35f, 0.0f);
		drawString("Press 'Space' to resume");
	}
	drawNumber(score, 35, 1.0, 0, 0, 1.35, 0.7);
	glRasterPos2f(1.05, 0.8);
	drawString("your score: ");
	blink = 1 - blink;
}

void reset(void){   //reset the initialization 
	int jj;
	seconds = 0;
	j = 1;
	score = 0;
	eachscore = 100;
	blink = 0;
	isFirstTime = 1;
	pause = 0;
	k = 0;
	start = 0;
	end = 0;
	eaten = 1;
	n = 4;
	p = 0;
	d = v;
	a = 0;
	s = 0;
	w = 0;
	t = 200;
	endt = 0;
	for (i=0;i<50;i++)
		for (jj=0;jj<50;jj++)
			arr[i][jj] = 0;
	b[0][0] = -0.08;
	b[0][1] = 0.04;
	for (i=1; i<n; i++){
		b[i][0] = b[i-1][0] + L;
		b[i][1] = b[0][1];
	}
	for (i=0; i<n-1; i++){
		arr[(int)((b[i][0] + 1) * 25 + 0.5)][(int)((b[i][1] + 1) * 25 - 0.5)] = 1;
	}
}

void drawString(const char* str) {       //draw string
    static int isFirstCall = 1;
    static GLuint lists;
	if( isFirstCall ) {
	    isFirstCall = 0;
        lists = glGenLists(MAX_CHAR);
        wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
    }
    for(; *str!='\0'; ++str)
		glCallList(lists + *str);
}

void out(void){       //ending picture
	start = 0;
	glColor3f(1.0, 0.0, 0.0);
    glRasterPos2f(0.05f, 0.3f);
    drawString("Game Over");
	glColor3f(0.0, 64.0/255, 0.0);
	glRasterPos2f(0.3f, -0.7f);
	drawString("Press 'R' to restart");
	t=20;
	glColor3f(0.0, 0.0, 1.0);
	glRasterPos2f(-0.15, -0.1);
	drawString("Your Score: ");
	if (j<=score){
		glColor3f(184.0/255, 134.0/255, 11.0/255);
		glRectf(0.60, -0.1, 0.80,-0.2);
		drawNumber(j, 35, 0.0, 0.0, 1.0, 0.65, -0.1);
		j += rand()%update + update;
	}
	else if (j>=score){
		drawNumber(score, 35, 0.0, 0.0, 1.0, 0.65, -0.1);
	}
	glColor3f(0.0, 64.0/255, 0.0);
	glRasterPos2f(-0.9, -0.58);
	drawString("coding monkeys :");
	glRasterPos2f(-0.9, -0.68);
	drawString("God Feng!!!");
	glRasterPos2f(-0.9, -0.78);
	drawString("God LZ!!!");
	glRasterPos2f(-0.9, -0.88);
	drawString("God NAN!!!");
	glRasterPos2f(-0.9, -0.98);
	drawString("zhazha fei..=.=~~");
	endt += t;
	if (endt > 15000){
		glColor3f(0.0, 0.0, 1.0);
		glRasterPos2f(-0.3, -0.98);
		drawString("¡û_¡ûYeah he's lying...But don't tell him...");
	}
}

void selectFont(int size, int charset, const char* face){   //change the size and style of characters
	HFONT hFont = CreateFontA(size, 0,0,0,FW_MEDIUM,0,0,0,charset,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(),hFont);
	DeleteObject(hOldFont);
}

void begin(void){         //beginning picture
	selectFont(35,ANSI_CHARSET,"Comic Sans MS");
	glColor3f(1.0, 0.0, 0.0);
    glRasterPos2f(0.05f, 0.3f);
    drawString("Snake Game");
	glColor3f(0.0,0.0,1.0);
	glRasterPos2f(-0.1f,-0.2f);
	drawString("Press 'Enter' to start");
	glColor3f(0.0,64.0/255,0.0);
	glRasterPos2f(-0.1f,-0.55f);
	drawString("Use 'W,A,S,D' to control");
	glRasterPos2f(-0.1f,-0.65f);
	drawString("Press 'Space' to pause");
	glRasterPos2f(-0.9f,-0.9f);
	drawString("designed by X501 workshop");
}

void initialwall(void){    //the initial wall around the windows
	int i;
	glColor3f(0.0,0.0,0.0);
	for (i=0; i<50; i++){
		arr[i][0] = 1;
		arr[i][49] = 1;
		glColor3f(0.0,0.0,0.0);
		glRectf( (i/25.0-1), (-0.96), (i/25.0-1 + L), (-0.96 - L));
		glRectf( (i/25.0-1), (1), (i/25.0-1 + L), (1 - L));
	}
	for (i=0; i<50; i++){
		arr[0][i] = 1;
		arr[49][i] = 1;
		glRectf( (0.96), (i/25.0-1), (0.96 + L), (i/25.0-1 + L));
		glRectf( (-1), (i/25.0-1), (-1 + L), (i/25.0-1 + L));
	}
}

void getappleposition(void){    //create an apple randomly
	static int x, y;
	srand( (int) time(NULL));
	if (eaten == 1){
		arr[x][y] = 0;
		do{
		x = (rand() % 46) + 2;
		y = (rand() % 46) + 2;
		}
		while (arr[x][y] == 1);
		eaten = 0;
	}
	arr[x][y]=-1;
	glColor3f(190.0/255, 0.0, 0.0);
	glRectf( (x/25.0-1), (y/25.0-0.96), (x/25.0-1 + L), (y/25.0 -0.96 - L));
}

void Speed(int n){  //control speed by  frequence(f=1/t)
	if(t>=75)
	   t=200/(0.08*((int)(n/4)*4)+0.6);
	else if((t>=65)&&(t<75))
	   t=200/(0.2*((int)(n/8)*8)-1);
	 
}

void game(void){    //main function of game
	color = 1;
	initialwall();
	glColor3f(0.0, 0.0, 0.0);
	for (i=0; i<k; i++)      //change the dropped body into wall
		glRectf(b[i][0], b[i][1], b[i][0] + L, b[i][1] - L);
	for (i=0; i<k; i++)
		arr[(int)((b[i][0] + 1) * 25 + 0.5)][(int)((b[i][1] + 1) * 25 - 0.5)] = 1;
	getappleposition();
	for (i=k; i<n; i++){           //draw the snake
		if (color)
			glColor3f(0.12549, 0.52549, 0.145098);
		else 
			glColor3f(0.0549019, 0.2274509, 0.06274550);
		glRectf(b[i][0], b[i][1], b[i][0] + L, b[i][1] - L);
		color = 1 - color;
	}
	if (arr[(int)((b[n-1][0] + 1) * 25 + 0.5)][(int)((b[n-1][1] + 1) * 25 - 0.5)] == -1) {        //eat the apple
		eaten = 1;
		n++;
		b[n-1][0] = b[n-2][0] + (a+d);
		b[n-1][1] = b[n-2][1] + (s+w);
		if (!  (( (b[n-1][0] == b[n-2][0])  &&  (b[n-2][0]== b[n-3][0]) )  ||  ((b[n-1][1] == b[n-2][1]) && (b[n-2][1] == b[n-3][1]))) ) 
			p = 1-p;
		arr[(int)((b[n-2][0] + 1) * 25 + 0.5)][(int)((b[n-2][1] + 1) * 25 - 0.5)] = 1;
		score += eachscore;
		eachscore += 13;
	}
	else{               //move and turn
		eaten = 0;
		arr[(int)((b[k][0] + 1) * 25 + 0.5)][(int)((b[k][1] + 1) * 25 - 0.5)] = 0;
		for (i=k; i<n-1; i++){
			b[i][0] = b[i+1][0];
			b[i][1] = b[i+1][1];
		}
		arr[(int)((b[n-2][0] + 1) * 25 + 0.5)][(int)((b[n-2][1] + 1) * 25 - 0.5)] = 1;
		b[n-1][0] += (a+d);
		b[n-1][1] += (s+w);
		if (!  (( (b[n-1][0] == b[n-2][0])  &&  (b[n-2][0]== b[n-3][0]) )  ||    ((b[n-1][1] == b[n-2][1]) && (b[n-2][1] == b[n-3][1]))) ) 
			p = 1-p;
	}
	if (arr[(int)((b[n-1][0] + 1) * 25 + 0.5)][(int)((b[n-1][1] + 1) * 25 - 0.5)] == 1) 
		end = 1;
	if ((n-remain)<0) 
		k=0;
	else if ((n-remain)%drop == 0)
		k = drop * ((int)(n-remain)/drop);
	drawNumber(score, 35, 1.0, 0, 0, 1.35, 0.7);
	seconds+=t;
	if (seconds>=2000){      //add 1 score every 2 seconds
		seconds-=2000;
		score++;
	}
	glRasterPos2f(1.05, 0.8);
	drawString("your score: ");
	glColor3f(0.0, 64.0/255, 0.0);
	glRasterPos2f(1.05, -0.7);
	drawString("press ");
	glRasterPos2f(1.05, -0.8);
	drawString("'Space'");
	glRasterPos2f(1.05, -0.9);
	drawString("to pause");
}

void keyboard(unsigned char key, int temp1,int temp2) {     //keyboard control function
	if (key==13 && !start) 
		start=1;
	if (key==' ' && start) 
		pause=1;
	if (!isFirstTime)
		if (pause && key==' ') {
			pause=0;
			isFirstTime=1;
			t=oldt;
		}
	if(pause) 
		isFirstTime=0;
	if (!pause && !p && !(key=='r' || key=='R')){
		if(key=='w' || key=='W'){
			w=v;
			a=0;
			d=0;
			s=0;
		} 
		if(key=='s' || key=='S'){
			s=-v;
			a=0;
			d=0;
			w=0;
		} 
	}
	else if (!pause && p && !(key=='r' || key=='R')){
		if(key=='d' || key=='D'){
			d=v;
			w=0;
			s=0;
			a=0;
		}
		if(key=='a' || key=='A'){
			a=-v;
			w=0;
			s=0;
			d=0;
		} 
	}
	else if (!start && (key=='r' || key=='R')) 
		reset();
}

void DrawIt(void){    //drwa it!
	glClearColor(184.0/255, 134.0/255, 11.0/255, 0.9);
	glClear(GL_COLOR_BUFFER_BIT);
	if (!pause){
		if ((start) && (!end))
			game();
		else if (!start && !end)
			begin();
		else if (end)
			out();
		Speed(n);
	}
	else
		pausefunc();
	glFlush();
}

void Tick(int n) {     //delay function
	glutTimerFunc(t, Tick, 0);
	glutPostRedisplay();
	glutKeyboardFunc(keyboard);
}

int main(int argc, char *argv[]){
	reset();
	glutInit(&argc, argv);
	glutInitWindowPosition(200, 20);
	glutInitWindowSize(812.5, 650);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Snake Game.exe");
	gluOrtho2D(-1, 1.5, -1, 1);
	glutDisplayFunc(DrawIt);
	glutTimerFunc(t, Tick, 0);
	glutKeyboardFunc(keyboard);
	Speed(n);
	glutMainLoop();
	return 0;
}