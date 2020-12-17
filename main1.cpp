#include<windows.h>
#include "OPENGL lib/include/GL/glut.h"


#include <stdlib.h>
#include <stdio.h>
#include <iostream>


//Game Speed
int FPS = 50;
//Game Track
int start = 0;


//For  main car
int indx = 0;


int roadDivTopMost = 0;
int roadDivTop = 0;
int roadDivMdl = 0;
int roadDivBtm = 0;

//Cars Coming
int car1 = 0;
int lrIndex1 = 0;
int car2 = +35;
int lrIndex2 = 0;
int car3 = +70;
int lrIndex3 = 0;
int lrIndex = 0;

const int font= (int)GLUT_BITMAP_TIMES_ROMAN_24;

void renderBitmapString(float x, float y, void* font, const char* string) {
	const char* c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void startGame() {
	//Road
	glColor3f(0.412, 0.412, 0.412);
	glBegin(GL_POLYGON);
	glVertex2f(20, 0);
	glVertex2f(20, 100);
	glVertex2f(80, 100);
	glVertex2f(80, 0);
	glEnd();

	//MAIN car
		//Front Tire
	glColor3f(0.000, 0.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(indx + 26 - 2, 5);
	glVertex2f(indx + 26 - 2, 7);
	glVertex2f(indx + 30 + 2, 7);
	glVertex2f(indx + 30 + 2, 5);
	glEnd();
	//Back Tire
	glColor3f(0.000, 0.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(indx + 26 - 2, 1);
	glVertex2f(indx + 26 - 2, 3);
	glVertex2f(indx + 30 + 2, 3);
	glVertex2f(indx + 30 + 2, 1);
	glEnd();
	//Car Body
	glColor3f(0.678, 1.000, 0.184);
	glBegin(GL_POLYGON);
	glVertex2f(indx + 26, 1);
	glVertex2f(indx + 26, 8);
	glColor3f(0.000, 0.545, 0.545);

	glVertex2f(indx + 28, 10);
	glVertex2f(indx + 30, 8);
	glVertex2f(indx + 30, 1);
	glEnd();

	//Opposite car 2
	glColor3f(0.000, 0.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex2 + 26 - 2, car2 + 100 - 4);
	glVertex2f(lrIndex2 + 26 - 2, car2 + 100 - 6);
	glVertex2f(lrIndex2 + 30 + 2, car2 + 100 - 6);
	glVertex2f(lrIndex2 + 30 + 2, car2 + 100 - 4);
	glEnd();
	glColor3f(0.000, 0.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex2 + 26 - 2, car2 + 100);
	glVertex2f(lrIndex2 + 26 - 2, car2 + 100 - 2);
	glVertex2f(lrIndex2 + 30 + 2, car2 + 100 - 2);
	glVertex2f(lrIndex2 + 30 + 2, car2 + 100);
	glEnd();
	glColor3f(0.294, 0.000, 0.510);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex2 + 26, car2 + 100);
	glVertex2f(lrIndex2 + 26, car2 + 100 - 7);
	glVertex2f(lrIndex2 + 28, car2 + 100 - 9);
	glVertex2f(lrIndex2 + 30, car2 + 100 - 7);
	glVertex2f(lrIndex2 + 30, car2 + 100);
	glEnd();
	car2--;
	if (car2 < -100) {
		car2 = 0;
		lrIndex2 = lrIndex;
	}
	



	//Opposite car 3
	glColor3f(0.000, 0.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex3 + 26 - 2, car3 + 100 - 4);
	glVertex2f(lrIndex3 + 26 - 2, car3 + 100 - 6);
	glVertex2f(lrIndex3 + 30 + 2, car3 + 100 - 6);
	glVertex2f(lrIndex3 + 30 + 2, car3 + 100 - 4);
	glEnd();
	glColor3f(0.000, 0.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex3 + 26 - 2, car3 + 100);
	glVertex2f(lrIndex3 + 26 - 2, car3 + 100 - 2);
	glVertex2f(lrIndex3 + 30 + 2, car3 + 100 - 2);
	glVertex2f(lrIndex3 + 30 + 2, car3 + 100);
	glEnd();
	glColor3f(1.000, 0.271, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex3 + 26, car3 + 100);
	glVertex2f(lrIndex3 + 26, car3 + 100 - 7);
	glVertex2f(lrIndex3 + 28, car3 + 100 - 9);
	glVertex2f(lrIndex3 + 30, car3 + 100 - 7);
	glVertex2f(lrIndex3 + 30, car3 + 100);
	glEnd();
	car3--;
	if (car3 < -100) {
		car3 = 0;
		lrIndex3 = lrIndex;
	}
}
void fristDesign() {


	//Road Design 
	glColor3f(00, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(32 - 2 + 21, 55);
	glVertex2f(32 + 58, 50 - 50);
	glVertex2f(32 - 22, 50 - 50);
	glEnd();
	//Road Midle
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(32 - 2 + 21, 55);
	glVertex2f(50 + 2, 50 - 50);
	glVertex2f(50 - 2, 50 - 50);
	glEnd();


	//Menu Place Holder
	glColor3f(0.098, 0.098, 0.439);
	glBegin(GL_POLYGON);
	glVertex2f(32 - 4, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 - 15 + 10);
	glVertex2f(32 - 4, 50 - 15 + 10);
	glEnd();

	glColor3f(00, 0, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(32 - 4, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 + 4 + 10);
	glVertex2f(32 - 4, 50 + 4 + 10);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(32 + 45, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 + 5 + 10);
	glVertex2f(32 + 46, 50 - 15 + 10);
	glVertex2f(32 + 45, 50 - 15 + 10);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(32 - 4, 50 - 14 + 10);
	glVertex2f(32 + 46, 50 - 14 + 10);
	glVertex2f(32 + 46, 50 - 15 + 10);
	glVertex2f(32 - 4, 50 - 15 + 10);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(32 - 4, 50 + 5 + 10);
	glVertex2f(32 - 5, 50 + 5 + 10);
	glVertex2f(32 - 5, 50 - 15 + 10);
	glVertex2f(32 - 4, 50 - 15 + 10);
	glEnd();



	renderBitmapString(30, 80, (void*)font, "2D Car Racing Game ");

	glColor3f(0.000, 1.000, 0.000);
	renderBitmapString(30, 50 + 10, (void*)font, "Press SPACE to START");
	renderBitmapString(30, 50 - 3 + 10, (void*)font, "Press ESC to Exit");

	glColor3f(1.000, 1.000, 1.000);
	renderBitmapString(30, 50 - 10 + 10, (void*)font, "Press RIGHT to turn Right");
	renderBitmapString(30, 50 - 12 + 10, (void*)font, "Press LEFT to turn Left");




}
void spe_key(int key, int x, int y) {
	switch (key) {


	case GLUT_KEY_LEFT:
		if (lrIndex >= 0) {
			lrIndex = lrIndex - (FPS / 10);
			if (lrIndex < 0) {
				lrIndex = -1;
			}
		}
		break;


	case GLUT_KEY_RIGHT:
		if (lrIndex <= 44) {
			lrIndex = lrIndex + (FPS / 10);
			if (lrIndex > 44) {
				lrIndex = 45;
			}
		}
		break;

	default:
		break;
	}

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	if (start == 1) {
		glClearColor(0.000, 0.392, 0.000, 1);
		startGame();
	}

	else {
		fristDesign();
		}

	glFlush();
	glutSwapBuffers();
	
}


	int main(int argc, char* argv[])
	{


		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
		glutInitWindowSize(500, 650);
		glutInitWindowPosition(200, 20);
		glutCreateWindow("Car Game");

		glutDisplayFunc(display);
		glutSpecialFunc(spe_key);

		glutMainLoop();

		return 0;
	}

	