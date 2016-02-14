
#include "bonus.h"

#include <GL/gl.h>
#include <stdlib.h>

#include "game.h"

struct b {
	//pozice x, y, rychlost x, y
	float x, y, sx, sy;
	//typ bonusu
	int type;
	struct b* next;
};

struct b* bonuses;

//inicializacni funkce bonusu pri zacatku nove hry
void init_bonuses() {
	bonuses=NULL;
}

//funkce pro smazani vsech bonusu pri konci hry
void delete_bonuses() {
	struct b* p;
	while (bonuses) {
		p=bonuses;
		bonuses=bonuses->next;
		free(p);
	}
}

//funkce pro pridavani bonusu do spojaku
void add_bonus(float x, float y, float sx, float sy, int type) {
	struct b* p;
	p=malloc(sizeof(struct b));
	if (!p) return;
	p->x=x;
	p->y=y;
	p->sx=sx;
	p->sy=sy;
	p->type=type;
	p->next=bonuses;
	bonuses=p;
}

//posun bonusu o casovy tik
void move_bonuses(float time) {
	struct b* i, ** p;
	int delete;
	p=&bonuses;
	while (*p) {
		i=*p;
		delete=0;
		
		//zmena polohy bonusu
		i->x+=i->sx*time;
		i->y+=i->sy*time;

		//pri lapeni hracem bude bonus smazan (pta se funkce z game.c)
		if (player_bonuses(i->x, i->y, i->type)) delete=1;
		
		//uspora pameti, pokud bonus opusti navzdy pole
		if ((i->x < -300) || (i->x > 300) || (i->y < -400) || (i->y > 400)) 			delete=1;

		//smazani bonusu ze spojaku
		if (delete) {
			*p=i->next; //(**p).next;
			free(i);
		} else p=&((**p).next);
	}	
}

//funkce pro kresleni ruznych bonusu
void draw_bonuses() {
	struct b* i;
	for(i=bonuses;i;i=i->next) {
		glPushMatrix();
		glTranslatef(i->x,i->y,0);
		switch (i->type) {
			case 0: 
				//modrofialova pro docasny stit
				glColor3f(0.5, 0.5, 1);
				break;
			case 1:
				//zluta pro 1 power-up
				glColor3f(1, 1, 0);
				break;
			case 2:
				//bila pro bonusove skore
				glColor3f(1, 1, 1);
				break;
			case 3: 
				//svetla zelena pro delo
				glColor3f(0.5, 1, 0);
				break;
			default: break;
		}
		//kresleni samotneho ctverce bonusu
		glBegin(GL_QUADS);
		glVertex2f(-5, -5);
		glVertex2f(5, -5);
		glVertex2f(5, 5);
		glVertex2f(-5, 5);
		glEnd();
		glPopMatrix();
	}
}

