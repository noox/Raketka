
#include "enemywave.h"

#include "frand.h"
#include "enemy.h"

//nageneruje novou vlnu nepratel na zacatku kola
void generate_enemy_wave(int level) {
	int a, b;
	//obycejni nepratele jsou v mrizce
	for(a=-220;a<=220;a+=40) 
		for(b=280;b<=320;b+=40)
			add_enemy(DFRAND*100,380,0,-1,a,b,20,1+(level),level,1);
	
	//stitovi nepratele
	for(a=1;a<=level;a++)
		add_enemy(DFRAND*100,380,0,-1,0,250,20,5+(level*12),level,2);
	
	//utocni nepratele
	for(a=1;a<=level;a++)
		add_enemy(DFRAND*100,380,0,-1,0,200,20,5+(level*3),level,3);
}

