
#include "particles.h"

#include <GL/gl.h>
#include <stdlib.h>

struct p {
	//pozice x, y, rychlost x, y, zivotnost, soucasne stari, barvy
	float x, y, sx, sy, life, age, red, green, blue;
	//typ particlu
	int type;
	struct p *next;
};

struct p *particles;

//inicializacni funkce particlu pri zacatku nove hry
void init_particles() {
	particles=NULL;
}

//funkce pro smazani vsech particlu pri konci hry
void delete_particles() {
	struct p *r;
	while (particles) {
		r=particles;
		particles=particles->next;
		free(r);
	}
}

//funkce pro pridavani particlu do spojaku
void add_particle(float x, float y, float sx, float sy, float life, float red, float green, float blue, int type) {
	struct p *r;
	r=malloc(sizeof(struct p));
	if (!r) return;
	r->x=x;
	r->y=y;
	r->sx=sx;
	r->sy=sy;
	r->life=life;
	r->age=0;
	r->red=red;
	r->green=green;
	r->blue=blue;
	r->type=type;
	r->next=particles;
	particles=r;
}

//posun particlu o casovy tik
void update_particles(float time) {
	struct p* i, ** r;
	int delete;
	r=&particles;
	while (*r) {
		i=*r;
		delete=0;
		
		//zmena polohy particlu
		i->x+=i->sx*time;
		i->y+=i->sy*time;
		
		//starnuti particlu
		i->age+=time;
		
		//kdyz uz jsou zobrazene moc dlouho
		if (i->age>=i->life) delete=1;

		//uspora pameti, pokud particly opusti navzdy pole
		if ((i->x < -300) || (i->x > 300) || (i->y < -400) || (i->y > 400))
			delete=1;
		
		//mazani nepratel ze spojaku
		if (delete) {
			*r=i->next; //(**r).next;
			free(i);
		} else r=&((**r).next);
	}	
}

//funkce pro kresleni ruznych typu particlu
void draw_particles() {
	struct p *r;
	glEnable(GL_BLEND);

	//aditivni smesovani barev
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	
	for (r=particles;r;r=r->next) 
		switch (r->type) {
			case 1:
				//dlouhy particle pro centralizovany efekt 'hvezdy'
				glBegin(GL_LINES);
				glColor4f(r->red, r->green, r->blue, 1-r->age/r->life);
				glVertex2f(r->x, r->y);
				glColor4f(0, 0, 0, 1);
				glVertex2f(r->x-1.1*r->sx, r->y-1.1*r->sy);
				glEnd();
				break;
			case 2:
				//kratky particle pro mene vyrazny rozstrik particlu do dalky
				glBegin(GL_LINES);
				glColor4f(r->red, r->green, r->blue, 1-r->age/r->life);
				glVertex2f(r->x, r->y);
				glColor4f(0, 0, 0, 1);
				glVertex2f(r->x-0.1*r->sx, r->y-0.1*r->sy);
				glEnd();
				break;
			case 3:
				//kulaty particle pro efekt koure
				glBegin(GL_TRIANGLE_FAN);
				glColor4f(r->red, r->green, r->blue, 1-r->age/r->life);
				glVertex2f(r->x, r->y);
				glColor4f(0, 0, 0, 1);
				glVertex2f(r->x+5, r->y);
				glVertex2f(r->x, r->y-5);
				glVertex2f(r->x-5, r->y);
				glVertex2f(r->x, r->y+5);
				glVertex2f(r->x+5, r->y);
				glEnd();
				break;
			default: break;
		}
	glDisable(GL_BLEND);
}

