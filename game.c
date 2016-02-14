
#include "game.h"

#include <GL/gl.h>
#include <math.h>

#include "background.h"
#include "enemy.h"
#include "bullets.h"
#include "frand.h"
#include "text.h"
#include "particles.h"
#include "bonus.h"
#include "enemywave.h"

//pozice hrace x, y, rychlost hrace x, y, cas do nabiti zbrane
float posx, posy, speedx, speedy, reload;
//cas do odkliknuti game over screenu, do konce stitu, do vyprseni dela
float deathtimer, shieldtimer, canontimer;
//level hry, power level hrace, hp hrace (prakticky nepouzivane), skore
int level, plevel, hp, score;
//booleovska hodnota toho, zda je potreba kreslit game over screen
int playerdead;

//inicializacni funkce pri zacatku hry
void init_game() {
	//pocatecni pozice, rychlost a hp raketky
	posx=0;
	posy=-300;
	speedx=speedy=0;
	hp=1;

	//hrac muze hned strilet
	reload=0;
	
	//promenne pro zachovani hlavnich statistik hry
	level=0;
	plevel=0;
	score=0;

	//na zacatku hrac zije
	playerdead=0; 
	
	//cas od smrti hrace nakonci
	deathtimer=0;
	
	//trvani bonusu
	shieldtimer=0;
	canontimer=0;
	
	init_stars();
	init_bullets();
	init_enemies();
	init_particles();
	init_bonuses();
}

//funkce pro deinicializaci vsech modulu
void finish_game() {
	delete_bullets();
	delete_enemies();
	delete_particles();
	delete_bonuses();
}

//funkce starajici se o leveling
void handle_levels() {
	//pokud dosli nepratele (funkce z enemy.c)
	if (out_of_enemies()) {
		level++;
		plevel++;
		
		//a nageneruje novou vlnu nepratel
		generate_enemy_wave(level);
	}
}	

//funkce pro kresleni 
void draw_game() {
	float t;
	
	draw_stars();
	draw_enemies();
	draw_bullets();
	draw_particles();
	draw_bonuses();
	
	//mod pro koncovy screen hry
	if (playerdead) { 
		//smesovani barev
		glEnable(GL_BLEND);
		
		//vyber blendovaci funkce
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
		
		//zesednuti pozadi
		glColor4f(0, 0, 0, 0.6);
		glBegin(GL_QUADS);
		glVertex2f(-250, -350);
		glVertex2f(250, -350);
		glVertex2f(250, 350);
		glVertex2f(-250, 350);
		glEnd();
		
		glDisable(GL_BLEND);
		
		//kresleni statistik hry na konci hry
		glPushMatrix();
		glTranslatef(-240, 0, 0);
		glScalef(18, 18, 0);
		glColor3f(0, 1, 0);
		glPushMatrix();
			glTranslatef(2, 5, 0);
			glScalef(4, 4, 0);
			draw_string("GAME OVER");
			glColor3f(1, 1, 1);
			glTranslatef(0.03, 0.03, 0);
			draw_string("GAME OVER");
		glPopMatrix();
		draw_string("LEVEL");
		glTranslatef(3.5, 0, 0);
		draw_int(level);
		glTranslatef(-3.5, -1, 0);
		draw_string("SCORE");
		glTranslatef(3.5, 0, 0);
		draw_int(score);
		glTranslatef(-3.5, -5, 0);
		glPushMatrix();
			glTranslatef(0.3, -4, 0);
			glScalef(2, 2, 0);
			glColor3f(0, 1, 0);
			draw_string("PRESS FIRE TO RESTART");
		glPopMatrix();
		glPopMatrix();
	}
	else {
		//statistika hry v levem spodnim rohu
		glPushMatrix(); 
		glTranslatef(-240, -305, 0);
		glScalef(18, 18, 1);
		glColor3f(0, 1, 0);
		draw_string("POWER");
		glTranslatef(3.5, 0, 0);
		draw_int(plevel);
		glTranslatef(-3.5, -1, 0);
		draw_string("LEVEL");
		glTranslatef(3.5, 0, 0);
		draw_int(level);
		glTranslatef(-3.5, -1, 0);
		draw_string("SCORE");
		glTranslatef(3.5, 0, 0);
		draw_int(score);
		glPopMatrix();

		glTranslatef(posx, posy, 0);
		
		//raketka
		glBegin(GL_TRIANGLES); 
		glColor3f(0, 0, 1);
		glVertex2f(-20, -10);
		glColor3f(0.5, 0.5, 1);
		glVertex2f(0, 0);
		glVertex2f(0, 50);

		glVertex2f(0, 50);
		glVertex2f(0, 0);
		glColor3f(0, 0, 1);
		glVertex2f(20, -10);

		glColor3f(1, 0, 0);
		glVertex2f(0, 0);
		glColor3f(1, 1, 0);
		glVertex2f(-2.5, -6);
		glVertex2f(2.5, -6);
		glEnd();
		
		//pokud hrac sebere stitovy bonus
		if (shieldtimer>0) {
			//poslednich 5 vterin stit blika
			if (shieldtimer<5) 
				t=sinf(shieldtimer*20); 
			else t=1;
			
			glColor3f(0.3*t*t, 0.3*t*t, 0.6*t*t);
			
			//nakresleni trojuhelnikoveho stitu
			glBegin(GL_LINE_LOOP);
			glVertex2f(0, 55);
			glVertex2f(-25, -15);
			glVertex2f(25, -15);
			glEnd();
		}
	}
}

//posun hry o casovy tik
void update_game(float time, int k_up, int k_down, int k_right, int k_left, int k_fire) {
	//pozadi pro koncovy screen hry
	if (playerdead) { 
		move_stars(time);
		move_enemies(time);
		move_bullets(time);
		update_particles(time);
		move_bonuses(time);

		deathtimer-=time;
		if ((deathtimer<=0) && k_fire) { 
			//zacatek nove hry
			finish_game();
			init_game();
		}
	}

	else {
		handle_levels();
		
		//odecteni casu od casovacu bonusu
		shieldtimer-=time;
		canontimer-=time;

		reload+=time;

		//ovladani raketky (funkce z main.c)
		if (k_left) speedx-=time*1300;
		if (k_right) speedx+=time*1300;
		if (k_up) speedy+=time*1300;
		if (k_down) speedy-=time*1300;

		//strelba mozna jen po specifickem casovem intervalu 
		if (k_fire && ((canontimer>0)?(reload>(0.2/(plevel))):(reload>(0.5/(plevel*0.9))))) { 
			if (canontimer<=0)
				//strelba zavisla na power levelu
				add_bullet(posx, posy+50, 0, 200, plevel, 1, 1);
			else 
				//silenej gun po sebrani zeleneho bonusu
				add_bullet(posx, posy+50, 0.8*speedx+200*DFRAND*DFRAND*DFRAND, 300+speedy+20*DFRAND, 10*plevel, 1, 1); 
			reload=0;
		}
		
		//aplikace rychlosti raketky na pozici
		posx+=speedx*time;
		posy+=speedy*time;

		//aby raketka brzdila stejne pri ruznem frameratu
		speedx*=powf(0.02, time); //powf = exponenciela
		speedy*=powf(0.02, time);

		//okraje hraciho pole pro raketku
		if (posx<-225) {posx=-225; speedx=0;} 
		if (posx>225) {posx=225; speedx=0;}
		if (posy<-335) {posy=-335; speedy=0;}
		if (posy>-100) {posy=-100; speedy=0;}

		move_stars(time);
		move_enemies(time);
		move_bullets(time);
		update_particles(time);
		move_bonuses(time);
	}
}

//funkce obstara efekt pri ztrate zivota (power levelu)
void player_injury(float posx, float posy) {
	int i;
	for (i=0;i<110;i++)
		add_particle(posx, posy, 50*DFRAND, 50*DFRAND, FRAND, 1, FRAND, 0.5, 2);
}

//funkce obstara vybuch raketky pri 0 hp
void player_explosion(float posx, float posy) { 
	int i;
	for (i=0;i<160;i++)
		add_particle(posx, posy, 50*DFRAND, 50*DFRAND, 2*FRAND, 1, FRAND, 0.1, 1);
	for (i=0;i<110;i++)
		add_particle(posx, posy, 150*DFRAND, 150*DFRAND, 3*FRAND, 1, FRAND, 0.5, 2);
	for (i=0;i<115;i++)
		add_particle(posx+10*DFRAND, posy+10*DFRAND, 10*DFRAND, 10*DFRAND, 6*FRAND, 0.5, 0.5, 0.5, 3);
	for (i=0;i<160;i++)
		add_particle(posx, posy, 50*DFRAND, 50*DFRAND, 2*FRAND, 1, 0.5*FRAND, 0.1, 3);
}

//funkce volana z bullets.c
int try_to_damage_player(float x, float y, int dmg) {
	if (playerdead) return 0;

	//kontrola kolize strely s raketkou
	if (((3*(x-posx)+50)>=(y-posy)) && (posy-10<=y) && (-3*(x-posx)+50>=(y-posy))) {
		//pokud ma raketka stit, strela se jen smaze (bullets.c)
		if (shieldtimer>0) return 1;
		
		hp-=dmg;

		//level-down
		if (hp<=0) { 
			plevel--;
			hp=1;
		}

		//kdyz hrac zemre
		if (plevel<=0) {
			player_explosion(posx, posy+25);
			
			//konec hry pri prohre
			playerdead=1;

			//casova rezerva na konci hry (par vterin na pusteni mezerniku)
			deathtimer=2;	
		}
		//strela bouchne na raketce
		else player_injury(x, y);

		//zasah! vraceni 1 pro smazani strely (do bullets.c)
		return 1;
	}
	//raketka nezasazena
	return 0;
}

//funkce volana z bonus.c
int player_bonuses(float x, float y, int type) {
	if (playerdead) return 0;
	
	//kontrola kolize bonusu s raketkou
	if (((3*(x-posx)+50)>=(y-posy)) && (posy-10<=y) && (-3*(x-posx)+50>=(y-posy))) {
		switch (type) {
			case 0: 
				//docasny stit
				shieldtimer=20;	
				break;
			case 1: 
				//1x power-up
				plevel++;
				break;
			case 2: 
				//bonus skore
				score+=(500*level);
				break;
			case 3: 
				//delo!
				canontimer=20;
				break;
			default: break;
		}
		//bonus sebran, vraceni 1 pro smazani bonusu (do bonus.c)
		return 1;
	}
	//bonus nesebran
	return 0;
}

//funkce pro pridavani a udrzeni skore
void add_score(int s) {
	if (playerdead) return;
	score+=s;
}

