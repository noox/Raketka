
#include "bullets.h"

#include <GL/gl.h>
#include <stdlib.h>

#include "enemy.h"
#include "game.h"

struct s {
	//pozice x, y, rychlost x, y
	float x, y, sx, sy;
	//sila strely, pratelskost (bool), vizual strely;
	int dmg, from, type;
	struct s* next;
};

struct s* bullets;

//inicializacni funkce strel pri zacatku nove hry
void init_bullets() {
	bullets=NULL;
}

//funkce pro smazani vsech strel pri konci hry
void delete_bullets() {
	struct s* p;
	while (bullets) {
		p=bullets;
		bullets=bullets->next;
		free(p);
	}
}

//funkce pro pridavani strel do spojaku
void add_bullet(float x, float y, float sx, float sy, int dmg, int from, int type) {
	struct s* p;
	p=malloc(sizeof(struct s));
	if (!p) return;
	p->x=x;
	p->y=y;
	p->sx=sx;
	p->sy=sy;
	p->dmg=dmg;
	p->from=from;
	p->type=type;
	p->next=bullets;
	bullets=p;
}

//posun strel o casovy tik
void move_bullets(float time) {
	struct s* i, ** p;
	int delete;
	p=&bullets;
	while (*p) {
		i=*p;
		delete=0;
		
		//zmena polohy strely
		i->x+=i->sx*time;
		i->y+=i->sy*time;
		
		//pri zasahu nepritele bude strela smazana (pta se funkce z enemy.c)
		if (i->from && try_to_damage_enemy(i->x, i->y, i->dmg)) delete=1; 
		
		//pri zasahu hrace bude strela smazana (pta se funkce z game.c)
		if ((!i->from) && try_to_damage_player(i->x, i->y, i->dmg)) delete=1; 
		
		//uspora pameti, pokud strely opusti navzdy pole
		if ((i->x < -300) || (i->x > 300) || (i->y < -400) || (i->y > 400)) 
			delete=1;

		//mazani strel ze spojaku
		if (delete) {
			*p=i->next; //(**p).next;
			free(i);
		} else p=&((**p).next);
	}	
}

//funkce pro kresleni ruznych strel
void draw_bullets() {
	struct s* i;
	for(i=bullets;i;i=i->next) {
		glPushMatrix();
		glTranslatef(i->x,i->y-20,0);
		switch (i->type) {
			case 1:
				//strely z raketky
				glBegin(GL_TRIANGLES);
				glColor3f(0, 1, 1);
				glVertex2f(5, 0);
				glVertex2f(0, 10);
				glVertex2f(-5, 0);
				glEnd();
				break;
			case 2:
				//strely nepratel
				glBegin(GL_TRIANGLES);
				glColor3f(1, 0.5, 0);
				glVertex2f(0, 0);
				glVertex2f(2.5, 10);
				glVertex2f(-2.5, 10);
				glEnd();
				break;
			default: break;
		}
		glPopMatrix();
	}
}

