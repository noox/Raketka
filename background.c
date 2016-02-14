
#include "background.h"

#include <GL/gl.h>
#include <stdlib.h>

#include "frand.h"

//pocet hvezd v pozadi
#define SC 1000

struct star {
	//pozice x, y, 'rychlost'
	float x, y, speed;
};

struct star sf[SC];

//funkce pro rozhozeni hvezd na zacatku
void init_stars() { 
	int i;
	for(i=0;i<SC;i++) {
		//nahodna pozice hvezdy na zacatku
		sf[i].x=DFRAND*250;
		sf[i].y=DFRAND*350;

		//0.1 = vsechny se pohybuji + random pridana rychlost
		sf[i].speed=0.1+FRAND*0.9;

		//vice hvezd v 'pozadi', malo v 'popredi'
		sf[i].speed*=sf[i].speed;
	}
}

//funkce pro prekreslovani pozadi
void draw_stars() {
	int i;
	glBegin(GL_LINES);
	for(i=0;i<SC;i++) {
		//cim jsou hvezdy rychlejsi, tim jsou belejsi
		glColor3f(sf[i].speed*0.4, sf[i].speed*0.4, sf[i].speed*0.4); 			
		//nakresleni delky cary v zavislosi na rychlosti
		glVertex2f(sf[i].x, sf[i].y);
		glVertex2f(sf[i].x, sf[i].y-sf[i].speed*30);
	}
	glEnd();
}

//posun hvezd o casovy tik
void move_stars(float time) {
	int i;
	for(i=0;i<SC;i++) {
		//pozicni posun o zmensenou rychlost za cas
		sf[i].y-=sf[i].speed*time*300; 		
		
		//pokud hvezda dosahne konce hraciho pole
		if (sf[i].y<-350) {
			//presune se zpet nahoru
			sf[i].y=350;
			
			//nova horizontalni pozice
			sf[i].x=DFRAND*250;
			
			//nova rychlost
			sf[i].speed=0.1+FRAND*0.9; 
			
			sf[i].speed*=sf[i].speed;
		}
	}
}

