
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>

#include "game.h"

char up=0, down=0, left=0, right=0, space=0;
int lasttime=0;

//inicializace nemenneho pozadi
void init() {
	init_game();

	//smesovani barev
	glEnable(GL_SMOOTH); 
	
	glClearColor(0, 0, 0, 0);

	//nastaveni presnosti vypoctu (realne)
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 
}

//funkce zjisti cas od posledniho zavolani (snimku)
float get_time_diff() {
	int newtime;
	float diff;

	//cas v ms od minuleho snimku
	newtime=glutGet(GLUT_ELAPSED_TIME);

	//rozdil casu + prevod na sekundy
	diff=(newtime-lasttime)*0.001;
	
	lasttime=newtime;

	//pro preteceni
	if (diff<=0) diff=0.000001;
	
	//zpomaleni hry pri malem fps
	if (diff>0.1) diff=0.1;
	
	return diff;
}

//deinicializace pri konci hry
void deinitialize() {
	finish_game();
}

//periodicke prekreslovani sceny
void display(int _data) { 
	float time;
	time=get_time_diff();
	
	//posun o casovy usek a predani vstupu z klavesnice
	update_game(time, up, down, right, left, space);

	//vycisteni snimku
	glClear(GL_COLOR_BUFFER_BIT); 
	
	//reset na souradnice 0, 0, 0
	glLoadIdentity();

	draw_game();	
	
	//z double bufferingu, prehozeni snimku
	glutSwapBuffers();
	glutTimerFunc(10,display,0);
}

void reshape(int s, int v) {
	//fyzicka plocha, kde kreslim
	glViewport(0,0,s,v); 
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//prakticky urcuji 'rozliseni hry'
	glOrtho(-250,250,-350,350,-1,1);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard_down(unsigned char key, int x, int y) {
	switch (key) {
		//kdyz Esc > konec hry
		case 27: glutLeaveMainLoop(); break;
		case ' ': space=1; break;
		default: break;
	}
}

void keyboard_up(unsigned char key, int x, int y) {
	switch (key) {
		case ' ': space=0; break;
		default: break;
	}
}

void special_keys_down(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT: left=1; break; 
		case GLUT_KEY_RIGHT: right=1; break;
		case GLUT_KEY_UP: up=1; break;
		case GLUT_KEY_DOWN: down=1; break;
		default: break;
	}
}

void special_keys_up(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT: left=0; break; 
		case GLUT_KEY_RIGHT: right=0; break;
		case GLUT_KEY_UP: up=0; break;
		case GLUT_KEY_DOWN: down=0; break;
		default: break;
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	init();

	//double buffering
	glutInitDisplayMode(GLUT_DOUBLE);
	
	glutInitWindowSize(500, 700);
	glutCreateWindow("Raketka by noox");
	
	//callbacky
	glutReshapeFunc(reshape);
	
	//zachyceni vstupu z klavesnice
	glutKeyboardFunc(keyboard_down);
	glutKeyboardUpFunc(keyboard_up);

	//zachyceni vstupu z klavesnice - na netisknutelne znaky
	glutSpecialFunc(special_keys_down);
	glutSpecialUpFunc(special_keys_up);

	//za 0 ms, prekreslovani
	glutTimerFunc(0,display,0);
	
	//zahajeni hlavniho cyklu
	glutMainLoop();

	deinitialize();
	return 0;
}

