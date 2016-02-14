
#include "enemy.h"

#include <stdlib.h>
#include <GL/gl.h>

#include "bullets.h"
#include "game.h"
#include "particles.h"
#include "frand.h"
#include "bonus.h"

struct e {
	//pozice x, y, rychlost x, r, velikost nepritele (proti kolizim), cil kam ma letet (pro ai) x a y, cas do dalsiho vystrelu 
	float posx, posy, speedx, speedy, rad, targetx, targety, reload;
	//aktualni zivot, maximalni hp, level, type: 1-obycejny, 2-stitovy, 3-utocny
	int hp, maxhp, level, type; 
	struct e *next;
};

struct e *enemies;

//inicializacni funkce nepratel pri zacatku nove hry
void init_enemies() {
	enemies=NULL;
}

//funkce pro smazani vsech strel pri konci hry
void delete_enemies() {
	struct e *p;
	while (enemies) {
		p=enemies;
		enemies=enemies->next;
		free(p);
	}
}

//funkce vrati nahodny casovy interval potrebny k znovuvystreleni
float get_reload_time(int level, int type) { 
	//utocni strili 10x casteji
	return (type==3?0.1:1)*(FRAND*200)/(level+3);
}

//funkce pro pridavani nepratel do spojaku
void add_enemy(float posx, float posy, float speedx, float speedy, float targetx, float targety, float rad, int hp, int level, int type) {
	struct e *p;
	p=malloc(sizeof(struct e));
	if (!p) return;
	p->posx=posx;
	p->posy=posy;
	p->speedx=speedx;
	p->speedy=speedy;
	p->targetx=targetx;
	p->targety=targety;
	p->reload=get_reload_time(level, type);
	p->rad=rad;
	p->hp=hp;
	p->maxhp=hp;
	p->level=level;
	p->type=type;
	p->next=enemies;
	enemies=p;
}

//funkce zajisti explozi pri sestreleni nepritele
void make_explosion(float posx, float posy) { 
	int i;
	//pridavani particlu do spojaku v particles.c
	for (i=0;i<60;i++)
		add_particle(posx, posy, 50*DFRAND, 50*DFRAND, FRAND, 1, FRAND, 0.1, 1);
	for (i=0;i<10;i++)
		add_particle(posx, posy, 150*DFRAND, 150*DFRAND, FRAND, 1, FRAND, 0.5, 2);
	for (i=0;i<15;i++)
		add_particle(posx+10*DFRAND, posy+10*DFRAND, 10*DFRAND, 10*DFRAND, 3*FRAND, 0.5, 0.5, 0.5, 3);
}

//funkce volana z bullets.c, 
int try_to_damage_enemy(float x, float y, int dmg) {
	struct e **p, *r;
	for (p=&enemies;*p;p=&((**p).next)) {
		//hledani cile pro strelu
		if (((**p).posx+(**p).rad >= x) && ((**p).posx-(**p).rad <= x) && ((**p).posy+(**p).rad >= y) && ((**p).posy-(**p).rad <= y)) {
			(**p).hp-=dmg;

			if ((**p).hp<=0) {				
				//nahodny vznik bonusu
				if (!(rand()%30))
					add_bonus((**p).posx, (**p).posy, 0, -50, rand()%4);
				
				//pridavani score (funkce z game.c)
				add_score((**p).level);
				
				//nepritel vybuchne
				make_explosion((**p).posx, (**p).posy);
				
				//mazani padlych
				r=*p;
				*p=(**p).next;
				free(r);
			}
			//zasah! vraceni 1 pro smazani strely (do bullets.c)
			return 1;
		}
	}
	//nepritel nezasazen
	return 0;
}

//'inteligence' nepratel
void enemy_ai (float time, struct e *i) {
	i->reload-=time;

	//vznik strely jen po urcitem casovem intervalu
	if (i->reload<0) {
		add_bullet(i->posx, i->posy, 0, -100, i->level, 0, 2);
		i->reload=get_reload_time(i->level, i->type);
	}
	
	//pohyb obycejnych jednotek
	if (i->type==1) {
		i->speedx=i->targetx-i->posx;
		i->speedy=i->targety-i->posy;
	}
	
	//pohyb stitovych jednotek
	if (i->type==2) {
		//omezeni hranic pohybu
		if (i->posx>240) {
			i->speedx=0;
			i->posx=240;
		}
		if (i->posx<-240) {
			i->speedx=0;
			i->posx=-240;
		}
		i->speedy=i->targety-i->posy;
		
		//rozkomihani pohybu
		i->speedx+=DFRAND*time*200;
	}

	//pohyb utocnych jednotek
	if (i->type==3) {
		//omezeni hranic pohybu
		if (i->posx>240) {
			i->speedx=0;
			i->posx=240;
		}
		if (i->posx<-240) {
			i->speedx=0;
			i->posx=-240;
		}
		if (i->posy>350) {
			if (i->speedy>0)
				i->speedy=0;
			//i->posy=350;
		}
		if (i->posy<0) {
			i->speedy=0;
			i->posy=0;
		}

		//rozkomihani pohybu
		i->speedx+=DFRAND*time*1000;
		i->speedy+=DFRAND*time*1000;
	}
}

//posun nepratel o casovy tik
void move_enemies(float time) {
	struct e* i, ** p;
	int delete;
	p=&enemies;
	while (*p) {
		i=*p;
		delete=0;
		
		//zmena polohy nepritele
		i->posx+=i->speedx*time;
		i->posy+=i->speedy*time;
		
		//a pridani dalsich zavislosi pohybu
		enemy_ai(time, i);
		
		//uspora pameti, kdyz nepritel opusti navzdy pole
		if ((i->posx < -300) || (i->posx > 300) || (i->posy < -400) || (i->posy > 400)) 
			delete=1;
		
		//mazani nepratel ze spojaku
		if (delete) {
			*p=i->next; //(**p).next;
			free(i);
		} else p=&((**p).next);
	}
}

//funkce pro kresleni ruznych typu nepratel
void draw_enemies() {
	struct e* i;
	float t;
	for(i=enemies;i;i=i->next) {
		t=i->hp/(float)(i->maxhp);
		glPushMatrix();
		glTranslatef(i->posx,i->posy,0);
		glBegin(GL_TRIANGLES);
			//nepratele tmavnou kdyz ztraci hp
			glColor3f(0.5+t*0.5,0.3*(1-t),0.3*(1-t));
		
			//zakadni tvar nepritele - cerveny trojuhelnik
			glVertex2f(-10, 0);
			glVertex2f(0, -20);
			glVertex2f(10, 0);

		//rychla jednotka ma navic cerny trojuhelnik
		if (i->type==3) { 
			glColor3f(0, 0, 0);
			glVertex2f(-6, 0);
			glVertex2f(0, -16);
			glVertex2f(6, 0);
		}
		glEnd();

		//stitova jednotka ma kolem sebe navic modry trojuhelnik
		if (i->type==2) { 
			glBegin(GL_LINE_LOOP);
			glColor3f(0.5*t, 0.5*t, 1*t);
			glVertex2f(-14, 3);
			glVertex2f(0, -24);
			glVertex2f(14, 3);
			glEnd();
		}
		glPopMatrix();
	}
}

//funkce volana z main.c pro nagenerovani nove vlny nepratel
int out_of_enemies() {
	return (!enemies);
}

