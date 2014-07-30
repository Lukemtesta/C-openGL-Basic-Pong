
/* Basic Pong - Creator; Luke Testa  
  
  Copyright (c) 2014 Luke Marcus Biagio Testa
All rights reserved.

Redistribution and use in source and binary forms are permitted
provided that the above copyright notice and this paragraph are
duplicated in all such forms and that any documentation,
advertising materials, and other materials related to such
distribution and use acknowledge that the software was developed
by the Luke Marcus Biagio Testa. The name of the
Luke Marcus Biagio Testa may not be used to endorse or promote products derived
from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

  1 = 1 Player Mode
  2 = 2 Player Mode
 
  Difficulty;
  H = HARD
  M = Intermediate
  E = Easy
 
  Spacebar = Start Game
  R = Reset Score
  ESC = Exit Game
  I = Print instructions
  
  
  W = Left Stick Up
  S = Left Stick Down

  O = Right stick up
  L = Right Stick Down
  
*/


#include <iostream>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

using namespace std;

float _LEFT_MOVE_UP=0.0f, _LEFT_MOVE_DOWN=0.0f, _LEFT_TOTAL_MOVE=0.0f;
float _RIGHT_MOVE_UP=0.0f, _RIGHT_MOVE_DOWN=0.0f, _RIGHT_TOTAL_MOVE=0.0f;
float _BARRIER_TOP = 1.6f, _BARRIER_BOTTOM = -2.0f;
float _BALL_X=0.8f, _BALL_Y=0.0f;
float LeftB = -6.0f, RightB = 6.0f;
int RESET = 0, players=1;
int BOOLEAN_W = 0.0f, BOOLEAN_S =0.0f, BOOLEAN_O = 0.0f, BOOLEAN_L = 0.0f;
int hard = 3, medium = 2, easy = 1;
int difficulty = easy, level = 1;
float CENTREY = 0.0f, CENTREX = 0.0f, L2CENTREX;
int Lscore=0, Rscore=0;

int GAME_START=0, start = 0;
signed int WALL_TOP = 2.4f, WALL_BOTTOM = -2.2f;

//Print Instructions to screen
void printbuttons(void)
{
	cout << "1 = 1 Player Mode\n2 = 2 Player Mode\n\nDifficulty;\nM = Intermediate\nE = Easy\n\nSpacebar = Start Game\nR = Reset Score\nESC = Exit Game\n\n(2 Player Mode)\nW = Left Stick Up\nS = Left Stick Down\n\n(1 & 2 Player Modes)\nO = Right stick up\nL = Right Stick Down\n\n";
}




void keyup(unsigned char key, int x, int y)
{
//	cout << key << "\n";
//	if ( key == 's' )
	
	if(key =='w')
		BOOLEAN_W=0;
	if(key =='s')
		BOOLEAN_S=0;
	
	if(key == GLUT_KEY_UP)
		BOOLEAN_O=0;
	
	if(key ==GLUT_KEY_DOWN)
		BOOLEAN_L=0 ;
	
//	cout << BOOLEAN_W << " 1st W \n";
///	cout << _LEFT_MOVE_UP << "1st LEFT MOVE UP\n";
	
}

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
		case 32: // Spacebar
			GAME_START= start = 1;
			break;
		case '1':
			players=1;
			cout << "\n---------- 1 Player ----------\n\n";
			RESET = 1;
			break;
		case '2':
			players=2;
			cout << "\n---------- 2 Players ----------\n\n";
			RESET = 1;
			break;
		case 'h':
			difficulty = hard;
			cout << "\n---------- Hard ----------\n\n";
			RESET = 1;
			break;
		case 'm':
			difficulty = medium;
			cout << "\n---------- Intermediate ----------\n\n";
			RESET = 1;
			break;
		case 'e':
			difficulty = easy;
			cout << "\n---------- Easy ----------\n\n";
			RESET = 1;
			break;
		case 'r':
			RESET = 1;
			break;
		case 'i':
			printbuttons();
			break;
	}
	
	if(key =='w')
		BOOLEAN_W=1;
	if(key =='s')
		BOOLEAN_S=1;


	glutPostRedisplay();
}

void SpecialInput(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			BOOLEAN_O=1;
			break;
		case GLUT_KEY_DOWN:
			BOOLEAN_L=1;
			break;
		default:
			break;
	}

	glutPostRedisplay();
}


void SpecialInputUp(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			BOOLEAN_O=0;
			break;
		case GLUT_KEY_DOWN:
			BOOLEAN_L=0;
			break;
		default:
			break;
	}

	glutPostRedisplay();
}



//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL); //Enable color
	glClearColor(0.7f, 0.9f, 1.0f, 1.0f); //Change the background to sky blue

}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float _angle = 30.0f;
float _cameraAngle = 0.0f;


void RenderText(float x, float y, std::string text)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -10, 100);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)text.c_str() );

	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW); 
}


//Draws the 3D scene
void drawScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glColor3f(0.0f, 0.0f, 0.0f);
	if (  start == 0 )
	{
		RenderText(-0.4, 0.25, "Start: Spacebar      Move: Arrows      Difficulty: E, M, H");
		RenderText(-0.1, -0.25, "First to 5");
	}
	else
	{
		char str[4];

		sprintf_s(str, "%d", Rscore);
		RenderText(0.9, 0, str);
		sprintf_s(str, "%d", Lscore);
		RenderText(-0.9, 0, str);
	}

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);


	glTranslatef(0.0f,_LEFT_TOTAL_MOVE,0.0f);
	
	glBegin(GL_QUADS);
	
	//Left Stick
	glColor3f(0.5f, 0.0f, 0.8f);
	glVertex3f(LeftB, -0.2f, 0.0f);
	glVertex3f(LeftB, 0.4f, 0.0f);
	glVertex3f((LeftB - 0.1f), 0.4f, 0.0f);
	glVertex3f( (LeftB -0.1f), -0.2f, 0.0f);
	
	glEnd();
	
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);


	glTranslatef(0.0f, _RIGHT_TOTAL_MOVE, 0.0f);
	
	glBegin(GL_QUADS);
	
	//Right Stick
	glVertex3f( RightB, -0.2f, 0.0f);
	glVertex3f(RightB, 0.4f, 0.0f);
	glVertex3f( (RightB+0.1f), 0.4f, 0.0f);
	glVertex3f( (RightB+0.1f), -0.2f, 0.0f);

	glEnd();
	
		
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
	
	
	glTranslatef(_BALL_X, _BALL_Y, 0.0f);
	
	glBegin(GL_QUADS);
	
	//BALL

	if( start == 1 )
	{
		glColor3f(0.0f, 0.0f, 0.0f);	
		glVertex3f(-0.1f, 0.0f, 0.0f);
		glVertex3f(-0.1f, 0.1f, 0.0f);
		glVertex3f(0.0f, 0.1f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
	}
	
	glEnd(); 
	
	if(level==3 || level == 4)
	{
	
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
	
	
	glTranslatef(0.0f, CENTREY, 0.0f);
	
	glBegin(GL_QUADS);
	
	//Right Stick
	glVertex3f( 0.2f, -0.4f, 0.0f);
	glVertex3f(0.2f, 0.2f, 0.0f);
	glVertex3f( 0.3f, 0.2f, 0.0f);
	glVertex3f( 0.3, -0.4f, 0.0f);
	
	glEnd();
	
	}
	
	if(level==2 || level == 4)
	{

		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -5.0f);
		
		
		glTranslatef(L2CENTREX, 0.0f, 0.0f);
		
		glBegin(GL_QUADS);
		
		//Right Stick
		glVertex3f( -0.3f, 0.2f, 0.0f);
		glVertex3f(-0.4f, 0.3f, 0.0f);
		glVertex3f( 0.5f, 0.3f, 0.0f);
		glVertex3f( 0.5f, 0.2f, 0.0f);
		
		glEnd();
	}
		
	glPopMatrix();
			
	
	glutSwapBuffers();
}


int check=-2, SCORE=0;
float previousx=0.0f, previousy=0.0f,nextx=0.0f,nexty=0.0f, changex,changey, topR, topL, BottomR, BottomL, middletopR, middletopL, middlebottomR, middlebottomL;
float ceilingR,floorR,ceilingL,floorL;
float speedx=0.0f, speedy=0.0f;
float ceilingC,topC,middletopC,middlebottomC,bottomC,floorC,_bottomC,_floorC,_ceilingC,_topC,_middletopC,_middlebottomC;
int scoreBOOLEAN = 1;



// When a point is scored, reset all values to 0
void point(void)			
{
	previousx=previousy=nextx=nexty=changex=changey=0.0f; 
	_LEFT_TOTAL_MOVE=_RIGHT_TOTAL_MOVE=0.0f;
	_BALL_Y = 0.0f;
	_BALL_X = 1.0f;
}
	
// Determines Collisions and Ball motion
void moveBall(void)											// Grid Dimensions => Far right x[2.0/1.9] => Far left x[-2.0/-1.9] => Top y[2.1/2.0] => Bottom x[-2.0/-2.1]
{

	static int direction = 2;
		
	if(SCORE==1)											// When a point is scored, restart game
	{
		point();
		SCORE = GAME_START= check = -2;
		cout << Lscore << ":" << Rscore << "\n";
	}
	
	if( GAME_START==1 && check==-2 )					// If Game is a go, and nothing has been hit, then move ball to one side
	{										// If next xposition < Right Barrier (start of right stick drawing), then move the ball into new xposition (0.0 ball should now touch Right Barrier)
		check=-1;
		GAME_START = 0;
	} 
	
	if(check==-1)
	{
	//	cout << "score BOOLEAN \n" << scoreBOOLEAN;
		previousx = _BALL_X;
		if(scoreBOOLEAN == 1)
		_BALL_X += 0.2f;
		else {
			_BALL_X -= 0.2f;
		}

	}
	
	
	if( _BALL_Y >= WALL_TOP && ( previousx >= _BALL_X ) )																// Top Wall Collision
	{
		check=0; direction =1;
	}
	else if ( _BALL_Y >= WALL_TOP && ( _BALL_X >= previousx ))			
	{
		check=0; direction =0;
	}
	
	if( (_BALL_Y <= WALL_BOTTOM) && (_BALL_X	>= previousx) )															// Bottom Wall Collision
	{
		check=1; direction =1;
	}
	else if ( (_BALL_Y <= WALL_BOTTOM) &&( previousx >= _BALL_X ) )			
	{
		check=1; direction =0;
	}
			
	
	changex = _BALL_X - previousx;																						// Uses current position and previous position
	changey = _BALL_Y - previousy;																						// to calculate change in position and next position
	nextx = changex + _BALL_X;
	nexty = changey + _BALL_Y;
	topR = _RIGHT_TOTAL_MOVE + 0.2f;
	topL = _LEFT_TOTAL_MOVE + 0.2f;
	middletopR = _RIGHT_TOTAL_MOVE + 0.1f;
	middletopL = _LEFT_TOTAL_MOVE + 0.1f;
	middlebottomR = _RIGHT_TOTAL_MOVE - 0.1f;
	middlebottomL = _LEFT_TOTAL_MOVE - 0.1f;
	ceilingR = _RIGHT_TOTAL_MOVE + 0.3f;
	floorR = _RIGHT_TOTAL_MOVE - 0.3f;
	ceilingL = _LEFT_TOTAL_MOVE + 0.3f;
	floorL = _LEFT_TOTAL_MOVE - 0.3f;
	BottomR = _RIGHT_TOTAL_MOVE - 0.2f;
	BottomL = _LEFT_TOTAL_MOVE - 0.2f;
	speedx = sqrt(changex*changex);
	speedy = sqrt(changey*changey);
	
	if(level==3)
	{
	ceilingC = CENTREY +0.3f;
	topC = CENTREY + 0.2f;
	middletopC = CENTREY + 0.1f;
	middlebottomC = CENTREY -0.1f;
	bottomC = CENTREY - 0.2f;
	floorC = CENTREY - 0.3f;
	}
	
	if(level==2)
	{
		_ceilingC = L2CENTREX +0.3f;
		_topC = L2CENTREX + 0.2f;
		_middletopC = L2CENTREX + 0.1f;
		_middlebottomC = L2CENTREX -0.1f;
		_bottomC = L2CENTREX - 0.2f;
		_floorC = L2CENTREX - 0.3f;
	}
	
//	topC = CENTREY + 0.2f;
//	middletopC = CENTREY + 0.1f;
//	middlebottomC = CENTREY - 0.1f;
//	ceilingR = CENTREY + 0.3f;
//	floorR = CENTREY - 0.3f;
	
	if(nextx >= RightB)																									// Conditions for Right Wall Collision
	{
	//	cout << topR << "topR \n";

			if( nexty<=(topR+0.07) && nexty>=(topR-0.07) )
				check=4;
				//cout << check << " check = \n";
			else 
				if( nexty<=(middletopR+0.07f) && nexty>=(middletopR-0.07f) )
					check=6;
				else
					if(	(nexty<=(_RIGHT_TOTAL_MOVE+0.07f))	&& (nexty>=(_RIGHT_TOTAL_MOVE-0.07f)))																// Collision Detection for centre of L&R blocks
						check = 2;
					else 
						if(	(nexty<=(middlebottomR+0.07f))	&& (nexty>=(middlebottomR-0.07f)))																// Collision Detection for centre of L&R blocks
							check = 3;
						else 
							if(	(nexty<=(BottomR+0.07f))	&& (nexty>=(BottomR-0.07f)))																// Collision Detection for centre of L&R blocks
								check = 5;
							else 
								if(	(nexty<=(ceilingR+0.07f))	&& (nexty>=(ceilingR-0.07f)))																// Collision Detection for centre of L&R blocks
									check = 12;
								else 
									if(	(nexty<=(floorR+0.07f))	&& (nexty>=(floorR-0.07f)))																// Collision Detection for centre of L&R blocks
										check = 13;
	}
	
	if(level==3 || level == 4)
	{
		if(nextx >= 0.35 && nextx <= 0.45)																									// Conditions for Right Wall Collision
		{
			//	cout << topR << "topR \n";
			
			if( _BALL_Y<=(topC+0.07) && _BALL_Y>=(topC-0.07) )
				check=7;
			//cout << check << " check = \n";
			else 
				if( _BALL_Y<=(middletopC+0.07f) && _BALL_Y>=(middletopC-0.07f) )
					check=8;
				else
					if(	(_BALL_Y<=(CENTREY+1.07f))	&& (_BALL_Y>=(CENTREY-1.07f)))																// Collision Detection for centre of L&R blocks
						check = 9;
					else 
						if(	(_BALL_Y<=(middlebottomC+0.07f))	&& (_BALL_Y>=(middlebottomC-0.07f)))																// Collision Detection for centre of L&R blocks
							check = 11;
						else 
							if(	(_BALL_Y<=(bottomC+0.07f))	&& (_BALL_Y>=(bottomC-0.07f)))																// Collision Detection for centre of L&R blocks
								check = 10;
							else 
								if(	(_BALL_Y<=(ceilingC+0.07f))	&& (_BALL_Y>=(ceilingC-0.07f)))																// Collision Detection for centre of L&R blocks
									check = 14;
								else 
									if(	(_BALL_Y<=(floorC+0.07f))	&& (_BALL_Y>=(floorC-0.07f)))																// Collision Detection for centre of L&R blocks
										check = 15;
		}
		
		if(nextx >= -0.15 && nextx <= 0.25)																								// Conditions for Left Wall Collision
		{
			if( _BALL_Y<=(topC+0.07) && _BALL_Y>=(topC-0.07) )
				check=4;
			//cout << check << " check = \n";
			else 
				if( _BALL_Y<=(middletopC+0.07f) && _BALL_Y>=(middletopC-0.07f) )
					check=6;
				else
					if(	(_BALL_Y<=(CENTREY+0.07f))	&& (_BALL_Y>=(CENTREY-0.07f)))															
						check = 2;
					else 
						if(	(_BALL_Y<=(middlebottomC+0.07f))	&& (_BALL_Y>=(middlebottomC-0.07f)))															
							check = 3;
						else 
							if(	(_BALL_Y<=(bottomC+0.07f))	&& (_BALL_Y>=(bottomC-0.07f)))																
								check = 5;
							else 
								if(	(_BALL_Y<=(ceilingC+0.07f))	&& (_BALL_Y>=(ceilingC-0.07f)))																// Collision Detection for centre of L&R blocks
									check = 12;
								else 
									if(	(_BALL_Y<=(floorC+0.07f))	&& (_BALL_Y>=(floorC-0.07f)))																// Collision Detection for centre of L&R blocks
										check = 13;
			
		}
		
		if( (changex<0) &&  (nextx<=(CENTREY+0.07f)	&& nextx>=(CENTREY-0.07f)) )
		{
			previousx = _BALL_X;
			previousy = _BALL_Y;
			_BALL_X -= speedx;
			_BALL_Y += changey;
		}	
	} 
	
	if(level==2 || level == 4)
	{
		if(nexty >= 0.35 && nexty <= 0.45)																									// Conditions for Right Wall Collision
		{
			//	cout << topR << "topR \n";
			
			if( nextx<=(_topC+0.07) && nextx>=(_topC-0.07) )
				check=4;
			//cout << check << " check = \n";
			else 
				if( nextx<=(_middletopC+0.07f) && nextx>=(_middletopC-0.07f) )
					check=6;
				else
					if(	(nextx<=(L2CENTREX+1.07f))	&& (nextx>=(L2CENTREX-1.07f)))																// Collision Detection for centre of L&R blocks
						check = 2;
					else 
						if(	(nextx<=(_middlebottomC+0.07f))	&& (nextx>=(_middlebottomC-0.07f)))																// Collision Detection for centre of L&R blocks
							check = 3;
						else 
							if(	(nextx<=(_bottomC+0.07f))	&& (nextx>=(_bottomC-0.07f)))																// Collision Detection for centre of L&R blocks
								check = 14;
							else 
								if(	(nextx<=(_ceilingC+0.07f))	&& (nextx>=(_ceilingC-0.07f)))																// Collision Detection for centre of L&R blocks
									check = 14;
								else 
									if(	(nextx<=(_floorC+0.07f))	&& (nextx>=(_floorC-0.07f)))																// Collision Detection for centre of L&R blocks
										check = 15;
		}
		
		if(nexty >= 0.15 && nexty <= 0.25)																								// Conditions for Left Wall Collision
		{
			if( nextx<=(_topC+0.07) && nextx>=(_topC-0.07) )
				check=7;
			//cout << check << " check = \n";
			else 
				if( nextx<=(_middletopC+0.07f) && nextx>=(_middletopC-0.07f) )
					check=8;
				else
					if(	(nextx<=(L2CENTREX+0.07f))	&& (nextx>=(L2CENTREX-0.07f)))															
						check = 9;
					else 
						if(	(nextx<=(_middlebottomC+1.07f))	&& (nextx>=(_middlebottomC-1.07f)))															
							check = 10;
						else 
							if(	(nextx<=(_bottomC+0.07f))	&& (nextx>=(_bottomC-0.07f)))																
								check = 11;
							else 
								if(	(nextx<=(_ceilingC+0.07f))	&& (nextx>=(_ceilingC-0.07f)))																// Collision Detection for centre of L&R blocks
									check = 14;
								else 
									if(	(nextx<=(_floorC+0.07f))	&& (nextx>=(_floorC-0.07f)))																// Collision Detection for centre of L&R blocks
										check = 13;
			
		}
		
//		cout << L2CENTREX << " L2CENTREX\n";
//		cout << nextx << " nextx\n";
	} 
	
	//cout << nextx << "nextx \n";
	
	
	if(nextx <= LeftB)																								// Conditions for Left Wall Collision
	{
		if( nexty<=(topL+0.07) && nexty>=(topL-0.07) )
			check=7;
		//cout << check << " check = \n";
		else 
			if( nexty<=(middletopL+0.07f) && nexty>=(middletopL-0.07f) )
				check=8;
			else
				if(	(nexty<=(_LEFT_TOTAL_MOVE+0.07f))	&& (nexty>=(_LEFT_TOTAL_MOVE-0.07f)))															
					check = 9;
				else 
					if(	(nexty<=(middlebottomL+0.07f))	&& (nexty>=(middlebottomL-0.07f)))															
						check = 11;
					else 
						if(	(nexty<=(BottomL+0.07f))	&& (nexty>=(BottomL-0.07f)))																
							check = 14;
						else 
							if(	(nexty<=(ceilingL+0.07f))	&& (nexty>=(ceilingL-0.07f)))																// Collision Detection for centre of L&R blocks
								check = 14;
							else 
								if(	(nexty<=(floorL+0.07f))	&& (nexty>=(floorL-0.07f)))																// Collision Detection for centre of L&R blocks
									check = 15;

	}
	

	   
	   
	
	if ( (check ==0) && (direction ==1) )																				// Results of Wall Collision
	{
								previousx = _BALL_X;
								previousy = _BALL_Y;
								_BALL_X -= speedx;
								_BALL_Y -= speedy;
							}
		else 
			if	( (check==0) && (direction ==0 ) )
				{
									previousx = _BALL_X;
									previousy = _BALL_Y;
									_BALL_X += speedx;
									_BALL_Y -= speedy;	
								}
			else 
				if ( (check ==1) && (direction ==1) )
					{
										previousx = _BALL_X;
										previousy = _BALL_Y;
										_BALL_X += speedx;
										_BALL_Y += speedy;
									}
				else 
					if	( (check==1) && (direction ==0 ) )
						{
											previousx = _BALL_X;
											previousy = _BALL_Y;
											_BALL_X -= speedx;
											_BALL_Y += speedy;	
										}


	if( check== 2)																										// Result of Right Stick Collision to ball vector
	{
		previousx = _BALL_X;																// Collision in centre means x position changes while y position is maintained
		previousy = _BALL_Y;
		_BALL_X -= speedx;
		_BALL_Y += changey;
	}
	if( check== 3)
	{
		previousx = _BALL_X;
		previousy = _BALL_Y;
		_BALL_X -= 0.1f;
		_BALL_Y -= 0.1f;
	}
	if(check==4)
	{
		previousx = _BALL_X;
		previousy = _BALL_Y;
		_BALL_X -= 0.2f;
		_BALL_Y += 0.1f;
	}
	if(check==5)
	{
		previousx = _BALL_X;
		previousy = _BALL_Y;
		_BALL_X -= 0.2f;
		_BALL_Y -= 0.1f;
	}
	if(check==6)
	{
		previousx = _BALL_X;
		previousy = _BALL_Y;
		_BALL_X -= 0.1f;
		_BALL_Y += 0.1f;
	}
	if(check==12)
	{
		previousx = _BALL_X;
		previousy = _BALL_Y;
		_BALL_X -= 0.1f;
		_BALL_Y += 0.2f;
	}
	if(check==13)
	{
		previousx = _BALL_X;
		previousy = _BALL_Y;
		_BALL_X -= 0.1f;
		_BALL_Y -= 0.2f;
	}
	
	
	if( check== 9)																										// Result of LEFT Stick Collision to ball vector
	{
		previousx = _BALL_X;																// Collision in centre means x position changes while y position is maintained
		previousy = _BALL_Y;
		_BALL_X += speedx;
		_BALL_Y += changey;
	}
	if( check== 8)
	{
		previousx = _BALL_X;
		previousy = _BALL_Y;
		_BALL_X += 0.1f;
		_BALL_Y += 0.1f;
	}
	if(check==7)
	{
		previousx = _BALL_X;
		previousy = _BALL_Y;
		_BALL_X += 0.2f;
		_BALL_Y += 0.1f;
	}
	if(check==10)
	{
		previousx = _BALL_X;
		previousy = _BALL_Y;
		_BALL_X += 0.2f;
		_BALL_Y -= 0.1f;
	}
	if(check==11)
	{
		previousx = _BALL_X;
		previousy = _BALL_Y;
		_BALL_X += 0.2f;
		_BALL_Y -= 0.1f;
	}
	if(check==14)
	{
		previousx = _BALL_X;
		previousy = _BALL_Y;
		_BALL_X += 0.1f;
		_BALL_Y += 0.2f;
	}
	if(check==15)
	{
		previousx = _BALL_X;
		previousy = _BALL_Y;
		_BALL_X += 0.1f;
		_BALL_Y -= 0.2f;
	}
	
	
	if(nextx <= (LeftB-0.2f)  )														// If ball goes past sticks, set score and reset game
	{
		scoreBOOLEAN=0;
		Rscore++;
		SCORE=1;
	}
	else 
		if (nextx >= (RightB+0.2f)) 
		{
			scoreBOOLEAN = 1;
			Lscore++;
			SCORE=1;
		}
	
	if( Rscore == 5 && ( level==1 && players == 1) )
	{
		cout << "+++++++++++++++++++ LEVEL 2 ++++++++++++++++++\n\n";
		level++;
		Rscore = 0;
		RESET = 1;
	} 
	if( Rscore == 5 && ( level==2 && players == 1) )
	{
		cout << "+++++++++++++++++++ LEVEL 3 ++++++++++++++++++\n\n";
		level++;
		RESET = 1;
		Rscore = 0;
	}
	if( Rscore == 5 && ( level==3 && players == 1) )
	{
		cout << "\n\n+++++++++++++++++++ !!!!FINAL LEVEL!!!! ++++++++++++++++++\n\n+++++++++++++++++++ LEVEL 3 ++++++++++++++++++\n\n";
		level++;
		RESET = 1;
		Rscore = 0;
	}
	if( Rscore == 5 && ( level==4 && players == 1) )
	{
		int i;
		for(i=0;i<2000;i++)
			cout << "/n/n WIN /n/n";
	}
//	else {
//		cout << "!!!!!!CONGRATULATIONS!!!!!!!!! YOU HAVE WON!";
//		level=0;
//	}


	if (RESET == 1 || Rscore == 5 || Lscore == 5 )								// Reset game manually or by scores
	{
		GAME_START = Rscore = Lscore = _BALL_X = _BALL_Y = RESET = 0;
		check = -2;
		cout << Lscore << ":" << Rscore << "\n";
		point();
	}
	

} 

	int BOOLEANUP = 0, BOOLEANDOWN;

//Controls Stick Movement
void stickMove(void)
{
//	cout << BOOLEAN_W << " 2nd W \n";
//	cout << _LEFT_MOVE_UP << "2nd LEFT MOVE UP\n";
	
	if (  BOOLEAN_W == 1)
		_LEFT_MOVE_UP=1.0f;
	if ( BOOLEAN_S == 1)
		_LEFT_MOVE_DOWN=1.0f;
	if ( BOOLEAN_O == 1)
		_RIGHT_MOVE_UP=1.0f;
	if ( BOOLEAN_L == 1)
		_RIGHT_MOVE_DOWN=1.0f;
	
	//First IF == Player 1 Mode: Computer Controlled
	if ( players!=1)
	{
	if( (_LEFT_MOVE_UP >= 0.50f) && (_LEFT_TOTAL_MOVE < _BARRIER_TOP))
		_LEFT_TOTAL_MOVE += 0.1f;
	if( ( _LEFT_MOVE_DOWN >= 0.50f) && (_LEFT_TOTAL_MOVE > _BARRIER_BOTTOM) )
			_LEFT_TOTAL_MOVE -= 0.1f;
		
	}

	
			
			
	if(players==1)
	{
		
		if(difficulty==hard && changex<0.0f)
		{
			if( _BALL_X<=-3.0f && (_LEFT_TOTAL_MOVE >= nexty ))		// If Ball near Computer Stick, Move computer stick to ball's next y position to hit ball back
			{
				_LEFT_TOTAL_MOVE -= 0.3f;
			}
			if( _BALL_X<=-3.0f && _LEFT_TOTAL_MOVE <= nexty )
				_LEFT_TOTAL_MOVE += 0.3f;
		} 
		//			if(difficulty==hard && _BALL_X>0.0f)
		//				_LEFT_TOTAL_MOVE=0.0f;
		
		if(difficulty==medium && changex<0.0f)
		{
			if( _BALL_X<=-3.0f && _LEFT_TOTAL_MOVE >= nexty )		// If Ball near Computer Stick, Move computer stick to ball's next y position to hit ball back
			{
				_LEFT_TOTAL_MOVE -= 0.2f;
			}
			if( _BALL_X<=-3.0f && _LEFT_TOTAL_MOVE <= nexty )
				_LEFT_TOTAL_MOVE += 0.2f;
		} 
		
		if(difficulty==easy && changex<0.0f)
		{
			if( _BALL_X<=-2.0f && _LEFT_TOTAL_MOVE <= nexty )		// If Ball near Computer Stick, Move computer stick to ball's next y position to hit ball back
				_LEFT_TOTAL_MOVE += 0.1f;
			if( _BALL_X<=-2.0f && _LEFT_TOTAL_MOVE >= _BALL_Y )
				_LEFT_TOTAL_MOVE -=  0.1f;
		} 
	}
		

			
		if(level==3 || level == 4)
		{	
			if(BOOLEANUP==0)
				CENTREY += 0.1f;
			if(BOOLEANUP==1)
				CENTREY -= 0.1f;
			if(CENTREY <= _BARRIER_TOP && CENTREY >= (_BARRIER_TOP - 0.1f))
				BOOLEANUP = 1;
			if(CENTREY >= _BARRIER_BOTTOM && CENTREY < (_BARRIER_BOTTOM + 0.1f))
				BOOLEANUP = 0;
		}
	
		if(level==2 || level == 4)
		{	
			if(BOOLEANDOWN==0)
				L2CENTREX += 0.1f;
			if(BOOLEANDOWN==1)
				L2CENTREX -= 0.1f;
			if(L2CENTREX <= RightB && L2CENTREX > (RightB - 1.0f))
				BOOLEANDOWN = 1;
			if(L2CENTREX >= LeftB && L2CENTREX < (LeftB + 1.0f))
				BOOLEANDOWN = 0;
		}
		 	
	
	
	//Manual Rstick move for 1 & 2 Players
	if( (_RIGHT_MOVE_UP >= 0.50f) && (_RIGHT_TOTAL_MOVE < _BARRIER_TOP))
		_RIGHT_TOTAL_MOVE += 0.1f;
		else 
			if( ( _RIGHT_MOVE_DOWN >= 0.50f) && (_RIGHT_TOTAL_MOVE > _BARRIER_BOTTOM) )
			_RIGHT_TOTAL_MOVE -= 0.1f;
}


// Updates Display
void update(int value) 
{
	glutKeyboardFunc(handleKeypress);	
	
	stickMove();
	
	moveBall();

	_LEFT_MOVE_UP = _LEFT_MOVE_DOWN = _RIGHT_MOVE_UP = _RIGHT_MOVE_DOWN = 0;
	glutPostRedisplay();
	glutTimerFunc(20, update, 0);
}

// Main Function
int main(int argc, char** argv) {
	//Initialize GLUT
	
	cout << "\n\n\nPRESS I FOR INSTRUCTIONS\n\n\n";
	printbuttons();
	cout << "--------- 1 Player & Easy ----------\n*****************SCORE (L:R)*****************\n\n";
//	glutSetIgnoreKeyRepeat( true );
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 300);
	
	//Create the window
	glutCreateWindow("Pong");
	
	
	
	initRendering();
	
	//Set handler functions
	glutDisplayFunc(drawScene);
	glutSpecialFunc(SpecialInput);
	glutSpecialUpFunc(SpecialInputUp);
	glutKeyboardFunc(handleKeypress);
	glutKeyboardUpFunc(keyup);
	glutReshapeFunc(handleResize);
	
	
	glutTimerFunc(20, update, 0); //Add a timer
	
	glutMainLoop();
	return 0;
}









