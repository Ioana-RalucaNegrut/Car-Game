
#include<windows.h>


#include <GL/freeglut.h>


#include <cmath>
#include <cstdlib>
#include <GL/glut.h>
#include <cstdio>



#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>



#include "Serial.h"
#include <string.h>

//viteza cu care se deplaseaza masinile
int FPS = 20;
//inceput joc
int start = 0;
int gv = 0;


//miscare traseu
int roadDivTopMost = 0;
int roadDivTop = 0;
int roadDivMdl = 0;
int roadDivBtm = 0;

//index verificare stanga/dreapta
int lrIndex = 0;

//masina adversa
int car1 = 0;
int lrIndex1 = 0;
int car2 = +35;
int lrIndex2 = 0;
int car3 = +70;
int lrIndex3 = 0;

//afisare text
const int font1 = (int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2 = (int)GLUT_BITMAP_HELVETICA_18;
const int font3 = (int)GLUT_BITMAP_8_BY_13;



using namespace std;

const char* portName = "COM4";
#define MAX_DATA_LENGTH 255
char incomingData[MAX_DATA_LENGTH];
SerialPort* arduino;
int x,y = 0;
int value;


void renderBitmapString(float x, float y, void* font, const char* string) {
	const char* c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}



void startGame() {
	//Drum
	glColor3f(0.412, 0.412, 0.412);
	glBegin(GL_POLYGON);
	glVertex2f(20, 0);
	glVertex2f(20, 100);
	glVertex2f(80, 100);
	glVertex2f(80, 0);
	glEnd();

	//bordura din stanga a drumului
	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(20, 0);
	glVertex2f(20, 100);
	glVertex2f(23, 100);
	glVertex2f(23, 0);
	glEnd();

	//bordura din dreapta a drumului
	glColor3f(1.000, 1.000, 1.000);
	glBegin(GL_POLYGON);
	glVertex2f(77, 0);
	glVertex2f(77, 100);
	glVertex2f(80, 100);
	glVertex2f(80, 0);
	glEnd();

	//bordura  din mijloc drum
	  //sus
	glColor3f(1.000, 1.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(48, roadDivTop + 80);
	glVertex2f(48, roadDivTop + 100);
	glVertex2f(52, roadDivTop + 100);
	glVertex2f(52, roadDivTop + 80);
	glEnd();
	roadDivTop--;
	if (roadDivTop < -100) {
		roadDivTop = 20;

	}
	//mijloc
	glColor3f(1.000, 1.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(48, roadDivMdl + 40);
	glVertex2f(48, roadDivMdl + 60);
	glVertex2f(52, roadDivMdl + 60);
	glVertex2f(52, roadDivMdl + 40);
	glEnd();


	roadDivMdl--;
	if (roadDivMdl < -60) {
		roadDivMdl = 60;

	}
	//jos
	glColor3f(1.000, 1.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(48, roadDivBtm + 0);
	glVertex2f(48, roadDivBtm + 20);
	glVertex2f(52, roadDivBtm + 20);
	glVertex2f(52, roadDivBtm + 0);
	glEnd();
	roadDivBtm--;
	if (roadDivBtm < -20) {
		roadDivBtm = 100;

	}

	//masina principala
	glBegin(GL_POINTS);
	//roti din fata
	glColor3f(0.000, 0.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex + 26 - 2, 5);
	glVertex2f(lrIndex + 26 - 2, 7);
	glVertex2f(lrIndex + 30 + 2, 7);
	glVertex2f(lrIndex + 30 + 2, 5);
	glEnd();
	//roti din spate 
	glColor3f(0.000, 0.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex + 26 - 2, 1);
	glVertex2f(lrIndex + 26 - 2, 3);
	glVertex2f(lrIndex + 30 + 2, 3);
	glVertex2f(lrIndex + 30 + 2, 1);
	glEnd();
	//corpul masinii
	glColor3f(0.678, 1.000, 0.184);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex + 26, 1);
	glVertex2f(lrIndex + 26, 8);
	glColor3f(0.000, 0.545, 0.545);

	glVertex2f(lrIndex + 28, 10);
	glVertex2f(lrIndex + 30, 8);
	glVertex2f(lrIndex + 30, 1);
	glEnd();

	//masina adversa 1
	glColor3f(0.000, 0.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex1 + 26 - 2, car1 + 100 - 4);
	glVertex2f(lrIndex1 + 26 - 2, car1 + 100 - 6);
	glVertex2f(lrIndex1 + 30 + 2, car1 + 100 - 6);
	glVertex2f(lrIndex1 + 30 + 2, car1 + 100 - 4);
	glEnd();
	glColor3f(0.000, 0.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex1 + 26 - 2, car1 + 100);
	glVertex2f(lrIndex1 + 26 - 2, car1 + 100 - 2);
	glVertex2f(lrIndex1 + 30 + 2, car1 + 100 - 2);
	glVertex2f(lrIndex1 + 30 + 2, car1 + 100);
	glEnd();
	glColor3f(1.000, 0.000, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(lrIndex1 + 26, car1 + 100);
	glVertex2f(lrIndex1 + 26, car1 + 100 - 7);
	glVertex2f(lrIndex1 + 28, car1 + 100 - 9);
	glVertex2f(lrIndex1 + 30, car1 + 100 - 7);
	glVertex2f(lrIndex1 + 30, car1 + 100);
	glEnd();
	//verificare ciocnire masina1
	car1--;
	if (car1 < -100) {
		car1 = 0;
		lrIndex1 = lrIndex;
	}
	
	
	

	//masina adversa2
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
	//verificare ciocnire cu masina2
	car2--;
	if (car2 < -100) {
		car2 = 0;
		lrIndex2 = lrIndex;
	}
	
	


	//masina adversa3
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
	//verificare ciocnire cu masina3
	car3--;
	if (car3 < -100) {
		car3 = 0;
		lrIndex3 = lrIndex;
	}
	
	
	


}

void firstDesign() {

	//background
	glColor3f(0.000, 0.392, 0.000);
	glBegin(GL_POLYGON);
	glVertex2f(0, 55);
	glVertex2f(100, 55);
	glColor3f(0.604, 0.804, 0.196);
	glVertex2f(100, 50 - 50);
	glVertex2f(0, 50 - 50);
	glEnd();



	//design drum prima pagina
	glColor3f(00, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(32 - 2 + 21, 55);
	glVertex2f(32 + 58, 50 - 50);
	glVertex2f(32 - 22, 50 - 50);
	glEnd();
	//drum mijloc
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(32 - 2 + 21, 55);
	glVertex2f(50 + 2, 50 - 50);
	glVertex2f(50 - 2, 50 - 50);
	glEnd();


	//meniu pagina principala
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



	//Informatie prima pagina
	if (gv == 1) {
		glColor3f(1.000, 0.000, 0.000);
		renderBitmapString(35, 60 + 10, (void*)font1, "GAME OVER");

	}


	glColor3f(0.000, 1.000, 0.000);
	renderBitmapString(30, 50 + 10, (void*)font2, "Press SPACE to START");
	renderBitmapString(30, 50 - 3 + 10, (void*)font2, "Press ESC to EXIT");

	glColor3f(1.000, 1.000, 1.000);
	renderBitmapString(30, 50 - 10 + 10, (void*)font3, "Slide RIGHT to turn Right");
	renderBitmapString(30, 50 - 12 + 10, (void*)font3, "Slide LEFT to turn Left");


	glColor3f(0.000, 1.000, 1.000);



}

void display() {
	
		glClear(GL_COLOR_BUFFER_BIT);

		if (start == 1) {
			glClearColor(0.627, 0.322, 0.176, 1);

			glClearColor(0.000, 0.392, 0.000, 1);
			startGame();
		}

		else {
			firstDesign();
			glClearColor(0.184, 0.310, 0.310, 1);

		}
		

		glFlush();
		glutSwapBuffers();
	
}



void spe_key(int key) {

	switch (key) {

	case GLUT_KEY_LEFT://1
		if (lrIndex >= 0) {
			
			lrIndex = lrIndex - (FPS / 10);
			if (lrIndex < 0) {
				lrIndex = -1;
			}
		}
		break;


	case GLUT_KEY_RIGHT://2
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

void processKeys(unsigned char key, int x, int y) {

	switch (key)
	{
	case ' '://initializare inceputul jocului
		if (start == 0) {
			start = 1;
			gv = 0;
			FPS = 20;
			roadDivTopMost = 0;
			roadDivTop = 0;
			roadDivMdl = 0;
			roadDivBtm = 0;
			lrIndex = 0;
			car1 = 0;
			lrIndex1 = 0;
			car2 = +35;
			lrIndex2 = 0;
			car3 = +70;
			lrIndex3 = 0;


		}
		break;

	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer, 0);
}

void exampleReceiveData(void)
{
	int ref = 100;


	int readResult = arduino->readSerialPort(incomingData, MAX_DATA_LENGTH);
	printf("%s", incomingData);
		//transformarea datelor primite de la arduino si transmise ca parametrii la functia care stabileste directia in care va merge masina (dupa o valoarea de referinta se va stabila directia:stanga/dreapta)
		if (sscanf_s(incomingData, "%d", &value) > 0) {
			

				if (value > ref)
				{
					//printf("%d", value);
					spe_key(0x0064);
					ref = value;

				}
				else {
					//printf("%d", value);
					spe_key(0x0066);
					ref = value;

				}
			

		
	}

	Sleep(10);
}



void autoConnect(void)
{
	while (1) {
		
		std::cout << "Searching in progress";
		// asteptare conexiune
		while (!arduino->isConnected()) {
			Sleep(100);
			std::cout << ".";
			arduino = new SerialPort(portName);//se creaza o instanta de SerialPort
		}

		//verificare daca arduino este conectat sau nu
		if (arduino->isConnected()) {//stabilirea conexiunii
			std::cout << std::endl << "Connection established at port " << portName << std::endl;
		}


		//afisare fereastra joc 
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
		glutInitWindowSize(500, 650);
		glutInitWindowPosition(200, 20);
		glutCreateWindow("Car Game");
		glutDisplayFunc(display);
	
		glutKeyboardFunc(processKeys);

		glOrtho(0, 100, 0, 100, -1, 1);
		glClearColor(0.184, 0.310, 0.310, 1);

		glutTimerFunc(1000, timer, 0);
		

		while (arduino->isConnected()) {
			exampleReceiveData();//functia care citeste datele transmise de la portul serial arduino
			glutMainLoop();//bucla pentru jocul in glut
		}
					
		

		

	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	
	autoConnect();//se face conexiunea la portul COM4

	

	return 0;
}

