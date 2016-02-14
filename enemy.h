
void init_enemies();
void delete_enemies();
void add_enemy(float posx, float posy, float speedx, float speedy, float targetx, float targety, float rad, int hp, int level, int type);
int try_to_damage_enemy(float posx, float posy, int dmg);
void move_enemies(float time);
void draw_enemies();
int out_of_enemies();

